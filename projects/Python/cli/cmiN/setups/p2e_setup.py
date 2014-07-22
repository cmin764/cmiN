from distutils.core import setup 
import py2exe

import os
import sys
import subprocess
import shutil

## si le fichier bundlepmw.py contient l'importation regsub (qui n'existe plus depuis la version 2.5 de Python)
## Vous pouvez sinon le faire à la main en remplaçant "regsub" par "re" et "gsub" par "sub"
fp = open(sys.prefix + os.sep + "Lib/site-packages/Pmw/Pmw_1_3/bin/bundlepmw.py")
a = fp.read().replace("regsub", "re").replace("gsub", "sub")
fp.close()
ft = open(sys.prefix + os.sep + "Lib/site-packages/Pmw/Pmw_1_3/bin/bundlepmw.py", "w")
ft.write(a)
ft.close()

## Création du fichier Pmw.py dans le répertoire courant
subprocess.call([sys.executable, sys.prefix + os.sep + "Lib/site-packages/Pmw/Pmw_1_3/bin/bundlepmw.py",
                 sys.prefix + os.sep + "Lib/site-packages/Pmw/Pmw_1_3/lib"])
## On copie les 2 fichiers PmwBlt.py et PmwColor.py dans le répertoire courant 
shutil.copyfile(sys.prefix + os.sep + "Lib/site-packages/Pmw/Pmw_1_3/lib/PmwBlt.py", "PmwBlt.py")
shutil.copyfile(sys.prefix + os.sep + "Lib/site-packages/Pmw/Pmw_1_3/lib/PmwColor.py", "PmwColor.py")
  
setup
(
    options={'py2exe': {"optimize": "2", 'bundle_files': 3}},
    windows=[{'script':'source.pyw', 'icon_resources':[(1, 'icon.ico')]}],
    name="Soft",
    version='1.0',
    company_name="Me",
    copyright = "Me",
    description='Some description.',
    author='Me',
    author_email='Me@domain.com',
    url='http://site.com/',
    #zipfile=None # "Don't send" error if zipfile is not commented and you use a windows GUI source
)
