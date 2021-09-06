/*
    Core Architecture                        
    -------           -------
    |Core0|           |Core1|
    -------           -------
    Config loading    
    USB HID           GUI display          
    Serial            WS2812b mgmt  
    Keyboard scaning
    FS operations    
*/

#include <U8g2lib.h>
#include "GyverButton.h"
#include "Adafruit_TinyUSB.h"
#include <Adafruit_NeoPixel.h>
#include <LittleFS.h>
#include <ArduinoJson.h>


//Variables to be edited for different settings

//WS2812b pin
#define PIN 1

//Number of LEDs
#define LED_NUM 16

//Row pins
#define ROW_4 15
#define ROW_3 14
#define ROW_2 13
#define ROW_1 12

//Col pins
#define COL_1 6
#define COL_2 7
#define COL_3 8
#define COL_4 9

//total number of keys
#define KEY_NUM 16

//the size of the JSON buffer in bytes, must be bigger than maximum expected file size.
#define JSON_BUFFER_SIZE 4096

//Standard config to fallback to in case the filesystem has no configs already.
//(Has to be made with escape characters to not escape the string earlier than necessary)
const char stConfing[] PROGMEM = "{\n"
"    \"config\":{\n"
"        \"name\": \"This is a very long config name, 64 symbols maxxxxxxxxxxxxxxxxxx\",\n"
"        \"number\": 0,\n"
"        \"key1\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"    \n"
"        ],\n"
"        \"key2\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key3\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key4\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key5\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key6\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key7\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key8\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key9\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key10\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key11\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key12\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key13\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key14\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key15\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"key16\":[\n"
"            \"0xE5\", \n"
"            \"0x09\",\n"
"            \"0xE0\",\n"
"            \"0xE1\",\n"
"            \"0xE6\",\n"
"            \"0x28\"\n"
"        ],\n"
"        \"LED1\":[255, 123, 228],\n"
"        \"LED2\":[255, 123, 228],\n"
"        \"LED3\":[255, 123, 228],\n"
"        \"LED4\":[255, 123, 228],\n"
"        \"LED5\":[255, 123, 228],\n"
"        \"LED6\":[255, 123, 228],\n"
"        \"LED7\":[255, 123, 228],\n"
"        \"LED8\":[255, 123, 228],\n"
"        \"LED9\":[255, 123, 228],\n"
"        \"LED10\":[255, 123, 228],\n"
"        \"LED11\":[255, 123, 228],\n"
"        \"LED12\":[255, 123, 228],\n"
"        \"LED13\":[255, 123, 228],\n"
"        \"LED14\":[255, 123, 228],\n"
"        \"LED15\":[255, 123, 228],\n"
"        \"LED16\":[255, 123, 228]\n"
"    }\n"
"}\n"
"";

//Internal variables


boolean buttonStatus[16];
unsigned long millis_last;




enum
{
  RID_KEYBOARD = 1,
  RID_MOUSE,
  RID_CONSUMER_CONTROL, // Media, volume etc ..
};

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
  TUD_HID_REPORT_DESC_MOUSE   ( HID_REPORT_ID(RID_MOUSE) ),
  TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_CONSUMER_CONTROL) )
};


Adafruit_USBD_HID usb_hid;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);


GButton button0;
GButton button1;
GButton button2;
GButton button3;
GButton button4;
GButton button5;
GButton button6;
GButton button7;
GButton button8;
GButton button9;
GButton button10;
GButton button11;
GButton button12;
GButton button13;
GButton button14;
GButton button15;

U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/10, /* data=*/11, /* cs=*/4, /* dc=*/5, /* reset=*/2);

struct Config
{

  const char* name;
  uint8_t configNumber;
  uint8_t keyCommands[16][6];
  uint8_t ledColors[16][3];
  /*
  TODO
  add bitmap space
  add rgb color animations
  add program for configs
  add LED brightness
  */
};
Config config; 




