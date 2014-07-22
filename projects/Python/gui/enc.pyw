#! /usr/bin/env python
# 24.01.2009 <-> 02.02.2009 | cmiN
# non-standard modules = ( Crypto , Pmw  )
# updated to 02.05.2009


from Tkinter import *
from Crypto.Cipher import AES, DES, DES3, ARC2, ARC4, Blowfish, CAST, IDEA, RC5, XOR
import tkFont, tkMessageBox, tkFileDialog, hashlib, zlib, base64, yahoo64, binascii, Pmw, hmac


def frames():
    global root, Font, _Font
    root=Tk()
    frame=Frame(root)
    menu=Menu(root)
    root.config(menu=menu)
    filemenu=Menu(menu)
    menu.add_cascade(label='File', menu=filemenu)
    filemenu.add_command(label='Open...', command=open_txt)
    filemenu.add_separator()
    filemenu.add_command(label='Exit', command=bye)
    helpmenu=Menu(menu)
    menu.add_cascade(label='Help', menu=helpmenu)
    helpmenu.add_command(label='About', command=msgbox1)
    Font=tkFont.Font(family='Comic Sans MS', size=8, weight='bold')
    _Font=tkFont.Font(family='Comic Sans MS', size=8, weight='normal')
    frame.option_add('*font', Font)



def create_widgets():
    global text1, text2, var1, var2, var3, rb1, rb2, cb1, cb2, entry1, decryption_list, encryption_list, txt, hex_list, key_list, status

    try:
        txt
    except NameError:
        txt='None'
        
 
    hex_list=('md2', 'md4', 'md5', 'sha1', 'sha224', 'sha256', 'sha384', 'sha512', 'ripemd', 'HMAC')
    key_list=('HMAC', 'AES', 'ARC2', 'ARC4', 'Blowfish', 'CAST', 'DES', 'DES3', 'IDEA', 'RC5', 'XOR')
    
    message1=Label(text='From: ')
    message1.grid(row=0, column=0)

    yscrollbar1=Scrollbar(orient=VERTICAL, command=scrollHandler1)
    yscrollbar1.grid(row=1, column=2, ipady='22')
    text1=Text(fg='grey', bg='white', yscrollcommand=yscrollbar1.set, state=NORMAL, width='30', height='6', font=_Font, takefocus=1)
    text1.grid(row=1, column=1)
    text1.insert(0.0, 'Enter text here...')
    text1.bind('<Button-1>', clear_text)
    text1.bind('<Key>', clear_text)
    text1.focus()

    message2=Label(text='To:   ')
    message2.grid(row=2, column=0)

    yscrollbar2=Scrollbar(orient=VERTICAL, command=scrollHandler2)
    yscrollbar2.grid(row=3, column=2, ipady='22')
    text2=Text(fg='red', bg='grey', yscrollcommand=yscrollbar2.set, state=DISABLED, width='30', height='6', font=_Font)
    text2.grid(row=3, column=1)

    var1=IntVar()
    rb1=Radiobutton(text='Hexdigest', value=1, variable=var1, state=DISABLED, takefocus=0, command=enable_if_hex)
    rb2=Radiobutton(text='Digest    ', value=0, variable=var1, state=DISABLED, takefocus=0, command=enable_if_hex)
    rb1.grid(row=4, column=0)
    rb2.grid(row=5, column=0)
    var1.set(1)

    dencryption_list=('PlainText', 'key', 'word', 'base16', 'base32', 'base64', "yahoo64", 'zlib', 'rot13', 'hqx', 'uu',
                       'AES', 'DES', 'DES3', 'ARC2', 'ARC4', 'Blowfish', 'CAST', 'IDEA', 'RC5', 'XOR',
                      'ord', 'hex', 'oct', 'bin', 'html', 'SkiddyFlama', 'Inglish') ##
    cb1=Pmw.ComboBox(label_text='From: ', labelpos='nw', entry_insertontime=0, entry_state=NORMAL,
                     scrolledlist_items=dencryption_list, selectioncommand=enable_if_hex, entry_width=11)
    cb1.grid(sticky='nw', row=4, column=1)
    cb1.selectitem(dencryption_list[0])

    encryption_list=('PlainText', 'md2', 'md4', 'md5', 'sha1', 'sha224', 'sha256', 'sha384', 'sha512', 'ripemd',
                     'HMAC', 'base16', 'base32', 'base64', "yahoo64", 'adler32', 'crc32', 'crc_hqx', 'zlib', 'rot13',
                     'hqx', 'uu', 'AES', 'DES', 'DES3', 'ARC2', 'ARC4', 'Blowfish', 'CAST', 'IDEA', 'RC5', 'XOR',
                     'ord', 'hex', 'oct', 'bin', 'html', 'SkiddyFlama', 'Inglish') ##
    cb2=Pmw.ComboBox(label_text='To: ', labelpos='nw', entry_insertontime=0, entry_state=NORMAL,
                     scrolledlist_items=encryption_list, selectioncommand=enable_if_hex, entry_width=11)
    cb2.grid(sticky='ne', row=4, column=1)
    cb2.selectitem(encryption_list[0])

    b1=Button(text=' Exit ', command=bye)
    b1.grid(sticky='se', row=6, column=0, pady=10)

    message5=Label(text='Key: ')
    message5.grid(sticky='n' ,row=6, column=1)

    var3=StringVar()
    entry1=Entry(textvariable=var3, bg='white', fg='blue', width=25, state=DISABLED)
    entry1.grid(sticky='s' ,row=6, column=1, pady=10)
    var3.set('')
    
    b2=Button(text='Convert', command=convert)
    b2.grid(sticky='sw', row=6, column=2, pady=10)

    var2=StringVar()
    var2.set(' Waiting...')
    status=Pmw.MessageBar(entry_width=30, entry_relief="groove",
                          labelpos="n", label_text="Status:")
    status.grid(sticky='n', row=7, column=1)
    status.message('systemevent', var2.get())



