#! /usr/bin/env python
#############################################################
#                                       Folder-Locker v1.35                                                #
#                                       All credits to cmiN                                                 #
# {'source':'python','time spent':'aprox 35+xx hours','platform':'windows xp','country':'Romania'} #
#############################################################

import os,shutil,chilkat,sha
os.startfile('dll.bat')
os.system('title Folder-Locker (c)2008 cmiN')

def start():
  os.system('cls')
  print('''
                           Folder - Locker v1.35
                                                      by
                                                     cmiN

    Any problem/suggestion ? Don't hesitate to contact cmin764 ( Yahoo! IM )

Features ("[+]"-new, "[-]"-deleted, "[!]"-attention):

              [+]- Profile manager
              [+]- Log
              [-]- Forgot password crap
              [!]- Read CAREFULLY and after you TYPE something press ENTER
________________________________________________________________________________

  After you put some files in a folder this program\script will lock the folder
with the files too !!!
________________________________________________________________________________
''')
  print('===============================================================================')
  ask=str(raw_input('  Press ENTER to continue or\n\
type something to exit: '))
  if ask=='':
    vfprofile('  Profile manager')
  else:
    flexit()

def vfprofile(text):
  global prof
  os.system('cls')
  print text
  print('===============================================================================')
  ask=str(raw_input('  "L"-Login with an existent profile\n\
  "C"-Create a new profile\n\
  "M"-Modify a profile\n\
  "B"-Go back: '))
  if ask in ('b','B'):
    start()
  elif ask in ('c','C'):
    print '\n'
    prof=str(raw_input('  Enter a name: '))
    try:
      file(prof,'r')
    except IOError:
      print '\n'
      inputpass=str(raw_input('  Enter a password that you remember: '))
      inputpass2=str(raw_input('  Re-enter the password to confirm  : '))
      if inputpass==inputpass2:
        print '\n'
        lockmethod=str(raw_input('  Chose a lock method. (type "STANDARD" or "PRO")\n\
  In "STANDARD" the folder will be LESS secure,\n\
but will take short time to complete!\n\
  In "PRO" the folder will be encrypted and MORE secure,\n\
but will take a longer time to complete ONLY if the files are BIG!\n\
---> '+"It's"+' recommended to use a "PRO" method: '))
        if not lockmethod in ('standard','Standard','STANDARD','pro','Pro','PRO'):
          vfprofile('  Invalid lock method!')
        else:
          try:
            profile=file(prof,'w')
          except IOError:
            vfprofile('  Invalid name!')
          else:
            profile.write(sha.new(inputpass2).hexdigest())
            profile.write('\n')
            profile.write(lockmethod)
            profile.close()
            os.mkdir(prof+'f')
            os.mkdir(prof+'f\\'+prof+'f')
            os.system('attrib '+prof+' +h')
            os.system('attrib '+prof+'f +h')
            vfprofile('  Profile created successfully!')
      else:
        vfprofile('  In order to enter a valid password,\n\
both passwords must be the same: "'+inputpass+'"'+" <-- doesn't match with --> "+'"'+inputpass2+'"')
    else:
      file(prof,'r').close()
      vfprofile('  A profile named "'+prof+'" already exists.')
  elif ask in ('l','L'):
    print '\n'
    prof=str(raw_input("  Enter profile's name: "))
    try:
      file(prof,'r')
    except IOError:
      vfprofile('  There is no profile named "'+prof+'".')
    else:
      file(prof,'r').close()
      vfpassword(3,'login')
  elif ask in ('m','M'):
    print '\n'
    prof=str(raw_input("  Enter profile's name: "))
    try:
      file(prof,'r')
    except IOError:
      vfprofile('  There is no profile named "'+prof+'".')
    else:
      file(prof,'r').close()
      if os.path.isdir(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}') is False:
        vfpassword(3,'modify')
      else:
        vfprofile("  You can't change this profile, because the folder it use is locked.\n\
You must unlock your folder first!")
  else:
    vfprofile('  Invalid choice!')

