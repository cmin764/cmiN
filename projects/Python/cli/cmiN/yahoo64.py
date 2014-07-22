#! /usr/bin/env python

__doc__="""   O librarie ce adapteaza codarea/decodarea din base64 la yahoo64
           cu urmatoarele modificari pentru siguranta URL-urilor:

           + este reprezentat de .

           / este reprezentat de _
           
           = este reprezentat de -

                                             by  cmiN
        """

import base64

def encode(string):
    encoded=base64.b64encode(string)
    encoded=encoded.replace("+", ".")
    encoded=encoded.replace("/", "_")
    encoded=encoded.replace("=", "-")
    return encoded

def decode(string):
    string=string.replace(".", "+")
    string=string.replace("_", "/")
    string=string.replace("-", "=")
    decoded=base64.b64decode(string)
    return decoded

if __name__=="__main__":
    print(__doc__)
