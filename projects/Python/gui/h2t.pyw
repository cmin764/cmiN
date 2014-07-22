#! /usr/bin/env python
# 08.02.2009 <-> 08.02.2009 | cmiN
# non-standard modules = ( Pmw )

from Tkinter import *
import tkFont, tkMessageBox, hashlib, time, Pmw



def frames():
    global root, Font, _Font, img
    root=Tk()
    Font=tkFont.Font(family='Comic Sans MS', size=10, weight='bold')
    _Font=tkFont.Font(family='Comic Sans MS', size=8, weight='bold')
    img=PhotoImage(file='rst.gif')
    frame=Frame(root)
    frame.option_add('*font', Font)        



def create_widgets():
    global entry1, var1, var2, cb1, cb2, cb3, cvar1, cvar2, cvar3, cvar4, bvar
    canvas=Canvas(width=600, height=92)
    canvas.grid(row=0, column=0)
    canvas.create_image(0, 0, image=img, anchor='nw')

    message1=Label(text='Hash: ')
    message1.grid(row=1, column=0)

    xscrollbar1=Scrollbar(orient=HORIZONTAL, command=scrollHandler1)
    xscrollbar1.grid(row=3, column=0, ipadx='178')
    var1=StringVar()
    entry1=Entry(textvariable=var1, width=50, state=NORMAL,
                 bg='white', fg='black', xscrollcommand=xscrollbar1.set)
    entry1.grid(row=2, column=0)

    message2=Label(text='Text: ')
    message2.grid(row=4, column=0)

    var2=StringVar()
    entry2=Entry(textvariable=var2, width=50, state=DISABLED, fg='red')
    entry2.grid(row=5, column=0)

    cb1=Pmw.ComboBox(label_text='Hash: ', labelpos='nw', entry_insertontime=0,
                     scrolledlist_items=table_hash, entry_width=15)
    cb1.grid(sticky='sw', row=6, column=0, pady=15)
    cb1.selectitem(table_hash[0])

    cb2=Pmw.ComboBox(label_text='From: ', labelpos='nw', entry_insertontime=0,
                     scrolledlist_items=characters, entry_width=15)
    cb2.grid(sticky='s', row=6, column=0, pady=15)
    cb2.selectitem(characters[0])

    cb3=Pmw.ComboBox(label_text='To: ', labelpos='nw', entry_insertontime=0,
                     scrolledlist_items=characters, entry_width=15)
    cb3.grid(sticky='se', row=6, column=0, pady=15)
    cb3.selectitem(characters[0])

    cvar1=IntVar()
    check1=Checkbutton(text='a-z (26)', variable=cvar1)
    check1.grid(row=7, column=0, sticky='sw', padx=150)

    cvar2=IntVar()
    check2=Checkbutton(text='A-Z (26)', variable=cvar2)
    check2.grid(row=8, column=0, sticky='sw', padx=150)

    cvar3=IntVar()
    check3=Checkbutton(text='0-9 (10)', variable=cvar3)
    check3.grid(row=7, column=0, sticky='se', padx=150)

    cvar4=IntVar()
    check4=Checkbutton(text='`-? (32)', variable=cvar4)
    check4.grid(row=8, column=0, sticky='se', padx=150)

    bvar=StringVar()
    button1=Button(textvariable=bvar, command=process)
    button1.grid(sticky='s', row=9, column=0, pady=10)
    bvar.set('   Decrypt   ')



def scrollHandler1(*args):
    op, howMany=args[0], args[1]
    if op=='scroll':
        units=args[2]
        entry1.xview_scroll(howMany, units)
    elif op=='moveto':
        entry1.xview_moveto(howMany)