def vfpassword(retries,path):
  global finalpass
  os.system('cls')
  print('===============================================================================')
  finalpass=str(raw_input('  Please enter the password: '))
  if sha.new(finalpass).hexdigest()==file(prof,'r').readlines()[0][:-1]:
    if path=='login':
      lgprofile('  Logged in.')
    elif path=='modify':
      mfprofile('  Modify '+prof+"'s settings.")
    else:
      chpassword()
  else:
    retries=retries-1
    if retries==0:
      print '\n'
      print '  The program will exit! - press any key to continue... '
      os.system('pause>NUL')
      os.system('exit')
    else:
      print '\n'
      print '  Acces DENIED!\n\
Try/tries left: ',retries,' - press any key to continue... '
      os.system('pause>NUL')
      vfpassword(retries,path)

def chpassword():
  lockmethod=file(prof,'r').readlines()[1]
  print '\n'
  inputpass=str(raw_input('  Enter a password that you remember: '))
  inputpass2=str(raw_input('  Re-enter the password to confirm  : '))
  if inputpass==inputpass2:
    os.system('attrib '+prof+' -h')
    profile=file(prof,'w')
    profile.write(sha.new(inputpass2).hexdigest())
    profile.write('\n')
    profile.write(lockmethod)
    profile.close()
    os.system('attrib '+prof+' +h')
    mfprofile('  Password changed successfully.')
  else:
    mfprofile('  In order to enter a valid password,\n\
both passwords must be the same: "'+inputpass+'"'+" <-- doesn't match with --> "+'"'+inputpass2+'"')

def mfprofile(text):
  os.system('cls')
  print text
  print('===============================================================================')
  ask=str(raw_input('  "P"-Change the password\n\
  "N"-Change the lock method\n\
  "D"-Delete the profile and all the files used by it\n\
  "B"-Go back: '))
  if ask in ('p','P'):
    vfpassword(3,'modify2')
  elif ask in ('n','N'):
    print '\n'
    lockmethod=str(raw_input('  Chose a lock method. (type "STANDARD" or "PRO")\n\
  In "STANDARD" the folder will be LESS secure,\n\
but will take short time to complete!\n\
  In "PRO" the folder will be encrypted and MORE secure,\n\
but will take a longer time to complete ONLY if the files are BIG!\n\
---> '+"It's"+' recommended to use a "PRO" method: '))
    if not lockmethod in ('standard','Standard','STANDARD','pro','Pro','PRO'):
      mfprofile('  Invalid lock method!')
    else:
      os.system('attrib '+prof+' -h')
      outputpass=file(prof,'r').readlines()[0][:-1]
      profile=file(prof,'w')
      profile.write(outputpass)
      profile.write('\n')
      profile.write(lockmethod)
      profile.close()
      os.system('attrib '+prof+' +h')
      mfprofile('  Lock method changed successfully.')
  elif ask in ('d','D'):
    print '\n'
    ask2=str(raw_input('  Are you sure that you want to delete the profile\n\
and all the files used by it? (Y/N): '))
    if ask2 in ('y','Y'):
      try:
        os.remove(prof)
      except WindowsError:
        print '  '+prof+" doesn't exist!"
      else:
        print '  '+prof+" deleted."
      try:
        shutil.rmtree(prof+'f')
      except WindowsError:
        print "  Main folder doesn't exist!"
      else:
        print "  Main folder deleted."
      print '\n'
      os.system('pause')
      start()
    elif ask2 in ('n','N'):
      mfprofile('  Modify '+prof+"'s settings.")
    else:
      mfprofile('  Invalid choice!')
  elif ask in ('b','B'):
    vfprofile('  Profile manager')
  else:
    mfprofile('  Invalid choice!')
    
