#! /usr/bin/env python
# 29.06.2009 <> 29.06.2009 | cmiN
# URL-Checker 4 coolbyte @ rstcenter.com



import os, sys, urllib2, socket, multiprocessing



def main():
    sys_args=sys.argv
    if len(sys_args) != 4:
        print("\tUsage:\n\n\
\tuc.py unchecked.txt checked.txt 1\n\n\
\t  [+] unchecked.txt is a list with all the URLs you want to check\n\
\t  [+] in checked.txt are passed all available URLs\n\
\t  [+] 1 is the timeout value\n\n\
Press any key to exit. . .")
        os.system("pause >NUL")
    else:
        try:
            unchecked=sys_args[1]
            checked=sys_args[2]
            timeout=int(sys_args[3])
            arguments=[unchecked, checked, timeout]
            pool.apply_async(check, args=arguments, callback=cb)
            print("Please wait and press any key if you want to break the process. . .\n")
            os.system("pause >NUL")
        except:
            print("\nAn error occurred!")


        
def check(unchecked, checked, timeout):
    try:
        socket.setdefaulttimeout(timeout)
        f=file(unchecked, "r")
        urls=f.read().split("\n")
        f.close()
        f=file(checked, "w")
        for url in urls:
            try:
                urllib2.urlopen(url)
            except:
                pass
            else:
                f.write(url+"\n")
                print("[+] Valid: "+url)
        f.close()
        return "\nReady! Check: "+checked
    except:
        return "\nAn error occurred!"



def cb(returned):
    print returned



if __name__=="__main__":
    multiprocessing.freeze_support()
    pool=multiprocessing.Pool(2)
    main()