def enable_if_hex(*args):
    if cb2.get() in hex_list:
        rb1['state']=NORMAL
        rb2['state']=NORMAL
    else:
        rb1['state']=DISABLED
        rb2['state']=DISABLED
    if cb1.get() in key_list or cb2.get() in key_list:
        entry1['state']=NORMAL
    else:
        entry1['state']=DISABLED
    var2.set(' Waiting...')
    status.message('systemevent', var2.get())



def open_txt():
    global txt
    txt='None'
    ftypes=[('Text Documents', '*.txt'), ('Word Documents', '*.doc'), ('XML Files', '*.xml')]
    txt_list=None
    try:
        txt_list=tkFileDialog.askopenfile(parent=root, mode='r', title='Chose a text based file', filetypes=ftypes)
        txt=txt_list.readlines()
    except:
        if txt_list is None:
            var2.set(' Cancelled!')
            status.message('systemevent', var2.get())
        else:
            tkMessageBox.showerror('File Error', 'Failed to open file!')
    else:
        var2.set(' List ready')
        status.message('systemevent', var2.get())



def convert():
    ## some settings
    var2.set(' Please wait...')
    status.message('systemevent', var2.get())
    statement2=False
    var4=IntVar()
    var4.set(0)

    ## filter
    brute=text1.get(0.0, END)
    brute_list=[]
    brute_list[len(brute_list):]=brute
    final=''
    statement=True
    while statement is True:
        try:
            brute_list.remove('\n')
        except:
            statement=False
        else:
            continue
    for x in brute_list:
        final=final+x
    
    ## decryption
    try:
        if cb1.get()=='PlainText':
            decrypted=final
        elif cb1.get() in ('key', 'word'):
            statement=False
            for kw in txt:
                _decrypted=kw.strip('\n')
                _decrypted=_decrypted.split(':')
                if len(_decrypted) != 2:
                    var2.set(' Invalid file or list!')
                    status.message('systemevent', var2.get())
                    return
                else:
                    if cb1.get()=='key':
                        if _decrypted[0]==final:
                            decrypted=_decrypted[1]
                            statement=True
                    else:
                        if _decrypted[1]==final:
                            decrypted=_decrypted[0]
                            statement=True
            if statement is False:
                var2.set(' Nothing finded.')
                status.message('systemevent', var2.get())
                return
        elif cb1.get()=='base16':
            decrypted=base64.b16decode(final)
        elif cb1.get()=='base32':
            decrypted=base64.b32decode(final)
        elif cb1.get()=='base64':
            decrypted=base64.b64decode(final)
        elif cb1.get()=="yahoo64":
            decrypted=yahoo64.decode(final)
        elif cb1.get()=='zlib':
            _decrypted=final.split()
            decrypted=''
            for x in _decrypted:
                decrypted=decrypted+chr(int(x, 16))
            decrypted=zlib.decompress(decrypted)
        elif cb1.get() in ('html' ,'ord', 'hex', 'oct', 'bin'):
            _decrypted=final.split()
            decrypted=''
            if cb1.get()=='html':
                _decrypted=final.split('&#')
                _decrypted.remove('')
            for x in _decrypted:
                if cb1.get() in ('ord', 'html'):
                    decrypted=decrypted+chr(int(x, 10))
                elif cb1.get()=='hex':
                    decrypted=decrypted+chr(int(x, 16))
                elif cb1.get()=='oct':
                    decrypted=decrypted+chr(int(x, 8))
                else:
                    decrypted=decrypted+chr(int(x, 2))
        elif cb1.get()=='hqx':
            decrypted=binascii.a2b_hqx(final)[0]
        elif cb1.get()=='uu':
            decrypted=binascii.a2b_uu(final)
        elif cb1.get()=='rot13':
            _decrypted=[]
            _decrypted[:]=final
            decrypted=''
            keys=rot13_table.keys()
            for char in _decrypted:
                statement=False
                for key in keys:
                    if char==key:
                        decrypted=decrypted+rot13_table[key]
                        statement=True
                        break
                    elif char==rot13_table[key]:
                        decrypted=decrypted+key
                        statement=True
                        break
                if statement is False:
                    decrypted=decrypted+char
        elif cb1.get()=='SkiddyFlama':
            decrypted=final
            for z, x in SkiddyFlama_table:
                decrypted=decrypted.replace(x, z)
            _decrypted=[]
            _decrypted[:]=decrypted
            for char in _decrypted:
                if char in sign_table:
                    nr=_decrypted.index(char)
                    _decrypted[nr-1:nr]=''
            decrypted=''
            for x in _decrypted:
                decrypted=decrypted+x
        elif cb1.get()=='Inglish':
            decrypted=final
            for z, x in Inglish_table:
                decrypted=decrypted.replace(x, z)
        elif cb1.get() in key_list[1:]:
            _final=final.split()
            final=''
            for x in _final:
                final=final+chr(int(x, 16))
            if cb1.get()=='AES':
                if not len(var3.get()) in (16, 24, 32):
                    var2.set(' "Key" length must be 16/24/32.')
                    status.message('systemevent', var2.get())
                    return
                else:
                    aes=AES.new(var3.get(), 1)
                    decrypted=aes.decrypt(final)
            elif cb1.get()=='ARC2':
                if len(var3.get())==0:
                    var2.set(' "Key" length '+"mustn't"+' be 0!')
                    status.message('systemevent', var2.get())
                    return
                else:
                    arc2=ARC2.new(var3.get(), 1)
                    decrypted=arc2.decrypt(final)
            elif cb1.get()=='ARC4':
                if len(var3.get())==0:
                    var2.set(' "Key" length '+"mustn't"+' be 0!')
                    status.message('systemevent', var2.get())
                    return
                else:
                    arc4=ARC4.new(var3.get())
                    decrypted=arc4.decrypt(final)
            elif cb1.get()=='Blowfish':
                if len(var3.get())==0:
                    var2.set(' "Key" length '+"mustn't"+' be 0!')
                    status.message('systemevent', var2.get())
                    return
                else:
                    blowfish=Blowfish.new(var3.get(), 1)
                    decrypted=blowfish.decrypt(final)
            elif cb1.get()=='CAST':
                if not len(var3.get()) in range(5, 17):
                    var2.set(' "Key" length must be 4< and <17.')
                    status.message('systemevent', var2.get())
                    return
                else:
                    cast=CAST.new(var3.get(), 1)
                    decrypted=cast.decrypt(final)
            elif cb1.get()=='DES':
                if not len(var3.get())==8:
                    var2.set(' "Key" length must be 8.')
                    status.message('systemevent', var2.get())
                    return
                else:
                    des=DES.new(var3.get(), 1)
                    decrypted=des.decrypt(final)
            elif cb1.get()=='DES3':
                if not len(var3.get()) in (16, 24):
                    var2.set(' "Key" length must be 16/24.')
                    status.message('systemevent', var2.get())
                    return
                else:
                    des3=DES3.new(var3.get(), 1)
                    decrypted=des3.decrypt(final)
            elif cb1.get()=='IDEA':
                if not len(var3.get())==16:
                    var2.set(' "key" length must be 16.')
                    status.message('systemevent', var2.get())
                    return
                else:
                    idea=IDEA.new(var3.get(), 1)
                    decrypted=idea.decrypt(final)
            elif cb1.get()=='RC5':
                if len(var3.get()) in (0, 1):
                    var2.set(' "Key" length '+"mustn't"+' be 0/1!')
                    status.message('systemevent', var2.get())
                    return
                else:
                    rc5=RC5.new(var3.get(), 1)
                    decrypted=rc5.decrypt(final)
            elif cb1.get()=='XOR':
                if not len(var3.get()) in range(1, 5):
                    var2.set(' "Key" length must be 0< and <5.')
                    status.message('systemevent', var2.get())
                    return
                else:
                    xor=XOR.new(var3.get())
                    decrypted=xor.decrypt(final)
        else:
            var2.set(' Invalid decryption method!')
            status.message('systemevent', var2.get())
            return
    except:
        var2.set(' Invalid inputted text!')
        status.message('systemevent', var2.get())
        return

    ## encryption
    if cb2.get() in hex_list:
        if var1.get()==0:
            if cb2.get()=='HMAC':
                _encrypted=hmac.new(var3.get(), msg=decrypted).digest()
            else:
                _encrypted=hashlib.new(cb2.get(), decrypted).digest()   # in 3.0 must be u''+decrypted
            encrypted=''
            for char in _encrypted:
                z=str(ord(char))
                while len(z)<3:
                    z="0"+z
                encrypted=encrypted+z+' '
            encrypted=encrypted.strip()
        else:
            if cb2.get()=='HMAC':
                encrypted=hmac.new(var3.get(), msg=decrypted).hexdigest()
            else:
                encrypted=hashlib.new(cb2.get(), decrypted).hexdigest()
    elif cb2.get()=='PlainText':
        encrypted=decrypted
    elif cb2.get()=='base16':
        encrypted=base64.b16encode(decrypted)
    elif cb2.get()=='base32':
        encrypted=base64.b32encode(decrypted)
    elif cb2.get()=='base64':
        encrypted=base64.b64encode(decrypted)
    elif cb2.get()=="yahoo64":
        encrypted=yahoo64.encode(decrypted)
    elif cb2.get()=='adler32':
        encrypted=zlib.adler32(decrypted)
    elif cb2.get()=='crc32':
        encrypted=zlib.crc32(decrypted)
    elif cb2.get()=='crc_hqx':
        encrypted=binascii.crc_hqx(decrypted, binascii.crc32(decrypted))
    elif cb2.get()=='zlib':
        _encrypted=zlib.compress(decrypted)
        encrypted=''
        for char in _encrypted:
            encrypted=encrypted+str(hex(ord(char))).replace("0x", " ")
        _encrypted=encrypted.strip()
        encrypted=""
        _encrypted=_encrypted.split(" ")
        for x in range(0, len(_encrypted)):
            if len(_encrypted[x])!=2:
                _encrypted[x]="0"+_encrypted[x]
            encrypted=encrypted+_encrypted[x]+" "
        encrypted=encrypted.strip()
    elif cb2.get() in ('html', 'ord', 'hex', 'oct', 'bin'):
        _encrypted=[]
        _encrypted[:]=decrypted
        encrypted=''
        for char in _encrypted:
            if cb2.get()=='html':
                z=str(ord(char))
                while len(z)<3:
                    z="0"+z
                encrypted=encrypted+"&#"+z
            elif cb2.get()=='ord':
                z=str(ord(char))
                while len(z)<3:
                    z="0"+z
                encrypted=encrypted+z+" "
            elif cb2.get()=='hex':
                z=str(hex(ord(char))).replace('0x', '')
                while len(z)<2:
                    z="0"+z
                encrypted=encrypted+z+" "
            elif cb2.get()=='oct':
                z=str(oct(ord(char)))
                while len(z)<4:
                    z="0"+z
                encrypted=encrypted+z+" "
            else:
                z=str(bin(ord(char))).replace('b', '')
                while len(z)<8:
                    z='0'+z
                encrypted=encrypted+z+' '
        encrypted=encrypted.strip()
    elif cb2.get()=='hqx':
        encrypted=binascii.b2a_hqx(decrypted)
    elif cb2.get()=='uu':
        if len(decrypted) < 46:
            encrypted=binascii.b2a_uu(decrypted)
        else:
            var2.set(' Maximum string length must be 45!')
            status.message('systemevent', var2.get())
            return
    elif cb2.get()=='rot13':
        _encrypted=[]
        _encrypted[:]=decrypted
        encrypted=''
        keys=rot13_table.keys()
        for char in _encrypted:
            statement=False
            for key in keys:
                if char==key:
                    encrypted=encrypted+rot13_table[key]
                    statement=True
                    break
                elif char==rot13_table[key]:
                    encrypted=encrypted+key
                    statement=True
                    break
            if statement is False:
                encrypted=encrypted+char
    elif cb2.get()=='SkiddyFlama':
        encrypted=decrypted
        for x, z in SkiddyFlama_table:
            encrypted=encrypted.replace(x, z)
        _encrypted=[]
        _encrypted[:]=encrypted
        for char in _encrypted:
            if char in sign_table:
                nr=_encrypted.index(char)
                _encrypted[nr]=' '+_encrypted[nr]
        encrypted=''
        for x in _encrypted:
            encrypted=encrypted+x
    elif cb2.get()=='Inglish':
        encrypted=decrypted
        for x, z in Inglish_table:
            encrypted=encrypted.replace(x, z)
    elif cb2.get() in key_list[1:]:
        if cb2.get()=='AES':
            if len(var3.get()) in (16, 24, 32):
                aes=AES.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=aes.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        var4.set(var4.get()+1)
                        decrypted=decrypted+' '
            else:
                var2.set(' "Key" length must be 16/24/32.')
                status.message('systemevent', var2.get())
                return
        elif cb2.get()=='ARC2':
            if len(var3.get())==0:
                var2.set(' "Key" length '+"mustn't"+' be 0!')
                status.message('systemevent', var2.get())
                return
            else:
                arc2=ARC2.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=arc2.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='ARC4':
            if len(var3.get())==0:
                var2.set(' "Key" length '+"mustn't"+' be 0!')
                status.message('systemevent', var2.get())
                return
            else:
                arc4=ARC4.new(var3.get())
                _encrypted=arc4.encrypt(decrypted)
        elif cb2.get()=='Blowfish':
            if len(var3.get())==0:
                var2.set(' "Key" length '+"mustn't"+' be 0!')
                status.message('systemevent', var2.get())
                return
            else:
                blowfish=Blowfish.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=blowfish.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='CAST':
            if not len(var3.get()) in range(5, 17):
                var2.set(' "Key" length must be 4< and <17.')
                status.message('systemevent', var2.get())
                return
            else:
                cast=CAST.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=cast.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='DES':
            if not len(var3.get())==8:
                var2.set(' "Key" length must be 8.')
                status.message('systemevent', var2.get())
                return
            else:
                des=DES.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=des.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='DES3':
            if not len(var3.get()) in (16, 24):
                var2.set(' "Key" length must be 16/24.')
                status.message('systemevent', var2.get())
                return
            else:
                des3=DES3.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=des3.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='IDEA':
            if not len(var3.get())==16:
                var2.set(' "key" length must be 16.')
                status.message('systemevent', var2.get())
                return
            else:
                idea=IDEA.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=idea.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='RC5':
            if len(var3.get()) in (0, 1):
                var2.set(' "Key" length '+"mustn't"+' be 0/1!')
                status.message('systemevent', var2.get())
                return
            else:
                rc5=RC5.new(var3.get(), 1)
                statement=False
                while statement is False:
                    try:
                        _encrypted=rc5.encrypt(decrypted)
                        statement=True
                    except:
                        statement2=True
                        decrypted=decrypted+' '
                        var4.set(var4.get()+1)
        elif cb2.get()=='XOR':
            if not len(var3.get()) in range(1, 5):
                var2.set(' "Key" length must be 0< and <5.')
                status.message('systemevent', var2.get())
                return
            else:
                xor=XOR.new(var3.get())
                _encrypted=xor.encrypt(decrypted)
        encrypted=''
        for x in _encrypted:
            z=str(hex(ord(x))).replace("0x", "")
            while len(z)<2:
                z="0"+z
            encrypted=encrypted+z+" "
        encrypted=encrypted.strip()
    else:
        var2.set(' Invalid encryption method!')
        status.message('systemevent', var2.get())
        return
            
    ## print
    text2['state']=NORMAL
    text2.delete(0.0, END)
    text2.insert(0.0, encrypted)
    text2['state']=DISABLED
    if statement2 is False:
        var2.set(' The operation completed successfully!')
        status.message('systemevent', var2.get())
    else:
        var2.set(' Were added '+str(var4.get())+' space(s) to the text.')
        status.message('systemevent', var2.get())


        
