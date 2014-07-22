#! /usr/bin/env python
# Text In Image
# 02.01.2012 cmiN
#
# This is a simple GUI script which can hide text in pictures
# using least significant bit method.
# Also the input text can be encrypted and the output can be decrypted too
# with a symmetric key using AES.
# Writing is done directly on input image so be careful with certain extensions
# because the output will always have the BMP format.
#
# Contact: cmin764@yahoo/gmail.com


from Tkinter import * # widgets's classes
from tkFileDialog import askopenfilename # get file name
from tkMessageBox import showerror, showinfo # user dialog
from PIL import Image # image converting
from Crypto.Cipher import AES # text cipher


class Engine:
    """
    Code for processing the image.
    Separated from GUI.
    """
    
    def __init__(self):
        """ Initialize parameters. """
        self.ext = "bmp" # save format
        self.name = None # save name
        self.path = None # save path
        self.im = None # image object, read and write
        self.generator = None # get locations to write/read bits
        self.useAES = None # use it or not
        self.aes = None # AES object
        self.data = None # data to be written to image
        self.width = None # image width
        self.height = None # image height
        self.tmp = None # last string, used when key changes
        
    def binary(self, nr, size):
        """ Get 1&0 representation. """
        return bin(nr).replace("0b", "").zfill(size * 8)
        
    def path_name(self, path):
        """ Split a file path in path and name. """
        ind = path.rfind("/") + 1
        return (path[:ind], path[ind:])
        
    def set_generator(self):
        """ Useful for resetting. """
        self.generator = ((wp, hp, ch) for wp in xrange(self.width) # WxHxC
                                       for hp in xrange(self.height)
                                       for ch in xrange(3))
    
    def load(self, path):
        """ Load image. """
        self.im = Image.open(path)
        (self.width, self.height) = self.im.size
        (self.path, self.name) = self.path_name(path)
        return self.width * self.height * 3 # total useful bytes
        
    def parse_key(self, key):
        """ If key exists make an AES object from it. """
        if not key:
            self.aes = None # empty key == no encryption
            return self.parse_string(self.tmp) # must return size (see the next return)
        key.decode() # test availability
        size = len(key)
        for padding in (16, 24, 32): # fixed key size
            if size <= padding:
                break
        key += chr(0) * (padding - size)
        self.aes = AES.new(key)
        return self.parse_string(self.tmp) # if key changes you must update string
        
    def parse_string(self, string):
        """ Convert to bitstring. """
        if not string: # without string can't start the process
            self.tmp = None
            self.data = None
            return 0
        string.decode() # test availability
        self.tmp = string
        if self.useAES and self.aes: # encrypt it
            string += chr(0) * ((16 - len(string) % 16) % 16) # multiple of 16 string
            string = self.aes.encrypt(string)
        string = str().join([self.binary(ord(x), 1) for x in string]) # convert every char in a set of 8 bits
        size = self.binary(len(string), 4) # get binary representation of string's length in 4 bytes
        self.data = size + string
        return len(self.data)
            
    def write(self):
        """ Write using LSB. """
        self.set_generator() # rearm
        for bit in self.data:
            (wp, hp, ch) = self.generator.next() # get next position
            values = list(self.im.getpixel((wp, hp))) # retrieve its values
            tmp = self.binary(values[ch], 1) # convert one of them
            values[ch] = int(tmp[:7] + bit, 2) # alter that channel
            self.im.putpixel((wp, hp), tuple(values)) # put it back
        self.im.save(self.path + self.name, format=self.ext) # save the new output
        
    def read(self):
        """ Read from every LSB. """
        self.set_generator() # rearm
        total = self.width * self.height * 3
        if total < 32:
            raise Exception("Text not found.")
        size = chunk = string = str()
        i = 0 # for(i=0; true; ++i)
        while True:
            (wp, hp, ch) = self.generator.next() # i byte
            values = self.im.getpixel((wp, hp))
            tmp = self.binary(values[ch], 1)
            if i < 32: # it's lame but I prefer string/bitset
                size += tmp[7]
                if i == 31:
                    size = int(size, 2)
                    if size < 1 or (size + 32) > total:
                        raise Exception("Text not found.")
            elif i < size + 32:
                chunk += tmp[7]
                if len(chunk) == 8:
                    string += chr(int(chunk, 2))
                    chunk = str()
            else:
                break
            i += 1
        if self.useAES and self.aes:
            if len(string) % 16 != 0:
                raise Exception("Text not encrypted.")
            string = self.aes.decrypt(string).rstrip(chr(0))
        string.decode() # rise an exception if invalid
        return string
                