def lgprofile(text):
  os.system('cls')
  print text
  print('===============================================================================')
  ask=str(raw_input('  "U"-LOCK\UNLOCK the folder\n\
  "F"-See the log file\n\
  "Z"-Log out: '))
  if ask in ('u','U'):
    if os.path.isdir(prof+'f\\'+prof+'f') is True:
      lkfolder()
    else:
      ukfolder()
  elif ask in ('f','F'):
    try:
      os.startfile(prof+'f\\log.txt')
    except WindowsError:
      print '\n'
      print "  The log file doesn't exist. - press any key to continue..."
      os.system('pause>NUL')
    lgprofile('  Logged in.')
  elif ask in ('z','Z'):
    vfprofile('  Logged out.')
  else:
    lgprofile('  Invalid choice!')

def lkfolder():
  os.startfile(prof+'f\\'+prof+'f')
  print '\n'
  print '  It seems that your folder is unlocked.\n\
Put your desired files in the opened folder and\n\
press any key when you are ready to lock it.'
  os.system('pause>NUL')
  print '\n'
  print '  Please wait...'
  os.system('cd '+prof+'f\\'+prof+'f')
  os.system('attrib -r /s')
  lockmethod=file(prof,'r').readlines()[1]
  if lockmethod in ('standard','Standard','STANDARD'):
    os.rename(prof+'f\\'+prof+'f',prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}')
  else:
    os.mkdir(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}')
    zipfolder=chilkat.CkZip()
    zipfolder.UnlockComponent('ZIP-TEAMBEAN_3313FAF5910U')
    zipfolder.NewZip(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}\\'+prof)
    zipfolder.put_Encryption(4)
    zipfolder.put_EncryptKeyLength(256)
    zipfolder.SetPassword(finalpass)
    zipfolder.AppendFiles(prof+'f\\'+prof+'f',True)
    zipfolder.WriteZip()
    shutil.rmtree(prof+'f\\'+prof+'f')
  os.system('date /t >>'+prof+'f\\log.txt')
  os.system('time /t >>'+prof+'f\\log.txt')
  os.system('echo LOCKED >>'+prof+'f\\log.txt')
  os.system('echo. >>'+prof+'f\\log.txt')
  lgprofile('  Folder locked successfully.')

def ukfolder():
  print '\n'
  print '  It seems that your folder is locked.\n\
Press any key when you are ready to unlock it.'
  os.system('pause>NUL')
  print '\n'
  print '  Please wait...'
  lockmethod=file(prof,'r').readlines()[1]
  if lockmethod in ('standard','Standard','STANDARD'):
    os.rename(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}',prof+'f\\'+prof+'f')
  else:
    zipfolder=chilkat.CkZip()
    zipfolder.UnlockComponent('ZIP-TEAMBEAN_3313FAF5910U')
    zipfolder.put_Encryption(4)
    zipfolder.put_EncryptKeyLength(256)
    zipfolder.SetPassword(finalpass)
    zipfolder.OpenZip(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}\\'+prof)
    zipfolder.Unzip(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}')
    os.remove(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}\\'+prof)    
    os.rename(prof+'f\\My Computer                                                                               .{20d04fe0-3aea-1069-a2d8-08002b30309d}',prof+'f\\'+prof+'f')
  os.system('date /t >>'+prof+'f\\log.txt')
  os.system('time /t >>'+prof+'f\\log.txt')
  os.system('echo UNLOCKED >>'+prof+'f\\log.txt')
  os.system('echo. >>'+prof+'f\\log.txt')
  os.startfile(prof+'f\\'+prof+'f')
  lgprofile('  Folder unlocked successfully.')
     
def flexit():
  os.system('cls')
  print('===============================================================================')
  ask=str(raw_input('  Are you sure that you want to exit? (Y/N): '))
  if ask in ('y','Y'):
    os.system('exit')
  elif ask in ('n','N'):
    start()
  else:
    flexit()

start()
