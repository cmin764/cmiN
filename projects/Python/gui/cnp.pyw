#! /usr/bin/env python
# 12.04.2009 <-> 13.04.2009 | cmiN
# non-standard modules = ( Pmw  )


from Tkinter import *
import tkFont, tkMessageBox, Pmw, time, random


def main():
    global info, now
    now=(long(time.time()) / 300) * 300
    info="""
Cnp-Gen este un soft ce genereaza cnp-uri pe baza urmatoarelor cunostinte:

 SAALLZZJJNNNC - unde fiecare dintre litere reprezinta o cifra:

  S = sex + secol ( Persoanelor de sex masculin le sunt atribuite numerele
                       impare iar persoanelor de sex feminin numerele pare. )
  AA  = anul
  LL  = luna
  ZZ  = ziua
  JJ  = codul judetului
  NNN = este un numar din intervalul 001 - 999
  C   = cifra de control ( Fiecare cifra din CNP este inmultita cu cifra
                           de pe aceeasi pozitie din numarul 279146358279;
                           rezultatele sunt insumate, iar rezultatul final
                           este impartit cu rest la 11. Daca restul este 10,
                           atunci cifra de control este 1, altfel cifra de
                           control este egala cu restul.)


                             by cmiN
                                           
Idee luata dupa scriptul in php de pe http://rstcenter.com/ <tromfil>
"""
    county_list()
    frames()
    widgets()
    end()


def frames():
    global root, font
    root=Tk()
    font=tkFont.Font(family="Comic Sans MS", size=10, weight="bold")
    frame=Frame(root)
    frame.option_add("*font", font)
    menu=Menu(root)
    filemenu=Menu(menu)
    helpmenu=Menu(menu)
    menu.add_cascade(label="File", menu=filemenu)
    menu.add_cascade(label="Help", menu=helpmenu)
    filemenu.add_separator()
    filemenu.add_command(label="Exit", command=bye)
    helpmenu.add_command(label="About", command=info_msgbox)
    root.config(menu=menu)


def widgets():
    global date, statement, sex, county, cnp_entry, generate_list, validate_list

    date=Pmw.Counter(labelpos="w", label_text="Data nasterii: ",
                     entryfield_value=time.strftime("%d/%m/%Y", time.localtime(now)),
                     entryfield_validate={"validator": "date", "format": "dmy",},
                     datatype={"counter": "date", "format": "dmy", "yyyy": 1}
                     )

    statement=Pmw.RadioSelect(labelpos="w", label_text="Stare: ", command=statement_callback,
                              frame_borderwidth=2, frame_relief="ridge"
                              )
    
    sex=Pmw.RadioSelect(labelpos="w", label_text="Sex: ", command=sex_callback,
                              frame_borderwidth=2, frame_relief="ridge"
                              )
    
    for text in ("Roman", "Strain rezident in Romania", "Strain"):
        statement.add(text)
    for text in ("Masculin", "Feminin"):
        sex.add(text)
        
    county=Pmw.ComboBoxDialog(title="Judet", buttons=("OK", "Cancel"),
                              defaultbutton="OK", combobox_labelpos="n",
                              label_text="Alege un judet...",
                              scrolledlist_items=(judete_keys)
                              )
    county.withdraw()
    county_button=Button(text="Judet...", command=county_click)

    generate=Button(text="Genereaza!", command=generator, fg="red")

    generate_list=Pmw.TextDialog(scrolledtext_labelpos="n", title="Lista",
                                 defaultbutton=0,
                                 label_text="Lista cu toate CNP-urile"
                                 )

    validate_list=Pmw.TextDialog(scrolledtext_labelpos="n", title="Date",
                                 defaultbutton=0,
                                 label_text="Date despre CNP"
                                 )
    
    generate_list.withdraw()
    validate_list.withdraw()
    generate_button=Button(text="Genereaza lista!", command=list_generator, fg="blue")

    cnp_entry=Pmw.EntryField(labelpos="w", label_text="CNP: ", value=1930426394424,
                             validate = {'validator': 'numeric', "max": 9999999999999}
                            )

    validate=Button(text="Valideaza!", command=validator, fg="green")

    for widget in (date, statement, sex):
        widget.pack(padx=8, pady=8, anchor="w")

    county_button.pack(padx=20, pady=20, anchor="c")
    cnp_entry.pack(padx=20, pady=20, anchor="c")
    generate.pack(anchor="w")
    generate_button.pack(anchor="w")
    validate.pack(anchor="w")