void u8g2_prepare(void)
{
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

void u8g2_box_frame(uint8_t a)
{
    u8g2.drawStr(0, 0, "drawBox");
    u8g2.drawBox(5, 10, 20, 10);
    u8g2.drawBox(10 + a, 15, 30, 7);
    u8g2.drawStr(0, 30, "drawFrame");
    u8g2.drawFrame(5, 10 + 30, 20, 10);
    u8g2.drawFrame(10 + a, 15 + 30, 30, 7);
}

void u8g2_disc_circle(uint8_t a)
{
    u8g2.drawStr(0, 0, "drawDisc");
    u8g2.drawDisc(10, 18, 9);
    u8g2.drawDisc(24 + a, 16, 7);
    u8g2.drawStr(0, 30, "drawCircle");
    u8g2.drawCircle(10, 18 + 30, 9);
    u8g2.drawCircle(24 + a, 16 + 30, 7);
}

void u8g2_r_frame(uint8_t a)
{
    u8g2.drawStr(0, 0, "drawRFrame/Box");
    u8g2.drawRFrame(5, 10, 40, 30, a + 1);
    u8g2.drawRBox(50, 10, 25, 40, a + 1);
}

void u8g2_string(uint8_t a)
{
    u8g2.setFontDirection(0);
    u8g2.drawStr(30 + a, 31, " 0");
    u8g2.setFontDirection(1);
    u8g2.drawStr(30, 31 + a, " 90");
    u8g2.setFontDirection(2);
    u8g2.drawStr(30 - a, 31, " 180");
    u8g2.setFontDirection(3);
    u8g2.drawStr(30, 31 - a, " 270");
}

void u8g2_line(uint8_t a)
{
    u8g2.drawStr(0, 0, "drawLine");
    u8g2.drawLine(7 + a, 10, 40, 55);
    u8g2.drawLine(7 + a * 2, 10, 60, 55);
    u8g2.drawLine(7 + a * 3, 10, 80, 55);
    u8g2.drawLine(7 + a * 4, 10, 100, 55);
}

void u8g2_triangle(uint8_t a)
{
    uint16_t offset = a;
    u8g2.drawStr(0, 0, "drawTriangle");
    u8g2.drawTriangle(14, 7, 45, 30, 10, 40);
    u8g2.drawTriangle(14 + offset, 7 - offset, 45 + offset, 30 - offset, 57 + offset, 10 - offset);
    u8g2.drawTriangle(57 + offset * 2, 10, 45 + offset * 2, 30, 86 + offset * 2, 53);
    u8g2.drawTriangle(10 + offset, 40 + offset, 45 + offset, 30 + offset, 86 + offset, 53 + offset);
}

void u8g2_ascii_1()
{
    char s[2] = " ";
    uint8_t x, y;
    u8g2.drawStr(0, 0, "ASCII page 1");
    for (y = 0; y < 6; y++)
    {
        for (x = 0; x < 16; x++)
        {
            s[0] = y * 16 + x + 32;
            u8g2.drawStr(x * 7, y * 10 + 10, s);
        }
    }
}

void u8g2_ascii_2()
{
    char s[2] = " ";
    uint8_t x, y;
    u8g2.drawStr(0, 0, "ASCII page 2");
    for (y = 0; y < 6; y++)
    {
        for (x = 0; x < 16; x++)
        {
            s[0] = y * 16 + x + 160;
            u8g2.drawStr(x * 7, y * 10 + 10, s);
        }
    }
}

void u8g2_extra_page(uint8_t a)
{
    u8g2.drawStr(0, 0, "Unicode");
    u8g2.setFont(u8g2_font_unifont_t_symbols);
    u8g2.setFontPosTop();
    u8g2.drawUTF8(0, 24, "☀ ☁");
    switch (a)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        u8g2.drawUTF8(a * 3, 36, "☂");
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        u8g2.drawUTF8(a * 3, 36, "☔");
        break;
    }
}

