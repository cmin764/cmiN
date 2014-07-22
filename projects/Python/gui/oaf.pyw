#! /usr/bin/env python
# Oracle Answer Finder
# 02.05.2012 cmiN


from Tkinter import *
from urllib2 import build_opener, HTTPError, URLError
from urlparse import urlparse
from threading import Thread, Event
from socket import setdefaulttimeout, timeout


# constants
SMAX = 8 # maximum number of results
DIFF = 512 # how many chars to skip until the answer
TOUT = 2 # timeout in seconds


class GUI(Frame):

    def __init__(self, master=None, margin=10):
        Frame.__init__(self, master)
        self.app = Engine() # main app
        self.thread = None # Thread object used for parallel processing
        self.master.title("OAF - cmiN")
        self.grid(padx=margin, pady=margin)
        self.widgets()
        self.mainloop()

    def callback(self, event):
        """What happens after you press Enter in Question's entry."""
        # get and edit question
        qon = self.app.edit_qon(self.qEntry.get())
        if self.thread: # if it was initialized before
            # check question
            if qon == self.app.qon[0]: # same question (no reset)
                if self.thread.is_alive(): # let it finish
                    return
                else:
                    self.app.data = "" # empty buffer
                    self.app.dataLen = 0
            else: # another
                if self.thread.is_alive():
                    self.app.stop()
                    self.thread.join()
                self.app.reset() # reset everything
        # set question
        self.app.set_qon(qon)
        # process data
        self.thread = Thread(target=self.app.process)
        self.thread.start() # no return

    def widgets(self):
        # variables
        self.statusVar = StringVar(value="Ready.") # passed to Thread class for live updating
        #self.ansVar = StringVar() # same thing, but for answer
        self.app.statusVar = self.statusVar
        #self.app.ansVar = self.ansVar
        # label-entry pairs
        self.qLabel = Label(self, text="Question:")
        self.qEntry = Entry(self, width=100)
        self.aLabel = Label(self, text="Answer:")
        #self.aEntry = Entry(self, width=100, textvariable=self.ansVar)
        self.qLabel.grid(row=0, column=0, sticky="w")
        self.qEntry.grid(row=1, column=0)
        self.aLabel.grid(row=2, column=0, sticky="w")
        #self.aEntry.grid(row=3, column=0)
        # status widget
        self.sLabel1 = Label(self, text="Status:")
        self.sLabel2 = Label(self, width=86, textvariable=self.statusVar,
                             relief="sunken", bd=2, anchor="c")
        self.sLabel1.grid(row=4, column=0, sticky="w")
        self.sLabel2.grid(row=5, column=0, sticky="w")
        # text instead entry for answer
        self.ansText = Text(self, width=75, height=10)
        self.ansText.grid(row=3, column=0)
        self.app.ansText = self.ansText # make it available to the engine
        # behavior
        self.qEntry.bind("<Return>", self.callback)
        self.qEntry.bind("<KP_Enter>", self.callback)


