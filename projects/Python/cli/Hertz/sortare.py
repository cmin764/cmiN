#! /usr/bin/env python
# 28.06.2009 <> 28.06.2009 | cmiN
# Challenge [Programare]Sortare Alfabetica (Hertz) @ rstcenter.com

import os

def main():
    solution=0
    f=file("nume.txt", "r")
    names=f.read().split(",")
    names.sort()
    f.close()
    f=file("sorted_names.txt", "w")
    f.write("""| a| b| c| d| e| f| g| h| i| j| k| l| m| n| o| p| q| r| s| t| u| v| w| x| y| z|
|01|02|03|04|05|06|07|08|09|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|\n\n""")
    for x in range(len(names)):
        text=""
        variable=0
        for y in names[x]:
            variable+=ord(y)-96
            text+=str(ord(y)-96)+"+"
        text=text.strip("+")
        f.write(str(x+1)+". "+names[x]+" ("+text+")*"+str(x+1)+"="+str(variable*(x+1))+"\n")
        solution+=variable*(x+1)
    f.write("\nTotal: "+str(solution))
    f.close()
    print("Check 'sorted_names.txt'!")
    print(solution)
    os.system("pause >NUL")

if __name__=="__main__":
    main()
