#! /usr/bin/env python
# 27.06.2009 <> 27.06.2009 | cmiN
# Challenge [Programare] XORed (Hertz) @ rstcenter.com
# non-standard modules = ( Crypto )

import os, multiprocessing
from Crypto.Cipher import XOR



def decrypt(encrypted, chr_table):
    f=file("sol.txt", "w")
    for x in chr_table:
        word1=x
        for x in chr_table:
            word2=word1+x
            for x in chr_table:
                word3=word2+x
                xor=XOR.new(word3)
                decrypted=xor.decrypt(encrypted)
                status=True
                for x in decrypted:
                    if not ord(x) in range(65, 91)+range(97, 123)+[32]:
                        status=False
                if status:
                    f.write(decrypted+" - "+word3+"\n")
    f.close()



def cb(fileno):
    print("Ready! Check 'sol.txt' for a relevant result.")



def main():
    nr_table=[1, 12, 3, 3, 17, 5, 2, 22, 24, 10, 10, 11, 19, 13, 8, 6, 22, 14, 14,
              12, 27, 6, 9, 24, 2, 22, 4, 9, 17, 5, 14, 22, 30, 19, 23, 4, 9, 2]
    chr_table=["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
               "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
    encrypted=""
    for x in nr_table:
        encrypted+=chr(x)
    arguments=[encrypted, chr_table]
    pool.apply_async(decrypt, args=arguments, callback=cb)
    print("Please wait . . .")
    os.system("pause >NUL")



if __name__=="__main__":
    multiprocessing.freeze_support()
    pool=multiprocessing.Pool(4)
    main()
