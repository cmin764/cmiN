#! /usr/bin/env python
# 16.08.2009 <> 16.08.2009 | cmiN
# Multihash Brute Force (console)


import sys, hashlib, multiprocessing, time


class MBF:
    def __init__(self, hash_type, hexdigest_hash, charset_mode, interval_length):
        self.intype = hash_type
        self.instr = hexdigest_hash
        self.charset = [""]
        self.inttask = None
        self.outstr = None
        self.charset_mode = charset_mode
        self.interval_length = interval_length
        if int(interval_length.split("-")[0]) <= int(interval_length.split("-")[1]):
            self.inttask = xrange(int(interval_length.split("-")[0]), int(interval_length.split("-")[1]) + 1, 1)
        else:
            self.inttask = xrange(int(interval_length.split("-")[0]), int(interval_length.split("-")[1]) - 1, -1)
        if "la" in charset_mode:
            self.charset.extend(['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'])
        if "ua" in charset_mode:
            self.charset.extend(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'])
        if "d" in charset_mode:
            self.charset.extend(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'])
        if "o" in charset_mode:
            self.charset.extend(['`', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '|', '[', '{', ']', '}', ';', ':', "'", '"', ',', '<', '.', '>', '/', '?', ' '])
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
        if not int(self.interval_length.split("-")[0]) in xrange(1, 10) or not int(self.interval_length.split("-")[1]) in xrange(1, 10):
            raise Exception, "invalid interval length"
    def start(self):
        for task in self.inttask:
            if task == 1:
                generator = ("".join([word1]) for word1 in self.charset)
            elif task == 2:
                generator = ("".join([word1, word2]) for word1 in self.charset for word2 in self.charset)
            elif task == 3:
                generator = ("".join([word1, word2, word3]) for word1 in self.charset for word2 in self.charset for word3 in self.charset)
            elif task == 4:
                generator = ("".join([word1, word2, word3, word4]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset)
            elif task == 5:
                generator = ("".join([word1, word2, word3, word4, word5]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset)
            elif task == 6:
                generator = ("".join([word1, word2, word3, word4, word5, word6]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset)
            elif task == 7:
                generator = ("".join([word1, word2, word3, word4, word5, word6, word7]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset for word7 in self.charset)
            elif task == 8:
                generator = ("".join([word1, word2, word3, word4, word5, word6, word7, word8]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset for word7 in self.charset for word8 in self.charset)
            elif task == 9:
                generator = ("".join([word1, word2, word3, word4, word5, word6, word7, word8, word9]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset for word7 in self.charset for word8 in self.charset for word9 in self.charset)
            print "Length {0} started!".format(str(task))
            for generated_string in generator:
                if hashlib.new(self.intype, generated_string).hexdigest() == self.instr:
                    self.outstr = generated_string
                    break
            if not self.outstr is None:
                break
    def get(self):
        if self.outstr is None:
            print "The program didn't find a match for {hash_type} {hexdigest_hash} using mode {charset_mode} with string length {interval_length}.".format(hash_type=self.intype, hexdigest_hash=self.instr, charset_mode=self.charset_mode, interval_length=self.interval_length)
        else:
            print "The plain text is {outstr} for {hash_type} {hexdigest_hash} using mode {charset_mode} with string length {interval_length}.".format(hash_type=self.intype, hexdigest_hash=self.instr, charset_mode=self.charset_mode, interval_length=self.interval_length, outstr=self.outstr)
    __version__ = "1.0"
    __doc__ = """This class tries to find the plain text from a hash by generating strings and verifying their hash with the wanted one.
Available hash types: md2 md4 md5 sha1 sha224 sha256 sha384 sha512 ripemd"""


def run(*args):
    try:
        print "Please wait..."
        time.clock()
        MBFinstance = MBF(args[1], args[2], args[3], args[4])
        MBFinstance.check()
    except Exception, message:
        print "An error occurred: {0}".format(message)
    except:
        print "Unknown error."
    else:
        MBFinstance.start()
        MBFinstance.get()
        print "Ready! Elapsed time: {0}''".format(time.clock())
        
    
def main():
    usage = """\t Multihash Brute Forcer {0}

{1}

\tUsage: MhashBF hash_type hexdigest_hash charset_mode interval_length

Where hash_type is one from the available types
      hexdigest_hash is the hash in hexadecimal string representation
      charset_mode sets the characters to use:
                la - loweralpha
                ua - upperalpha
                 d - digits
                 o - others
      interval_length is the length of the string from x to y
                min: 1
                max: 9
      
\tExample: MhashBF md5 d674dfcd8b4db6762bcb3667316d3bb9 lad 1-4""".format(MBF.__version__, MBF.__doc__)
    if len(sys.argv) == 5:
        pool.apply_async(run, args=sys.argv)
    else:
        print usage
    raw_input()


if __name__ == "__main__":
    multiprocessing.freeze_support()
    pool = multiprocessing.Pool(1)
    main()
