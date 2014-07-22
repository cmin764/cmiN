#! /usr/bin/env python
# Subtitle Config Editor
# 11.04.2012 cmiN
# Tkinter GUI used to insert data into files


from Tkinter import *
from tkMessageBox import showinfo
from tkFileDialog import askopenfilename
from os.path import isdir, isfile
from subprocess import call # better than os.system


# constants
TITLE = "Config Editor" # window title # modify as you wish
RES = (300, 150) # resolution # width, height


class GUI(Frame):
    """Self-sustained frame.
    Constructor does all the job.
    """

    def __init__(self, master=None, margin=10):
        """Same as Frame's plus some links."""
        Frame.__init__(self, master, padx=margin, pady=margin)
        self.master.title(TITLE)
        self.master.minsize(*RES)
        self.master.maxsize(*RES)
        self.grid()
        self.widgets()
        self.mainloop()

    def __update(self, string):
        self.statusVar.set(string)

    def help_command(self):
        """Show this."""
        strings = ["1) Load a configuration file.",
                   "2) Fill the entries.",
                   "3) Click `Add` to append them.",
                   "4) Click `Start` to process them."]
        showinfo(parent=self.helpButton, title="Help", message="\n".join(strings))
        self.__update("Ready.")

    def load_command(self):
        """User dialog for selecting a file."""
        # build available types
        ftypes = [("Text", "*.txt"), ("Config", "*.cfg"), ("All", "*")]
        # get path to that file
        fpath = askopenfilename(parent=self.loadButton, title="Open config", filetypes=ftypes)
        if fpath == "" or type(fpath) is tuple: # mothafucka clicked cancel
            self.__update("Nothing loaded.")
            return
        # try to open it
        try:
            self.fobj = open(fpath, "a") # create file object
            self.fpath = fpath
            # substract the name
            index = max(fpath.rfind("/"), fpath.rfind("\\")) # win/posix
            fname = fpath[index + 1:]
            # update accordingly
            self.master.title(TITLE + " - " + fname)
            self.__update("Loaded %s." % fname)
        except IOError:
            self.fobj = None
            self.master.title(TITLE)
            self.__update("Cannot open the file.")

    def add_command(self):
        # check for exceptions
        if self.fobj is None: # file not ok
            self.__update("Select a configuration file first. See Help.")
            return
        if self.fobj.closed:
            try:
                self.fobj = open(self.fpath, "a") # reopen
            except IOError:
                self.fobj = None
                self.master.title(TITLE)
                self.__update("Cannot reopen the file.")
                return
        strings = [self.mainVar.get(), self.subVar.get(), self.movieVar.get()]
        valid = True # all strings must be directories
        if not isdir(strings[0]):
            valid = False
            self.mainEntry.config(bg="pink")
        if not isdir(strings[1]):
            valid = False
            self.subEntry.config(bg="pink")
        if not isdir(strings[2]):
            valid = False
            self.movieEntry.config(bg="pink")
        if not valid:
            self.__update("Invalid directories.")
            return
        # concatenate the lines
        data = "\n".join(strings)
        # write them
        self.fobj.write(data + "\n")
        self.fobj.flush()
        self.__update("Successfully added.")

    def start_command(self):
        """Start a process to take care of the configuration file."""
        if self.toExec is None: # not defined
            self.toExec = askopenfilename(parent=self.startButton, title="Open engine", filetypes=[("All", "*")])
            if self.toExec == ""  or type(self.toExec) is tuple:
                self.toExec = None
                self.__update("Canceled.")
                return
            if not isfile(self.toExec):
                self.toExec = None
                self.__update("Invalid engine.")
                return
        if self.fobj:
            self.fobj.close() # you're not in custody anymore :)
        self.__update("Started.")
        self.update() # because `call` is called before `statusLabel` is updated
        try:
            ret = call([self.toExec])
            self.__update("Completed with return code %d." % ret)
        except OSError:
            self.toExec = None
            self.__update("File busy or not runnable.")

    def handle_event(self, event):
        """Can't touch this xD."""
        if event.widget == self.mainEntry:
            self.mainEntry.config(bg="white")
        elif event.widget == self.subEntry:
            self.subEntry.config(bg="white")
        elif event.widget == self.movieEntry:
            self.movieEntry.config(bg="white")

    def widgets(self):
        """Create entries and buttons."""
        # simple "global" variables
        self.fobj = None
        self.toExec = None
        # object-like variables
        self.mainVar = StringVar()
        self.subVar = StringVar()
        self.movieVar = StringVar()
        self.statusVar = StringVar(value="Ready.")
        # create pairs of "Label: [_____________]"
        self.mainLabel = Label(self, text="Main: ", fg="darkgreen")
        self.mainEntry = Entry(self, textvariable=self.mainVar, width=25)
        self.subLabel = Label(self, text="Subtitles: ", fg="darkgreen")
        self.subEntry = Entry(self, textvariable=self.subVar, width=25)
        self.movieLabel = Label(self, text="Movie: ", fg="darkgreen")
        self.movieEntry = Entry(self, textvariable=self.movieVar, width=25)
        # create buttons
        self.helpButton = Button(self, text="Help", command=self.help_command, width=4)
        self.loadButton = Button(self, text="Load", command=self.load_command, width=4)
        self.addButton = Button(self, text="Add", command=self.add_command, width=4)
        self.startButton = Button(self, text="Start", command=self.start_command, width=4,
                                  fg="red", activeforeground="red")
        # status bar
        self.statusLabel = Label(self, textvariable=self.statusVar, relief="sunken", bd=2, anchor="w", padx=10, width=30)
        # make them visible
        self.mainLabel.grid(row=0, column=0, sticky="w")
        self.mainEntry.grid(row=0, column=1)
        self.subLabel.grid(row=1, column=0, sticky="w")
        self.subEntry.grid(row=1, column=1)
        self.movieLabel.grid(row=2, column=0, sticky="w")
        self.movieEntry.grid(row=2, column=1)
        self.helpButton.grid(row=3, column=0, sticky="sw", pady=10)
        self.loadButton.grid(row=3, column=1, sticky="sw", pady=10)
        self.addButton.grid(row=3, column=1, sticky="s", pady=10)
        self.startButton.grid(row=3, column=1, sticky="se", pady=10)
        self.statusLabel.grid(row=4, column=0, columnspan=2, sticky="nswe")
        # events for resetting the pink "error level"
        self.mainEntry.bind("<KeyRelease>", self.handle_event)
        self.subEntry.bind("<KeyRelease>", self.handle_event)
        self.movieEntry.bind("<KeyRelease>", self.handle_event)


if __name__ == "__main__":
    # only if not imported
    # create the main window with a frame in it
    GUI(Tk())