def county_click():
    global result, _choice
    result=county.activate()
    choice=county.get()
    if result=="OK":
        _choice=choice


def generator():
    try:
        global ZZ, LL, AA, S, JJ
        _date=date.get()
        _date=_date.split("/")
        ZZ=_date[0]
        LL=_date[1]
        AA=_date[2][2:]
        if _statement=="Roman":
            if int(_date[2]) in range(1800, 1900):
                if _sex=="Masculin":
                    S="3"
                elif _sex=="Feminin":
                    S="4"
            if int(_date[2]) in range(1900, 1999):
                if _sex=="Masculin":
                    S="1"
                elif _sex=="Feminin":
                    S="2"
            if int(_date[2]) in range(2000, 2099):
                if _sex=="Masculin":
                    S="5"
                elif _sex=="Feminin":
                    S="6"
        if _statement=="Strain rezident in Romania":
            if _sex=="Masculin":
                S="7"
            elif _sex=="Feminin":
                S="8"
        if _statement=="Strain":
            S="9"
        JJ=judete[_choice]
        NNN=str(random.randint(001, 999))
        if len(NNN)==1:
            NNN="00"+NNN
        elif len(NNN)==2:
            NNN="0"+NNN
        cn=S+AA+LL+ZZ+JJ+NNN
        suma=0
        z=0
        for x in "279146358279":
            suma=suma+int(x)*int(cn[z])
            z=z+1
        rest=suma%11
        if rest==10:
            C="1"
        else:
            C=str(rest)
        cnp=S+AA+LL+ZZ+JJ+NNN+C
        cnp_entry.setentry(int(cnp))
        return True
    except:
        error_msgbox()
        return False


def list_generator():
    global cnp_list
    if generator()==True:
        cnp_list=[]
        for NNN in range(001, 1000):
            NNN=str(NNN)
            if len(NNN)==1:
                NNN="00"+NNN
            elif len(NNN)==2:
                NNN="0"+NNN
            cn=S+AA+LL+ZZ+JJ+NNN
            suma=0
            z=0
            for x in "279146358279":
                suma=suma+int(x)*int(cn[z])
                z=z+1
            rest=suma%11
            if rest==10:
                C="1"
            else:
                C=str(rest)
            cnp=S+AA+LL+ZZ+JJ+NNN+C
            cnp_list.append(cnp)
        generate_list.configure(text_state="normal")
        generate_list.clear()
        for x in cnp_list:
            generate_list.insert("end", x+"\n")
        generate_list.configure(text_state="disabled")
        generate_list.activate()


