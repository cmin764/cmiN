# Cream utilizator nou `test` adaugat automat in grupul suplimentar
# `sudo`.
sudo useradd -G sudo test
# Facem switch user in `test` fara a fi necesara parola.
sudo su test
# Vedem unde gasim `passwd`.
which passwd
whereis passwd
# Scoatem bitul de SUID.
sudo chmod -s /usr/bin/passwd
# Testam passwd fara bitul setat si obtinem:

# Enter new UNIX password: 
# Retype new UNIX password: 
# passwd: Authentication token manipulation error
# passwd: password unchanged

# Deci problema, fiindca nu mai are capabilitatile alea generice de root/sudo
# ca sa faca ce ar trebui sa faca passwd (schimbarea parolei si alterarea
# fisierului /etc/passwd)

# Asa ca le introducem la mana, ca linux policies.
sudo setcap cap_dac_override,cap_fowner,cap_chown=ep /usr/bin/passwd
# ep vine de la atat effective cat si permit.
# Acum `passwd` se comporta normal.


# 2. Ii ajunge doar dac override lui more pentru a putea suprascrie
# drepturile de read si write pe acel fisier citibil doar de root
# in mod normal, insa acum se poate.
sudo setcap cap_dac_override=ep /bin/more