#define cross_width 24
#define cross_height 24
static const unsigned char cross_bits[] U8X8_PROGMEM = {
    0x00,
    0x18,
    0x00,
    0x00,
    0x24,
    0x00,
    0x00,
    0x24,
    0x00,
    0x00,
    0x42,
    0x00,
    0x00,
    0x42,
    0x00,
    0x00,
    0x42,
    0x00,
    0x00,
    0x81,
    0x00,
    0x00,
    0x81,
    0x00,
    0xC0,
    0x00,
    0x03,
    0x38,
    0x3C,
    0x1C,
    0x06,
    0x42,
    0x60,
    0x01,
    0x42,
    0x80,
    0x01,
    0x42,
    0x80,
    0x06,
    0x42,
    0x60,
    0x38,
    0x3C,
    0x1C,
    0xC0,
    0x00,
    0x03,
    0x00,
    0x81,
    0x00,
    0x00,
    0x81,
    0x00,
    0x00,
    0x42,
    0x00,
    0x00,
    0x42,
    0x00,
    0x00,
    0x42,
    0x00,
    0x00,
    0x24,
    0x00,
    0x00,
    0x24,
    0x00,
    0x00,
    0x18,
    0x00,
};

#define cross_fill_width 24
#define cross_fill_height 24
static const unsigned char cross_fill_bits[] U8X8_PROGMEM = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x18,
    0x00,
    0x18,
    0x64,
    0x00,
    0x26,
    0x84,
    0x00,
    0x21,
    0x08,
    0x81,
    0x10,
    0x08,
    0x42,
    0x10,
    0x10,
    0x3C,
    0x08,
    0x20,
    0x00,
    0x04,
    0x40,
    0x00,
    0x02,
    0x80,
    0x00,
    0x01,
    0x80,
    0x18,
    0x01,
    0x80,
    0x18,
    0x01,
    0x80,
    0x00,
    0x01,
    0x40,
    0x00,
    0x02,
    0x20,
    0x00,
    0x04,
    0x10,
    0x3C,
    0x08,
    0x08,
    0x42,
    0x10,
    0x08,
    0x81,
    0x10,
    0x84,
    0x00,
    0x21,
    0x64,
    0x00,
    0x26,
    0x18,
    0x00,
    0x18,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

#define cross_block_width 14
#define cross_block_height 14
static const unsigned char cross_block_bits[] U8X8_PROGMEM = {
    0xFF,
    0x3F,
    0x01,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0xC1,
    0x20,
    0xC1,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0x01,
    0x20,
    0xFF,
    0x3F,
};

void u8g2_bitmap_overlay(uint8_t a)
{
    uint8_t frame_size = 28;

    u8g2.drawStr(0, 0, "Bitmap overlay");

    u8g2.drawStr(0, frame_size + 12, "Solid / transparent");
    u8g2.setBitmapMode(false /* solid */);
    u8g2.drawFrame(0, 10, frame_size, frame_size);
    u8g2.drawXBMP(2, 12, cross_width, cross_height, cross_bits);
    if (a & 4)
        u8g2.drawXBMP(7, 17, cross_block_width, cross_block_height, cross_block_bits);

    u8g2.setBitmapMode(true /* transparent*/);
    u8g2.drawFrame(frame_size + 5, 10, frame_size, frame_size);
    u8g2.drawXBMP(frame_size + 7, 12, cross_width, cross_height, cross_bits);
    if (a & 4)
        u8g2.drawXBMP(frame_size + 12, 17, cross_block_width, cross_block_height, cross_block_bits);
}

void u8g2_bitmap_modes(uint8_t transparent)
{
    const uint8_t frame_size = 24;

    u8g2.drawBox(0, frame_size * 0.5, frame_size * 5, frame_size);
    u8g2.drawStr(frame_size * 0.5, 50, "Black");
    u8g2.drawStr(frame_size * 2, 50, "White");
    u8g2.drawStr(frame_size * 3.5, 50, "XOR");

    if (!transparent)
    {
        u8g2.setBitmapMode(false /* solid */);
        u8g2.drawStr(0, 0, "Solid bitmap");
    }
    else
    {
        u8g2.setBitmapMode(true /* transparent*/);
        u8g2.drawStr(0, 0, "Transparent bitmap");
    }
    u8g2.setDrawColor(0); // Black
    u8g2.drawXBMP(frame_size * 0.5, 24, cross_width, cross_height, cross_bits);
    u8g2.setDrawColor(1); // White
    u8g2.drawXBMP(frame_size * 2, 24, cross_width, cross_height, cross_bits);
    u8g2.setDrawColor(2); // XOR
    u8g2.drawXBMP(frame_size * 3.5, 24, cross_width, cross_height, cross_bits);
}

