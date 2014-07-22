#! /usr/bin/env python
# 22.08.2009 <> 22.08.2009 | cmiN
# Multihash Dictionary Attack (console)


import sys, hashlib, multiprocessing, time


class MDA:
    def __init__(self, hash_type, hexdigest_hash, words_file):
        self.intype = hash_type
        self.instr = hexdigest_hash
        self.infile = words_file
        self.outstr = None
    def check(self):
        if not self.intype in ("md2", "md4", "md5", "sha1", "sha224", "sha256", "sha384", "sha512", "ripemd"):
            raise Exception, "hash type not in available list"
        if not self.instr.isalnum() or self.instr.isdigit() or self.instr.isalpha():
            raise Exception, "invalid hash"
        if self.intype == "md2" and not len(self.instr) / 2.0 * 8 == 128:
            raise Exception, "invalid hash length"
        elif self.intype == "md4" and not len(self.instr) / 2.0 * 8 == 128:
            raise Exception, "invalid hash length"
        elif self.intype == "md5" and not len(self.instr) / 2.0 * 8 == 128:
            raise Exception, "invalid hash length"
        elif self.intype == "sha1" and not len(self.instr) / 2.0 * 8 == 160:
            raise Exception, "invalid hash length"
        elif self.intype == "sha224" and not len(self.instr) / 2.0 * 8 == 224:
            raise Exception, "invalid hash length"
        elif self.intype == "sha256" and not len(self.instr) / 2.0 * 8 == 256:
            raise Exception, "invalid hash length"
        elif self.intype == "sha384" and not len(self.instr) / 2.0 * 8 == 384:
            raise Exception, "invalid hash length"
        elif self.intype == "sha512" and not len(self.instr) / 2.0 * 8 == 512:
            raise Exception, "invalid hash length"
        elif self.intype == "ripemd" and not len(self.instr) / 2.0 * 8 == 160:
            raise Exception, "invalid hash length"
    def start(self):
        generator = (line for line in open(self.infile, "r"))
        for word in generator:
            if hashlib.new(self.intype, word.strip("\n")).hexdigest() == self.instr:
                self.outstr = word
                break
    def get(self):
        if self.outstr is None:
            print "The program didn't find a match for {hash_type} {hexdigest_hash} using all the words from {words_file}".format(hash_type=self.intype, hexdigest_hash=self.instr, words_file=self.infile)
        else:
            print "The plain text is {outstr} for {hash_type} {hexdigest_hash} using words from {words_file}".format(hash_type=self.intype, hexdigest_hash=self.instr, words_file=self.infile, outstr=self.outstr)
    __version__ = "1.0"
    __doc__ = """This class tries to find the plain text from a hash by reading strings from a file and verifying their hash with the wanted one.
Available hash types: md2 md4 md5 sha1 sha224 sha256 sha384 sha512 ripemd"""


def run(*args):
    try:
        print "Please wait..."
        time.clock()
        MDAinstance = MDA(args[1], args[2], args[3])
        MDAinstance.check()
    except Exception, message:
        print "An error occurred: {0}".format(message)
    except:
        print "Unknown error."
    else:
        MDAinstance.start()
        MDAinstance.get()
        print "Ready! Elapsed time: {0}''".format(time.clock())


def main():
    usage = """\t Multihash Dictionary Attack {0}

{1}

\tUsage: MhashDA hash_type hexdigest_hash words_file

Where hash_type is one from the available types
      hexdigest_hash is the hash in hexadecimal string representation
      words_file is a text file containing the words needed to be hashed
      
\tExample: MhashDA md5 d674dfcd8b4db6762bcb3667316d3bb9 D:\others\dict.txt""".format(MDA.__version__, MDA.__doc__)
    if len(sys.argv) == 4:
        pool.apply_async(run, args=sys.argv)        
    else:
        print usage
    raw_input()


if __name__ == "__main__":
    multiprocessing.freeze_support()
    pool = multiprocessing.Pool(1)
    main()