class Engine:

    def __init__(self):
        setdefaulttimeout(TOUT)
        self.opener = build_opener()
        self.opener.addheaders = [("User-agent", "Mozilla/5.0")]
        self.qon = ["", ""] # question
        self.data = "" # data contain the question [and answer]
        self.dataLen = 0 # data length
        self.start = 0 # google first result
        self.first = "url?q=" # from
        self.second = "&amp" # to
        self.seen = set() # evidence of visited links
        self.statusVar = None # through this set status
        self.ansVar = None # through this set answer if available
        self.ansText = None # almost same shit
        self.__stop = Event() # stop the process
        self.upEvent = Event() # solve the deadlock
        self.upEvent.set() # means it's safe (.wait will wait until .set is called or .is_set() is True)

    def update(self, status, answer):
        """Here is a fucking deadlock, when the same function is called simultaneously."""
        self.upEvent.wait() # wait to be setted
        self.upEvent.clear() # make it busy
        # do your ugly things
        if hasattr(self.statusVar, "set") and hasattr(self.statusVar, "get"):
            self.statusVar.set(status)
            self.statusVar.get() # just to make sure the update finished
        if hasattr(self.ansVar, "set") and hasattr(self.ansVar, "get"):
            self.ansVar.set(answer)
            self.ansVar.get()
        if hasattr(self.ansText, "insert") and hasattr(self.ansText, "delete"):
            self.ansText.delete(0.0, END)
            self.ansText.insert(0.0, answer)
        self.upEvent.set() # make it available

    def stop(self):
        self.update("Stopping...", "")
        self.__stop.set()

    def stopped(self):
        return self.__stop.is_set()

    def reset(self):
        self.__stop.clear()
        self.start = 0
        self.seen = set()
        #self.update("Ready.", "")

    def edit_qon(self, qon):
        return qon.strip().split("\n")[0] # idiot proof

    def set_qon(self, qon):
        """Set question."""
        self.qon[0] = qon
        self.qon[1] = '"' + self.qon[0].replace(" ", "+") + '"'

    def find(self):
        """Find links corresponding to query using google.

        Returns:
            0 -> match, link extracted, data updated
            1 -> no match for exact string
            2 -> url already visited or invalid url
            3 -> banned
            4 -> maximum number of results exceeded
        """
        if self.start >= SMAX:
            return 4
        link = "http://www.google.com/search?q={}&start={}".format(self.qon[1], self.start)
        try:
            fobj = self.opener.open(link)
        except HTTPError:
            self.update("Google banned you.", "")
            return 3
        except timeout:
            self.update("Timed out or Google banned you.", "")
            return 3
        else:
            data = fobj.read() # google's source
            fobj.close()
        # find a relevant closest position to the link
        index1 = data.find(self.first)
        if index1 == -1: # no results in page or modified pattern
            return 1 # invalid source
        self.start += 1 # now do the increment
        index1 += len(self.first)
        index2 = data.find(self.second, index1)
        url = data[index1:index2]
        # edit url
        newurl = ""
        i = 0
        length = len(url)
        while i < length:
            if url[i] == "%":
                char = chr(int(url[i + 1] + url[i + 2], 16))
                i += 2
            else:
                char = url[i]
            newurl += char
            i += 1
        url = newurl
        # process it
        if url in self.seen: # link already visited
            return 2
        self.seen.add(url)
        upo = urlparse(url)
        self.update("Looking in %s..." % upo.netloc, "")
        try:
            fobj = self.opener.open(url)
        except URLError:
            self.update("Invalid link.", "")
            return 2
        except timeout:
            self.update("Timed out.", "")
            return 3
        else:
            self.data = fobj.read()
            self.dataLen = len(self.data)
            fobj.close()
        return 0 # all fine

    def check(self, old, index):
        if index < 0 or index >= self.dataLen:
            return False # invalid index
        if abs(old - index) > DIFF:
            return False # too far
        return True # ok

    def get_star(self, index):
        """Find the line with (*).

        Returns:
            str -> good answer
            False -> invalid answer or couldn't find
        """
        ansNr = 1 # default answers (for multiple ones)
        chunk = "(Choose "
        firstTag = self.data.find("<", index)
        chunkIndex = self.data.find(chunk, index, firstTag)
        if chunkIndex != -1:
            chunkIndex += len(chunk)
            number = ""
            while self.data[chunkIndex] != ")":
                number += self.data[chunkIndex]
                chunkIndex += 1
            number = number.strip().lower()
            if number == "two":
                ansNr = 2
            elif number == "three":
                ansNr = 3
            elif number == "four":
                ansNr = 4 # i don't think this actually exists :)
        star = "(*)"
        last = index
        ans = ""
        while ansNr:
            index = self.data.find(star, last) - 1
            last = index + 1 + len(star)
            if index < 0:
                return False # invalid answer type
            # ok now we're good
            old = index
            while True:
                tag = True
                while self.data[index] != ">":
                    if tag and self.data[index].isspace():
                        index -= 1
                        continue
                    if tag:
                        ans = "\n" + ans
                        tag = False # found alphanumeric
                    ans = self.data[index] + ans
                    index -= 1
                    if not self.check(old, index):
                        return False
                ans = ans.strip()
                if tag and len(ans) > 0:
                    break
                while self.data[index] != "<":
                    index -= 1
                index -= 1
            ansNr -= 1
            ans = "\n" + ans
        return ans.strip()

    def get_single(self, index):
        """Line with single answer.

        Returns:
            str -> good answer
            False -> invalid answer or couldn't find
        """
        new = True # first answer (if multiple)
        ans = ""
        smooth = 1 # tag number difference
        while True:
            old = index
            # go to the first tag
            while self.data[index] != "<":
                index += 1
                if not self.check(old, index):
                    return False
            # no skip all of them
            nrTag = 0
            while self.data[index] == "<":
                while self.data[index] != ">":
                    index += 1
                index += 1
                nrTag += 1 # add tag
                if not self.check(old, index):
                    return False
            if new:
                new = False # not new anymore
                model = nrTag
            if abs(nrTag - model) > smooth:
                break # no incoming answers to this question
            while self.data[index] != "<":
                ans += self.data[index]
                index += 1
                if not self.check(old, index):
                    return False
            # add separator (don't worry, we will strip it at the end)
            ans = ans.strip() + "\n\n"
        ans = ans.strip()
        if ans == "":
            return False # empty one
        return ans

    def process(self):
        """Try to find answers to quiz questions by searching them on google.

        Format string, search it on google, locate first %d results,
        then search among them for patterns (question<>...<>answer<> or question<>answer...(*)<>).

        Returns:
            str -> answer found (or false positive)
              1 -> invalid/inexistent question (or google invalid source pattern)
              2 -> answer not found (or different search pattern)
              3 -> stopped
              4 -> banned
        """ % SMAX
        ret = 0 # virtual return
        while True:
            if self.stopped():
                return 3 # stopped
            if ret == 1:
                self.update("Invalid question.", "")
                return 1 # invalid question
            elif ret == 2: # already seen or invalid
                ret = self.find()
                continue
            elif ret == 3:
                return 4 # timed out or banned (too many queries)
            elif ret == 4:
                self.update("Nothing found.", "")
                return 2 # not found
            index = self.data.find(self.qon[0])
            if index >= 0:
                #index += len(self.qon[0]) # conflict with star (need some data from question)
                ans = self.get_star(index)
                if not ans:
                    ans = self.get_single(index)
                if ans:
                    self.update("Answer found!", ans)
                    return ans # string ok
            ret = self.find()


if __name__ == "__main__":
    GUI(Tk())