uint8_t draw_state = 0;

void draw(void)
{
    u8g2_prepare();
    switch (draw_state >> 3)
    {
    case 0:
        u8g2_box_frame(draw_state & 7);
        break;
    case 1:
        u8g2_disc_circle(draw_state & 7);
        break;
    case 2:
        u8g2_r_frame(draw_state & 7);
        break;
    case 3:
        u8g2_string(draw_state & 7);
        break;
    case 4:
        u8g2_line(draw_state & 7);
        break;
    case 5:
        u8g2_triangle(draw_state & 7);
        break;
    case 6:
        u8g2_ascii_1();
        break;
    case 7:
        u8g2_ascii_2();
        break;
    case 8:
        u8g2_extra_page(draw_state & 7);
        break;
    case 9:
        u8g2_bitmap_modes(0);
        break;
    case 10:
        u8g2_bitmap_modes(1);
        break;
    case 11:
        u8g2_bitmap_overlay(draw_state & 7);
        break;
    }
}

void keySetup(){
  button0.setType(LOW_PULL);
  button1.setType(LOW_PULL);
  button2.setType(LOW_PULL);
  button3.setType(LOW_PULL);
  button4.setType(LOW_PULL);
  button5.setType(LOW_PULL);
  button6.setType(LOW_PULL);
  button7.setType(LOW_PULL);
  button8.setType(LOW_PULL);
  button9.setType(LOW_PULL);
  button10.setType(LOW_PULL);
  button11.setType(LOW_PULL);
  button12.setType(LOW_PULL);
  button13.setType(LOW_PULL);
  button14.setType(LOW_PULL);
  button15.setType(LOW_PULL);
  button0.setDebounce(5);
  button1.setDebounce(5);
  button2.setDebounce(5);
  button3.setDebounce(5);
  button4.setDebounce(5);
  button5.setDebounce(5);
  button6.setDebounce(5);
  button7.setDebounce(5);
  button8.setDebounce(5);
  button9.setDebounce(5);
  button10.setDebounce(5);
  button11.setDebounce(5);
  button12.setDebounce(5);
  button13.setDebounce(5);
  button14.setDebounce(5);
  button15.setDebounce(5);
}


void matrixStatus(){
  byte keyCounter = 0;
  for(byte y = ROW_4; y >= ROW_1; y--){
    for(byte x = COL_1; x <= COL_4; x++){
      pinMode(y, OUTPUT);
      digitalWrite(y, HIGH);
      buttonStatus[keyCounter] = digitalRead(x);
      keyCounter++;
      pinMode(y, INPUT);
    }
  }
}