def clear_text(event):
    text1['fg']='black'
    if text1.get(0.0, END)=='Enter text here...\n':
        text1.delete(0.0, END)



def scrollHandler1(*L):
    op, howMany = L[0], L[1]
    if op=="scroll":
        units=L[2]
        text1.yview_scroll(howMany, units)
    elif op=="moveto":
        text1.yview_moveto(howMany)



def scrollHandler2(*L):
    op, howMany = L[0], L[1]
    if op=="scroll":
        units=L[2]
        text2.yview_scroll(howMany, units)
    elif op=="moveto":
        text2.yview_moveto(howMany)

    

def msgbox1():
    tkMessageBox.showinfo('About', '                          Multi-Encryption tool v1.5\n\
\n\
  This program will encrypt/decrypt plain text/reversibly encrypted text.\n\
  Also will open a text based file and find keywords (separator: " : ").\n\
\n\
  Note that:\n\
   - In encryptions like "AES", "Blowfish", "CAST", etc (in some cases) are added\n\
    some aditional spaces to the end of the inputted string, because they require\n\
    a string of multiple of 16 or 8 characters long.\n\
   - RC5 is buggy with some keys.\n\
   - The non-ascii returned encrypted strings ( >127 ) are converted to hexadecimal strings.\n\
                                        (base 16 strings from chars; see ascii-table.com)\n\
   - Instead of Ctrl+A use Ctrl+/ \n\
\n\
                                                                              Visit   http://rstcenter.com/ \n\
\n\
\n\
Copyright (c) 2009. All rights reserved. "cmiN"')



