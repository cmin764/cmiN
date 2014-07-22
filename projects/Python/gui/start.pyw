#! /usr/bin/env python
# File Runner
# 20.03.2012 cmiN


from os import startfile
from Tkinter import Tk, Frame, Button
from tkFileDialog import askopenfilename
from tkMessageBox import showinfo, showerror


class GUI(Frame):

    TITLE = "File Runner"

    def __init__(self, master=None, margin=10):
        Frame.__init__(self, master, padx=margin, pady=margin)
        self.grid()
        self.widgets()
        master.title(GUI.TITLE)
        master.mainloop()

    def browse(self):
        filePath = askopenfilename()
        if filePath in ("", None):
            return
        self.filePath = filePath
        self.startButton["state"] = "normal"
        index = max(filePath.rfind("\\"), filePath.rfind("/"))
        fileName = filePath[index + 1:]
        self.master.title(GUI.TITLE + " - %s" % fileName)

    def start(self):
        if self.filePath:
            startfile(self.filePath)
            showinfo("Info", "Started: %s" % self.filePath)
        else:
            showerror("Error", "Nothing to start!")

    def widgets(self):
        self.filePath = None
        self.browseButton = Button(self, text="Browse", width=10, command=self.browse)
        self.startButton = Button(self, text="Start", width=10, command=self.start, state="disabled")
        self.browseButton.grid(row=0, column=0, ipadx=10, ipady=10, padx=10, pady=10)
        self.startButton.grid(row=0, column=1, ipadx=10, ipady=10, padx=10, pady=10)


if __name__ == "__main__":
    GUI(Tk())