void keyTicker(){
  button0.tick(buttonStatus[0]);
  button1.tick(buttonStatus[1]);
  button2.tick(buttonStatus[2]);
  button3.tick(buttonStatus[3]);
  button4.tick(buttonStatus[4]);
  button5.tick(buttonStatus[5]);
  button6.tick(buttonStatus[6]);
  button7.tick(buttonStatus[7]);
  button8.tick(buttonStatus[8]);
  button9.tick(buttonStatus[9]);
  button10.tick(buttonStatus[10]);
  button11.tick(buttonStatus[11]);
  button12.tick(buttonStatus[12]);
  button13.tick(buttonStatus[13]);
  button14.tick(buttonStatus[14]);
  button15.tick(buttonStatus[15]);
}
void keyProcessor(){
  if (usb_hid.ready()){
    static bool has_key[KEY_NUM];
    bool isPress[] = {button0.isPress(), button1.isPress(), button2.isPress(), button3.isPress(),
    button4.isPress(), button5.isPress(), button6.isPress(), button7.isPress(), button8.isPress(), button9.isPress(),
    button10.isPress(), button11.isPress(), button12.isPress(), button13.isPress(), button14.isPress(), button15.isPress()};
    bool isRelease[] = {button0.isRelease(), button1.isRelease(), button2.isRelease(), button3.isRelease(),
    button4.isRelease(), button5.isRelease(), button6.isRelease(), button7.isRelease(), button8.isRelease(), button9.isRelease(),
    button10.isRelease(), button11.isRelease(), button12.isRelease(), button13.isRelease(), button14.isRelease(), button15.isRelease()};
    for(uint8_t key = 0; key < KEY_NUM; key++){
      if(isPress[key]){
        usb_hid.keyboardReport(RID_KEYBOARD, 0, config.keyCommands[key]);
        has_key[key] = true;
      }else if(isRelease[key]){
        if (has_key[key]) usb_hid.keyboardRelease(RID_KEYBOARD);
        has_key[key] = false;
      } 
    }
  }





//  if ( USBDevice.suspended() && btn_pressed )
//  {
//    // Wake up host if we are in suspend mode
//    // and REMOTE_WAKEUP feature is enabled by host
//    USBDevice.remoteWakeup();
//  }


  
//  butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
//
//  if (butt1.isClick()) Serial.println("Click");         // проверка на один клик
//  if (butt1.isSingle()) Serial.println("Single");       // проверка на один клик
//  if (butt1.isDouble()) Serial.println("Double");       // проверка на двойной клик
//  if (butt1.isTriple()) Serial.println("Triple");       // проверка на тройной клик
//
//  if (butt1.hasClicks())                                // проверка на наличие нажатий
//    Serial.println(butt1.getClicks());                  // получить (и вывести) число нажатий
//
//  if (butt1.isPress()) Serial.println("Press");         // нажатие на кнопку (+ дебаунс)
//  if (butt1.isRelease()) Serial.println("Release");     // отпускание кнопки (+ дебаунс)
//  if (butt1.isHold()) {                  // если кнопка удерживается
//    Serial.print("Holding ");             // выводим пока удерживается
//    Serial.println(butt1.getHoldClicks());        // можно вывести количество кликов перед удержанием!
//  }
//  if (butt1.isHold()) Serial.println("Holding");        // проверка на удержание
//  //if (butt1.state()) Serial.println("Hold");          // возвращает состояние кнопки
//
//  if (butt1.isStep()) {                                 // если кнопка была удержана (это для инкремента)
//    value++;                                            // увеличивать/уменьшать переменную value с шагом и интервалом
//    Serial.println(value);                              // для примера выведем в порт
//  }
//    
}

uint8_t getConfNumber(){  //returns number of files found in the config directory
  uint8_t numberOfFiles = 0;
  Dir dir = LittleFS.openDir("/config");
  while (dir.next()) {
    if(dir.fileSize()) {
      numberOfFiles++;
    }
  }
  return numberOfFiles;
}

uint8_t hexToInt(const char* input){
  char buff[16];
  strcpy(buff, input);
  for(uint8_t i = 0; i < (sizeof(buff)/sizeof(char))-2; i++){
    buff[i] = buff[i+2];   
  }
  uint8_t r = (uint8_t)strtol(buff, NULL, 16);
  return r;
}