class GUI(Frame):
    """
    Main window, inherited from Frame.
    Here we put our widgets and set their behavior.
    """
    
    def __init__(self, master=None, margin=30):
        """ Same as Frame's constructor. """
        Frame.__init__(self, master, padx=margin, pady=margin)
        self.grid()
        self.widgets()
        self.behavior()
        
    def widgets(self):
        """ Build and grid widgets. """
        # ---- create variables ----
        self.totalBytes = IntVar() # depends on image size
        self.usedBytes = IntVar() # how many of them are used
        self.textStatus = StringVar() # used per total bytes
        self.useEncryption = IntVar() # 0-plain 1-AES
        self.mode = IntVar() # 0-read 1-write
        self.textOpt = dict() # text last config
        self.keyOpt = dict() # key last config
        self.loaded = False # image loaded or not
        # ---- create widgets ----
        self.label = Label(self, textvariable=self.textStatus)
        self.about = Label(self, text="About", fg="blue")
        self.text = Text(self, width=30, height=5, fg="grey")
        self.scrollbar = Scrollbar(self, orient="vertical", command=self.text.yview)
        self.loadButton = Button(self, text="Load", width=5, command=lambda: self.action("load"))
        self.readRadio = Radiobutton(self, text="Read", variable=self.mode, value=0, command=self.set_state)
        self.checkButton = Checkbutton(self, text="Use AES", variable=self.useEncryption, onvalue=1, offvalue=0, command=self.set_state)
        self.startButton = Button(self, text="Start", width=5, state="disabled", command=lambda: self.action("start"))
        self.writeRadio = Radiobutton(self, text="Write", variable=self.mode, value=1, command=self.set_state)
        self.keyEntry = Entry(self, width=10, fg="grey", show="*")
        # ---- show widgets ----
        self.label.grid(row=0, column=0, columnspan=2, sticky="w")
        self.about.grid(row=0, column=2, sticky="e")
        self.text.grid(row=1, column=0, rowspan=3, columnspan=3)
        self.scrollbar.grid(row=1, column=3, rowspan=3, sticky="ns")
        self.loadButton.grid(row=4, column=0, sticky="w", pady=5)
        self.readRadio.grid(row=4, column=1)
        self.checkButton.grid(row=4, column=2, sticky="e")
        self.startButton.grid(row=5, column=0, sticky="w")
        self.writeRadio.grid(row=5, column=1)
        self.keyEntry.grid(row=5, column=2, sticky="e")
        
    def behavior(self):
        """ Customize widgets. """
        self.text.config(yscrollcommand=self.scrollbar.set)
        self.text.insert(0.0, "Text here")
        self.keyEntry.insert(0, "Key here")
        self.text.bind("<Button>", self.handle_event)
        self.text.bind("<KeyRelease>", self.handle_event)
        self.keyEntry.bind("<Button>", self.handle_event)
        self.keyEntry.bind("<KeyRelease>", self.handle_event)
        self.textOpt = self.get_opt(self.text)
        self.keyOpt = self.get_opt(self.keyEntry)
        self.about.bind("<Button>", self.handle_event)
        self.set_state()
        
    def action(self, arg):
        """ What every button triggers. """
        if arg == "load":
            fileTypes = [("BMP", "*.bmp"), ("JPEG", ("*.jpeg", "*.jpg")), ("PNG", "*.png"), ("All Files", "*.*")]
            path = askopenfilename(parent=self, title="Open image", filetypes=fileTypes)
            if path != "":
                try:
                    self.totalBytes.set(app.load(path))
                except IOError as msg:
                    showerror("Error", str(msg).capitalize().strip(".") + ".") # some formatting
                else:
                    self.loaded = True
                    self.set_state()
                    self.master.title("Text In Image - %s" % app.name) # update name in title
        elif arg == "start":
            if self.mode.get():
                try:
                    app.write()
                except Exception as msg:
                    showerror("Error", str(msg).capitalize().strip(".") + ".")
                else:
                    showinfo("Info", "Done.")
            else:
                try:
                    string = app.read()
                except UnicodeError:
                    showerror("Error", "Text not found or wrong key.")
                except Exception as msg:
                    showerror("Error", str(msg).capitalize().strip(".") + ".")
                else:
                    self.text.config(state="normal")
                    self.textOpt["fg"] = "black" # touched
                    self.text.delete(0.0, END)
                    self.text.insert(0.0, string)
                    self.text.config(state="disabled")
                    self.usedBytes.set(app.parse_string(string))
                    self.set_status()
                    showinfo("Info", "Done.")
                    
    def set_status(self):
        """ Get used per total bytes. """
        string = "%9.3f%s/%9.3f%s"
        unit1 = unit2 = "b"
        used = self.usedBytes.get()
        total = self.totalBytes.get()
        if used > total:
            self.label.config(fg="red")
        else:
            self.label.config(fg="black")
        if used > 999999:
            unit1 = "Mb"
            used /= 1000000.0
        elif used > 999:
            unit1 = "Kb"
            used /= 1000.0
        if total > 999999:
            unit2 = "Mb"
            total /= 1000000.0
        elif total > 999:
            unit2 = "Kb"
            total /= 1000.0
        self.textStatus.set(string % (used, unit1, total, unit2))
        
    def get_opt(self, widget):
        """ Get some options from a widget then pack them. """
        opt = dict()
        opt["state"] = widget["state"]
        opt["fg"] = widget["fg"]
        opt["bg"] = widget["bg"]
        return opt
        
    def set_state(self):
        """ Enable or disable a widget according to option selected. """
        if self.mode.get(): # write
            self.text.config(**self.textOpt)
        else:
            self.text.config(state="disabled", bg="lightgrey", fg="darkgrey")
        if self.useEncryption.get(): # use AES
            self.keyEntry.config(**self.keyOpt)
            app.useAES = True
        else:
            self.keyEntry.config(state="disabled")
            app.useAES = False
        length = app.parse_string(app.tmp)
        self.usedBytes.set(length)
        self.set_status()
        if self.loaded: # a file is loaded
            if self.mode.get() == 0: # read mode
                ok = True
            elif app.data != None and self.usedBytes.get() <= self.totalBytes.get():
                ok = True
            else:
                ok = False
        else:
            ok = False # no file loaded
        if ok:
            self.startButton.config(state="normal")
        else:
            self.startButton.config(state="disabled")
                
    def handle_event(self, event):
        """ Handle events for specific widgets. """
        if event.widget is self.text and self.text["state"] == "normal":
            if self.text["fg"] == "grey":
                self.text.delete(0.0, END)
                self.textOpt["fg"] = self.text["fg"] = "black"
            string = self.text.get(0.0, END).strip()
            try:
                length = app.parse_string(string)
            except UnicodeError:
                showerror("Error", "Invalid text.")
            else:
                self.usedBytes.set(length)
                self.set_state()
        elif event.widget is self.keyEntry and self.keyEntry["state"] == "normal":
            if self.keyEntry["fg"] == "grey":
                self.keyEntry.delete(0, END)
                self.keyOpt["fg"] = self.keyEntry["fg"] = "black"
            key = self.keyEntry.get()[:32] # first 32 (max size is 32)
            try:
                length = app.parse_key(key)
            except UnicodeError:
                showerror("Error", "Invalid key.")
            else:
                self.usedBytes.set(length)
                self.set_state()
        elif event.widget is self.about:
            showinfo("About", "Hide text, which can be encrypted with AES, in pictures, preferably bitmaps. Coded by cmiN. Visit rstcenter.com")


if __name__ == "__main__":
    app = Engine() # core
    root = Tk() # toplevel
    root.title("Text In Image")
    root.maxsize(350, 250)
    root.iconbitmap("tii.ico") # comment if you don't have one
    GUI(root)
    root.mainloop()
