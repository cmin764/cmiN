#! /usr/bin/env python

import webbrowser, time, urllib

def main():
    s1 = test()
    while True:
        time.sleep(60) # seconds
        s2 = test()
        if s1 != s2:
            print "Redeem!"
            webbrowser.open_new_tab("http://ptzplace.lockerz.com/")
        
def test():
    uobj = urllib.urlopen("http://ptzplace.lockerz.com/")
    source = uobj.read()
    uobj.close()
    return source
    
if __name__ == "__main__":
    main()