def validator():
    state=True
    try:
        cnp=cnp_entry.get()
        if len(cnp)!=13:
            raise Exception, "Lungime nevalida."
        S, AA, LL, ZZ, JJ, NNN, C=(int(cnp[0:1]), int(cnp[1:3]), int(cnp[3:5]), int(cnp[5:7]),
                                   int(cnp[7:9]), int(cnp[9:12]), cnp[12:13]
                                   )
        cn=cnp_entry.get()[:-1]
        if not S in range(1, 10):
            raise Exception, "Campul pentru sex nevalid."
        if not LL in range(1, 13):
            raise Exception, "Campul pentru luna nevalid."
        if not ZZ in range(1, 32):
            raise Exception, "Campul pentru ziua nevalid."
        if not JJ in range(1, 53):
            raise Exception, "Campul pentru judet nevalid."
        suma=0
        z=0
        for x in "279146358279":
            suma=suma+int(x)*int(cn[z])
            z=z+1
        rest=suma%11
        if rest==10:
            c="1"
        else:
            c=str(rest)
        if not C==c:
            raise Exception, "Cifra de control nevalida,"
    except:
        state=False
    if state==True:
        info_valid_msgbox()
        AA, LL, ZZ, JJ, NNN, C=(cnp[1:3], cnp[3:5], cnp[5:7],
                                cnp[7:9], cnp[9:12], cnp[12:13]
                                )
        if S==1:
            AA="19"+AA
            text1="Persoana rezidenta in Romania de sex masculin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==2:
            AA="19"+AA
            text1="Persoana rezidenta in Romania de sex feminin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==3:
            AA="18"+AA
            text1="Persoana rezidenta in Romania de sex masculin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==4:
            AA="18"+AA
            text1="Persoana rezidenta in Romania de sex feminin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==5:
            AA="20"+AA
            text1="Persoana rezidenta in Romania de sex masculin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==6:
            AA="20"+AA
            text1="Persoana rezidenta in Romania de sex feminin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==7:
            AA="xx"+AA
            text1="Persoana straina rezidenta in Romania de sex masculin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==8:
            AA="xx"+AA
            text1="Persoana straina rezidenta in Romania de sex feminin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        if S==9:
            AA="xx"+AA
            text1="Persoana straina de sex masculin/feminin nascuta in ziua: "+ZZ+" luna: "+LL+" anul: "+AA
        for text2 in judete.keys():
            if JJ==judete[text2]:
                break
        text=text1+" in judetul: "+text2+" cu numarul de evidenta: "+NNN+" si cifra de control: "+C+"."
        validate_list.configure(text_state="normal")
        validate_list.clear()
        validate_list.insert("end", text)
        validate_list.configure(text_state="disabled")
        validate_list.activate()
    else:
        warning_invalid_msgbox()
        

def bye():
    root.destroy()


def statement_callback(tag):
    global _statement
    _statement=tag


def sex_callback(tag):
    global _sex
    _sex=tag


def info_msgbox():
    tkMessageBox.showinfo("About", info)

def error_msgbox():
    tkMessageBox.showerror("Error", "Setari nevalide!")

def info_valid_msgbox():
    tkMessageBox.showinfo("Valid", "Felicitari, CNP-ul introdus/generat este valid!")

def warning_invalid_msgbox():
    tkMessageBox.showwarning("Warning", "CNP-ul introdus/generat NU este valid.")


def county_list():
    global judete, judete_keys
    judete={"Alba": "01", "Arad": "02", "Arges": "03", "Bacau": "04", "Bihor": "05",
            "Bistrita-Nasaud": "06", "Botosani": "07", "Brasov": "08", "Braila": "09", "Buzau": "10",
            "Caras-Severin": "11", "Cluj": "12", "Constanta": "13", "Covasna": "14", "Dambovita": "15",
            "Dolj": "16", "Galati": "17", "Gorj": "18", "Harghita": "19", "Hunedoara": "20",
            "Ialomita": "21", "Iasi": "22", "Ilfov": "23", "Maramures": "24", "Mehedinti": "25",
            "Mures": "26", "Neamt": "27", "Olt": "28", "Prahova": "29", "Satu Mare": "30",
            "Salaj": "31", "Sibiu": "32", "Suceava": "33", "Teleorman": "34", "Timis": "35",
            "Tulcea": "36", "Vaslui": "37", "Valcea": "38", "Vrancea": "39", "Bucuresti": "40",
            "Bucuresti S.1": "41", "Bucuresti S.2": "42", "Bucuresti S.3": "43", "Bucuresti S.4": "44", "Bucuresti S.5": "45",
            "Bucuresti S.6": "46", "Calarasi": "51", "Giurgiu": "52"
            }
    judete_keys=()
    for x in judete.keys():
        judete_keys=judete_keys+(x,)
    judete_keys=sorted(judete_keys)


def end():
    root.title("Cnp-Gen")
    root.minsize(400, 400)
    root.maxsize(400, 400)
    root.mainloop()

main()
