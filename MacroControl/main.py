import tkinter as tk
from tkinter import Scale, StringVar
from tkinter.filedialog import askopenfilename as getFile
from typing import Text
from PIL import Image, ImageTk
# cheat sheet:

#     Columns
#    ┌───┐
#    │   │
#    ▼   ▼
# ┌──┬───┬──┐
# │  │   │  │
# ├──┼───┼──┤◄─────┐
# │  │   │  │      │Rows
# │  │   │  │      │
# ├──┼───┼──┤◄─────┘
# │  │   │  │
# └──┴───┴──┘


#    N
#    ▲
#    │
# W──┼──E
#    │
#    S


# window properties
window = tk.Tk()
window.geometry("1200x800")
window.title("Pico Macro Control")
window.grid_rowconfigure(0, weight=0)
window.grid_rowconfigure(1, weight=0)
window.grid_rowconfigure(2, weight=0)
window.grid_columnconfigure(0, weight=0)
window.grid_columnconfigure(1, weight=0)
window.grid_columnconfigure(2, weight=1)
window.grid_columnconfigure(3, weight=0)


# frame for objects related to the image
frameRightOfImage = tk.Frame(window, bg="purple")
frameRightOfImage.grid(row=0, column=1, rowspan=2, sticky="ne")

# thumbnail label
thumbnailLabel = tk.Label(frameRightOfImage, text="Thumbnail:")
thumbnailLabel.config(font=(("", 12)))
thumbnailLabel.grid(row=0, column=0, padx=20, pady=10, sticky="n")
# thumbnail new button
thumbnailNewButton = tk.Button(frameRightOfImage, text="New")
thumbnailNewButton.config(font=(("", 12)))
thumbnailNewButton.grid(row=0, column=1, padx=20, pady=10, sticky="e")
# TODO 
# exec this when button is pressed
# thumbnaiNewFilePath = getFile() # show an "Open" dialog box and return the path to the selected file
# print(thumbnaiNewButton)

# image for the profile thumbnail
size = 128, 128
img = Image.open("./stuff/profile#0.png")
img = img.resize(size, Image.NEAREST)
render = ImageTk.PhotoImage(img)
image = tk.Label(frameRightOfImage, image=render)
image.image = render
image.grid(row=1, column=0, columnspan=3, rowspan=1, sticky="n", padx=20)
# image.place(x=0, y=0)





# frame for objects left of the image
frameLeftOfImage = tk.Frame(window, bg="white")
frameLeftOfImage.grid(row=0, column=0, rowspan=2, columnspan=2, sticky="nw")


# profile label
profileLabel = tk.Label(frameLeftOfImage, text="Profile:")
profileLabel.config(font=(("", 12)))
profileLabel.grid(row=0, column=0, padx=10, pady=10, sticky="n")
# dropdown profile selector

dropdownVar = StringVar(window)
dropdownVar.set("Profile #0") # default value
dropdownList = {"Profile #1", "dsfdjkjhkjhkjhkjhjksfdsfdjkjhkjhkjhkjhjksfdsfdjkjhkjhkjhkjhjksff", "fsdfs"}

# TODO
# add check that displays ... when the name is too long
profileSelector = tk.OptionMenu(frameLeftOfImage, window, dropdownVar, *dropdownList)
profileSelector.config(width=15, font=(("", 12)))
profileSelector.grid(row=0, column=1)

# profile name label

profileNameEditorLabel = tk.Label(frameLeftOfImage, text="Profile Name:")
profileNameEditorLabel.config(font=(("", 12)))
profileNameEditorLabel.grid(row=1, column=0, padx=10, pady=10, sticky="n")

# profile name edit text field

profileName = ""
profileLabelEditor = tk.Entry(frameLeftOfImage, textvariable=profileName)
profileLabelEditor.config(font=(("", 12)), width=18)
profileLabelEditor.grid(row=1, column=1, padx=10, pady=10, sticky="n")

# profile shortcut label
profileShortcut = [1, 2, 16]
profileShortcutEditorLabel = tk.Label(frameLeftOfImage, text=("Profile Shortcut: " + str(profileShortcut)))
profileShortcutEditorLabel.config(font=(("", 12)))
profileShortcutEditorLabel.grid(row=2, column=0, columnspan=1, padx=10, pady=10, sticky="n")

# profile shortcut editor
profileShortcutEditorButton = tk.Button(frameLeftOfImage, text="New")
profileShortcutEditorButton.config(font=(("", 12)), width=10)
profileShortcutEditorButton.grid(row=2, column=1, padx=10, pady=10, sticky="n")





# frame for the button blocks
frameForButtons = tk.Frame(window, bg="blue")
frameForButtons.grid(row=2, column=0, rowspan=3, sticky="nw", columnspan=1)

# TODO
# add colors to buttons

