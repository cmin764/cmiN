#! /usr/bin/env python
# 21.08.2010 <> 21.08.2010 | cmiN
# SMTP Spammer 4 paxnWo @ rstcenter.com

import sys, threading, smtplib, socket
from email.mime.text import MIMEText

def main(args):
    usage = """\t\t SMTP Spammer 1.0

\t Usage: source.ext fradd subject message tolist smlist eno timeout threads

Where fradd is an arbitrary sender address
      subject is a string
      message is a file containing the email body
      tolist is a file with recipient addresses
      smlist is a file with SMTPs in this format:
          host port user password
      eno specifies how many emails every SMTP will send per thread
      timeout is a float (seconds)
          if None -> no timeout
      threads is an integer

\t Example: smam.py 1337@rstcenter.com Hello msg.txt emails.txt hosts.txt 100 None 2"""
    try:
        if len(args) == 9:
            process(args[1], args[2], args[3], args[4], args[5], int(args[6]), args[7], int(args[8]))
        else:
            print usage
    except Exception as message:
        print "An error occurred: {}".format(message)
        return 1
    except:
        print "Unexpected error."
        return 2
    return 0
    
def process(fradd, subject, message, tolist, smlist, eno, timeout, threads):
    if timeout != "None":
        socket.setdefaulttimeout(float(timeout))
    fobj = open(message, "rt")
    source = fobj.read()
    fobj.close()
    if source.find("<html>") == -1:
        etype = "plain"
    else:
        etype = "html"
    eobj = MIMEText(source, etype)
    eobj["Subject"] = subject
    eobj["From"] = fradd
    Send.fradd = fradd
    Send.estr = eobj.as_string()
    Send.sobj = smtplib.SMTP()
    with open(smlist, "rt") as fobj:
        smtps = set()
        for line in fobj:
            smtps.add(line.strip("\n"))
        smtps = list(smtps)
    with open(tolist, "rt") as fobj:
        status = True
        xrobj = xrange(eno)
        smlen = len(smtps)
        i = 0
        while status:
            emails = list()
            for j in xrobj:
                line = fobj.readline().strip("\n")
                if not line:
                    status = False
                    break
                else:
                    emails.append(line)
            if i == smlen:
                i = 0
                while threading.active_count() > 1:
                    pass
            while threading.active_count() > threads:
                pass
            Send(smtps[i], emails).start()
            i += 1
        while threading.active_count() > 1:
            pass
        
class Send(threading.Thread):

    def __init__(self, smtp, emails):
        threading.Thread.__init__(self)
        self.smtp = smtp
        self.emails = emails
        
    def run(self):
        host, port, user, password = self.smtp.split(" ")
        self.sobj.connect(host, port)
        self.sobj.login(user, password)
        self.sobj.sendmail(self.fradd, self.emails, self.estr)
        self.sobj.quit()
    
if __name__ == "__main__":
    main(sys.argv)