def tables():
    global table_hash, table_1, table_2, table_3, table_4, characters
    
    table_hash=['md2', 'md4', 'md5', 'sha1', 'sha224', 'sha256', 'sha384', 'sha512', 'ripemd']

    table_1=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
             'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

    table_2=['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
             'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

    table_3=['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

    table_4=['`', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-',
             '_', '=', '+', '|', '[', '{', ']', '}', ';', ':', "'", '"', ',', '<', '.', '>', '/', '?', ' ']

    characters=['1', '2', '3', '4', '5', '6', '7', '8', '9', '10']



def decrypt():
        global statement

        table=[]
        if cvar1.get()==1:
            table=table+table_1
        if cvar2.get()==1:
            table=table+table_2
        if cvar3.get()==1:
            table=table+table_3
        if cvar4.get()==1:
            table=table+table_4
        while int(cb2.get()) <= int(cb3.get()):
            for x in table:
                word1=x
                if encrypt(word1) is True:
                    var2.set(word1)
                    statement=True
                    return
                for x in table:
                    if int(cb2.get()) >1:
                        word2=word1+x
                        if encrypt(word2) is True:
                            var2.set(word2)
                            statement=True
                            return
                        for x in table:
                            if int(cb2.get()) >2:
                                word3=word2+x
                                if encrypt(word3) is True:
                                    var2.set(word3)
                                    statement=True
                                    return
                                for x in table:
                                    if int(cb2.get()) >3:
                                        word4=word3+x
                                        if encrypt(word4) is True:
                                            var2.set(word4)
                                            statement=True
                                            return
                                        for x in table:
                                            if int(cb2.get()) >4:
                                                word5=word4+x
                                                if encrypt(word5) is True:
                                                    var2.set(word5)
                                                    statement=True
                                                    return
                                                for x in table:
                                                    if int(cb2.get()) >5:
                                                        word6=word5+x
                                                        if encrypt(word6) is True:
                                                            var2.set(word6)
                                                            statement=True
                                                            return
                                                        for x in table:
                                                            if int(cb2.get()) >6:
                                                                word7=word6+x
                                                                if encrypt(word7) is True:
                                                                    var2.set(word7)
                                                                    statement=True
                                                                    return
                                                                for x in table:
                                                                    if int(cb2.get()) >7:
                                                                        word8=word7+x
                                                                        if encrypt(word8) is True:
                                                                            var2.set(word8)
                                                                            statement=True
                                                                            return
                                                                        for x in table:
                                                                            if int(cb2.get()) >8:
                                                                                word9=word8+x
                                                                                if encrypt(word9) is True:
                                                                                    var2.set(word9)
                                                                                    statement=True
                                                                                    return
                                                                                for x in table:
                                                                                    if int(cb2.get()) >9:
                                                                                        word10=word9+x
                                                                                        if encrypt(word10) is True:
                                                                                            var2.set(word10)
                                                                                            statement=True
                                                                                            return
                                                                                    else:
                                                                                        break
                                                                            else:
                                                                                break
                                                                    else:
                                                                        break
                                                            else:
                                                                break
                                                    else:
                                                        break
                                            else:
                                                break
                                    else:
                                        break
                            else:
                                break
                    else:
                        break
            if cb2.get()==cb3.get():
                return
            else:
                cb2.selectitem(str(int(cb2.get())+1))
        
                    

def encrypt(string):
    hash=hashlib.new(cb1.get(), string).hexdigest()
    if hash==var1.get():
        return True
    else:
        return False



def process():
    global statement
    statement=False
    
    if not cb1.get() in table_hash or not cb2.get() in characters or not cb3.get() in characters:
        tkMessageBox.showerror(title='Error', message='Hash type or string length is incorrect!')
        return
    elif cvar1.get()==0 and cvar2.get()==0 and cvar3.get()==0 and cvar4.get()==0:
        tkMessageBox.showerror(title='Error', message='You must check at least one box!')
        return
    elif var1.get()=='':
        tkMessageBox.showerror(title='Error', message="The hash field mustn't be empty!")
        return
    elif int(cb2.get()) > int(cb3.get()):
        tkMessageBox.showerror(title='Error', message="The initial string length mustn't be greater than the final string length!")
        return
    decrypt()
    if statement is True:
        tkMessageBox.showinfo(title='Info', message='The process finished and finded a match!')
    else:
        tkMessageBox.showinfo(title='Info', message='The process finished without match.')
    


def end():
    root.title('Hash2Text')
    root.minsize(603, 400)
    root.maxsize(603, 400)
    root.mainloop()
    


tables()
frames()
create_widgets()
end()