void loadConfig(uint8_t number = 0){
  Dir dir = LittleFS.openDir("/config");
  while (dir.next()) {
    char buff[16];
    bzero(buff, 16);
    dir.fileName().toCharArray(buff, 16);
    char * pch;
    pch = strtok(buff,"config.json");
    uint8_t confNum = atoi(pch);
    if(confNum == number && dir.fileSize()){
      File f = dir.openFile("r");
      if (f && f.size() <= JSON_BUFFER_SIZE) {
        StaticJsonDocument<JSON_BUFFER_SIZE> doc;
        DeserializationError error = deserializeJson(doc, f);
        
        //DeserializationError error = deserializeJson(doc, json);
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          f.close();
          return;
        }
        //load config in to the struct called config
        config.configNumber = doc["config"]["number"];
        config.name = doc["config"]["name"];
        const char* input;
        //load key HID codes and LED colors
        for(uint8_t i = 0; i < 16; i++){
          char currField[16];
          bzero(currField, 16);
          sprintf(currField, "key%d", i+1);
          for(uint8_t j = 0; j < 6; j++){
            input = doc["config"][currField][j];
            config.keyCommands[i][j] = hexToInt(input);
          }
          bzero(currField, 16);
          sprintf(currField, "LED%d", i+1);
          for(uint8_t l = 0; l < 3; l++){
            config.ledColors[i][l] = doc["config"][currField][l];
          }
        }
        Serial.print("config number: ");
        Serial.println(config.configNumber);
        Serial.print("config name: ");
        Serial.println(config.name);
        Serial.print("config key1, first command: ");
        Serial.println(config.keyCommands[0][0]);
        Serial.print("config key1, 2nd command: ");
        Serial.println(config.keyCommands[0][1]);
        Serial.print("config key16, last command: ");
        Serial.println(config.keyCommands[15][5]);
        Serial.print("config led1, Red: ");
        Serial.println(config.ledColors[0][0]);
        Serial.print("config led16, Blue: ");
        Serial.println(config.ledColors[15][2]);
      }else{
        //TODO add display message about file too big
        f.close();
        Serial.println("Error: parsing failed due to file being larger than the buffer size. {JSON_BUFFER_SIZE_OVERFLOW}");
      }
      f.close();
    }
    Serial.println();
  }
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void ledService(uint8_t effect = 0){
  if(!effect){
    for(uint8_t i = 0; i < LED_NUM; i++){
      strip.setPixelColor(i, strip.Color(config.ledColors[i][0], config.ledColors[i][1], config.ledColors[i][2]));
    }
    strip.show();
  }
}
void setup(void)
{
  rp2040.idleOtherCore(); //doing anything with ArduinoJson causes the second core to lag idk why (maybe stack/heap overflow), to be fixed later
  
  
  
  
  for(byte y = COL_1; y <= COL_4; y++){     
      pinMode(y, INPUT);   
  }
  
  Serial.begin(115200);
  delay(100);
  LittleFS.begin();
  if(getConfNumber() == 0){           //in case the filesystem is empty create a basic config from ROM
    if(!LittleFS.exists("/config"))
      LittleFS.mkdir("/config");
    File f = LittleFS.open("/config/config0.json", "w");
    if (f) {
      f.write(stConfing, strlen(stConfing));
      f.close();
    }
  }



  // cnt++;
  // sprintf(buff, "%d\n", cnt);
  // f = LittleFS.open("counts.txt", "w");
  // if (f) {
  //   f.write(buff, strlen(buff));
  //   f.close();
  // }

  // Serial.println("---------------");
  // File i = LittleFS.open("file1.txt", "r");
  // if (i) {
  //   while (i.available()) {
  //     Serial.write(i.read());
  //   }
  //   Serial.println("---------------");
  //   i.close();
  // }
  keySetup();



  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setStringDescriptor("PicoMacro Keypad");

  usb_hid.begin();
  while( !USBDevice.mounted() ) delay(1);



  // Serial.println(getConfNumber());
  // loadConfig(getConfNumber() - 1);
}


void loop(void){
  matrixStatus();
  keyTicker();
  keyProcessor();
  // for(byte i = 0; i < 16; i++){
  //   Serial.print(buttonStatus[i]);
  //   Serial.print(", ");
  // }
  
  // Serial.print(", ");
  // Serial.println(micros() - millis_last);
  // millis_last = micros();
  delay(10);
  //Serial.println(getConfNumber());
  static unsigned long last_millis = 0;
  if(millis() - last_millis > 10000){
  last_millis = millis();  
  Serial.printf("core 1, millis: %d\n", millis());
  loadConfig(getConfNumber() - 1);
  ledService();
  }
}


//void setup1(){
  
    //u8g2.begin();
    //u8g2.clearBuffer();
    //strip.begin();
    //strip.setBrightness(100);
    //strip.show();
    //colorWipe(strip.Color(255, 0, 0), 50); // Red
    //colorWipe(strip.Color(0, 255, 0), 50); // Green
    //colorWipe(strip.Color(0, 0, 255), 50); // Blue
//}

//void loop1()
//{
    // picture loop

    // u8g2.clearBuffer();
    // draw();
    // u8g2.sendBuffer();

    // increase the state
    // draw_state++;
    // if (draw_state >= 12 * 8)
    //     draw_state = 0;
    // delay between each page
    //delay(100);
    //  static unsigned long last_millis = 0;
  //if(millis() - last_millis > 1000){
   // last_millis = millis();
  //Serial.printf("core 2, millis: %d\n", millis());
  //}
  //rainbowCycle(5);
//}