# <buttons>
buttonGrid1 = tk.Button(frameForButtons, text=" B1 ", bg="#54FA9B", fg="black") # example of custom color for button
buttonGrid1.config(font=(("", 12)))
buttonGrid1.grid(row=0, column=0, padx=5, pady=5, sticky="nw")

buttonGrid2 = tk.Button(frameForButtons, text=" B2 ")
buttonGrid2.config(font=(("", 12)))
buttonGrid2.grid(row=0, column=1, padx=5, pady=5, sticky="nw")

buttonGrid3 = tk.Button(frameForButtons, text=" B3 ")
buttonGrid3.config(font=(("", 12)))
buttonGrid3.grid(row=0, column=2, padx=5, pady=5, sticky="nw")

buttonGrid4 = tk.Button(frameForButtons, text=" B4 ")
buttonGrid4.config(font=(("", 12)))
buttonGrid4.grid(row=0, column=3, padx=5, pady=5, sticky="nw")

buttonGrid5 = tk.Button(frameForButtons, text=" B5 ")
buttonGrid5.config(font=(("", 12)))
buttonGrid5.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

buttonGrid6 = tk.Button(frameForButtons, text=" B6 ")
buttonGrid6.config(font=(("", 12)))
buttonGrid6.grid(row=1, column=1, padx=5, pady=5, sticky="nw")

buttonGrid7 = tk.Button(frameForButtons, text=" B7 ")
buttonGrid7.config(font=(("", 12)))
buttonGrid7.grid(row=1, column=2, padx=5, pady=5, sticky="nw")

buttonGrid8 = tk.Button(frameForButtons, text=" B8 ")
buttonGrid8.config(font=(("", 12)))
buttonGrid8.grid(row=1, column=3, padx=5, pady=5, sticky="nw")

buttonGrid9 = tk.Button(frameForButtons, text=" B9 ")
buttonGrid9.config(font=(("", 12)))
buttonGrid9.grid(row=2, column=0, padx=5, pady=5, sticky="nw")

buttonGrid10 = tk.Button(frameForButtons, text="B10")
buttonGrid10.config(font=(("", 12)))
buttonGrid10.grid(row=2, column=1, padx=5, pady=5, sticky="nw")

buttonGrid11 = tk.Button(frameForButtons, text="B11")
buttonGrid11.config(font=(("", 12)))
buttonGrid11.grid(row=2, column=2, padx=5, pady=5, sticky="nw")

buttonGrid12 = tk.Button(frameForButtons, text="B12")
buttonGrid12.config(font=(("", 12)))
buttonGrid12.grid(row=2, column=3, padx=5, pady=5, sticky="nw")

buttonGrid13 = tk.Button(frameForButtons, text="B13")
buttonGrid13.config(font=(("", 12)))
buttonGrid13.grid(row=3, column=0, padx=5, pady=5, sticky="nw")

buttonGrid14 = tk.Button(frameForButtons, text="B14")
buttonGrid14.config(font=(("", 12)))
buttonGrid14.grid(row=3, column=1, padx=5, pady=5, sticky="nw")

buttonGrid15 = tk.Button(frameForButtons, text="B15")
buttonGrid15.config(font=(("", 12)))
buttonGrid15.grid(row=3, column=2, padx=5, pady=5, sticky="nw")

buttonGrid16 = tk.Button(frameForButtons, text="B16")
buttonGrid16.config(font=(("", 12)))
buttonGrid16.grid(row=3, column=3, padx=5, pady=5, sticky="nw")
# </buttons>




# frame for the button customization block
frameForButConf = tk.Frame(window, bg="orange")
frameForButConf.grid(row=2, column=1, rowspan=2, sticky="nw")

# label
configLabel = tk.Label(frameForButConf, text="Button X Selected:")
configLabel.config(font=(("", 12)))
configLabel.grid(row=0, column=0, padx=20, pady=10, sticky="n", columnspan=2)

shortcutLabel = tk.Label(frameForButConf, text="Shortcut:")
shortcutLabel.config(font=(("", 12)))
shortcutLabel.grid(row=1, column=0, padx=20, pady=10, sticky="w")

# text field for shortcut
shortcutVar = ""
shortcutVarDisplay = tk.Entry(frameForButConf, textvariable=shortcutVar)
shortcutVarDisplay.config(font=(("", 12)))
shortcutVarDisplay.grid(row=1, column=1, padx=10, pady=10, sticky="w")
# TODO
# figure out how to compress elements closer together ignoring the grid

# new shortcut button
newShortcutBtn = tk.Button(frameForButConf, text="New")
newShortcutBtn.config(font=(("", 12)))
newShortcutBtn.grid(row=1, column=2, padx=5, pady=5, sticky="w")

# color label



window.mainloop()
print("test")

# TODO
# design GUI