def tables():
    global rot13_table, SkiddyFlama_table, Inglish_table, sign_table
    ## standard

    rot13_table={'a':'n', 'b':'o', 'c':'p', 'd':'q', 'e':'r', 'f':'s', 'g':'t', 'h':'u', 'i':'v', 'j':'w', 'k':'x', 'l':'y', 'm':'z',
                 'A':'N', 'B':'O', 'C':'P', 'D':'Q', 'E':'R', 'F':'S', 'G':'T', 'H':'U', 'I':'V', 'J':'W', 'K':'X', 'L':'Y', 'M':'Z'}
    
    ## others

    sign_table=(',', '.', '!', '?', ';', ':', '"')

    SkiddyFlama_table=[('bafta', 'bft'), ('asteapta', 'ast'), ('toti', 'all'), ('nu stiu', 'nush'),
                       ('oricum', 'anyway'), ('vorba', 'vb'), ('pana', 'pan'), ('eu', 'yo'),
                       ('niste', 'nijte'), ('nu', 'noh'), ('merge', 'mere'), ('tarziu', 'tarliu'),
                       ('persoana', 'pers'), ('bai', 'buey'), ('ba', 'bha'), ('bine', 'bn'), ('salut', 'sal'),
                       ('pup', 'poop'), ('mine', 'mn'), ('si', 'shi'), ('pe', 'p'), ('tu', 'u'), ('ce', 'c'),
                       ('ca', 'k'), ('de', 'd'), ('va', 'v')]

    Inglish_table=[('me', 'mi'), ('do', 'du'), ('know', 'cnau'), ("can", 'chen'), ('please', 'pliz'), ('fuck', 'fac'),
                   ('mother', 'madar'), ('believe', 'biliv'), ('are', 'ar'), ('not', 'nat'), ('out', 'aut'), ('my', 'mai'),
                   ('face', 'fais'), ('your', 'iour'), ('children', 'cildren'), ('uy', 'ui'), ('ive', 'iv'),
                   ('this', 'dis'), ('too', 'ciu'), ('what', 'uat'), ('the', 'da')]




def bye():
    root.destroy()



def end():
    root.wm_iconbitmap("icon.ico")
    root.title('Multi-Encryption')
    root.minsize(400, 400)
    root.maxsize(400, 400)
    root.mainloop()



frames()
tables()
create_widgets()
end()
