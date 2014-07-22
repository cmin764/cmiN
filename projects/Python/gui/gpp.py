#! /usr/bin/env python
#
# gpp: gui support for parport


try:
    from Tkinter import *
except ImportError:
    print "Please install python-tk"
from tkFileDialog import askopenfilename
from tkMessageBox import showinfo
from subprocess import call


DBIT = 8 # data register bit length
CBIT = 4 # control register bit length


class GUI(Frame):

    def __init__(self, master=None, margin=10):
        Frame.__init__(self, master)
        self.master.title("gparport")
        self.grid(padx=margin, pady=margin)
        self.widgets()

    def widgets(self):
        # Data Register text
        self.dataLabel = Label(self, text="Data Register: ")
        self.dataLabel.grid(row=0, column=0, columnspan=DBIT, sticky=W)
        self.dataVar = StringVar(self, "0")
        self.dataDisplay = Label(self, textvariable=self.dataVar,
                                 fg="darkgreen")
        self.dataDisplay.grid(row=0, column=3)
        # Data Register checkboxes
        self.dataCheck = list()
        for nr in xrange(DBIT):
            var = IntVar()
            newBox = Checkbutton(self, text=str(DBIT - nr - 1), variable=var,
                                 onvalue=1, offvalue=0, command=self.data_c)
            newBox.grid(row=1, column=nr)
            self.dataCheck.insert(0, var)

        # Control Register text
        self.controlLabel = Label(self, text="Control Register: ")
        self.controlLabel.grid(row=2, column=0, columnspan=CBIT, sticky=W)
        self.controlVar = StringVar(self, "0")
        self.controlDisplay = Label(self, textvariable=self.controlVar,
                                    fg="darkgreen")
        self.controlDisplay.grid(row=2, column=3)
        # Control Register checkboxes
        self.controlCheck = list()
        for nr in xrange(CBIT):
            var = IntVar()
            newBox = Checkbutton(self, text=str(CBIT - nr - 1), variable=var,
                                 onvalue=1, offvalue=0, command=self.control_c)
            newBox.grid(row=3, column=nr)
            self.controlCheck.insert(0, var)

        # Start
        self.epath = "" # binary path
        self.startButton = Button(self, text="Start", command=self.process)
        self.startButton.grid(row=3, column=4, columnspan=DBIT - CBIT,
                              sticky=W+E)

    def data_c(self):
        # Compute Data Register integer
        bitstring = ""
        for i in xrange(DBIT):
            bit = self.dataCheck[i].get()
            bitstring = str(bit) + bitstring
        self.dataVar.set(str(int(bitstring, 2)))

    def control_c(self):
        # Compute Control Register integer
        bitstring = ""
        for i in xrange(CBIT):
            bit = self.controlCheck[i].get()
            bitstring = str(bit) + bitstring
        self.controlVar.set(str(int(bitstring, 2)))

    def process(self):
        if not self.epath:
            # define path
            fileTypes = [("All Files", "*")]
            self.epath = askopenfilename(parent=self, title="Open",
                                         filetypes=fileTypes)
        if not self.epath:
            return # path not set
        callArgs = [self.epath, self.dataVar.get(), self.controlVar.get()]
        rc = call(callArgs)
        # show some information
        #showinfo("Info", "Executed: %s %s %s\nReturned: %d" %
        #         tuple(callArgs + [rc]))


if __name__ == "__main__":
    GUI().mainloop()
