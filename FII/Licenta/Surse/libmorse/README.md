# libmorse [![Documentation Status](https://readthedocs.org/projects/libmorse/badge/?version=latest)](https://libmorse.readthedocs.io/en/latest/?badge=latest)

Convert timed signals into alphabet.


## Installation

For this project, we're gonna use Python 2 version.


#### Install Python interpreter and pip:

*Linux*

```bash
$ sudo apt update && sudo apt install --upgrade python python-dev python-setuptools
$ sudo -H easy_install -U pip
```

*Windows*
- download and install desired version from here: https://www.python.org/downloads/
- download and run get-pip script: https://pip.pypa.io/en/stable/installing/

Make sure that you're using the correct version of pip, by running
`pip --version`. It should use the Python 2 version, if not, try with *pip2*.


#### Clone repository and install package:

```bash
$ git clone https://github.com/cmin764/libmorse.git
$ cd libmorse
$ sudo -H ./setup.sh    # setup.bat on Windows
```


## Usage

#### Run CLI and explore the library commands:

*Linux*

```bash
$ libmorse --help
```

If you have trouble with file permissions (libmorse.log), don't forget to
remove them with `sudo` first. Or simply run `git clean -fdx` to clean-up the
project directory.

*Windows*

```bat
> python bin\libmorse --help
```


#### Within CLI:

*Windows*

Convert alphabet into morse code:

```bat
> python bin\libmorse -v send -m "morse code"
-- --- .-. ... . / -.-. --- -.. .
```

Convert morse code back into alphabet (save output above on disk):

```bat
> python bin\libmorse -v send -m -o morse.txt "morse code"
> python bin\libmorse -v receive -m morse.txt
MORSE CODE
```

Convert alphabet into morse code as pairs of signal/silence quanta:

```bat
> python bin\libmorse -v send -o morse.mor "morse code"
> tail morse.mor -n 4
0 300.0
1 300.0
0 900.0
1 300.0
```

Convert quanta back into alphabet (above output already saved on disk):

```bat
> python bin\libmorse -v receive morse.mor
MORSE CODE
```

*Linux*

Same commands, just directly execute the `libmorse` script without the need to
supply paths, like in the top Windows examples above.


#### Within module:

You can also import **libmorse** as a normal python module/library and use it
accordingly in your Python scripts/projects.

Suppose we're having a source of signals and silences of different lengths,
like these:

```python
items = [(True, 900.0),
 (False, 300.0),
 (True, 900.0),
 (False, 900.0),
 (True, 900.0),
 (False, 300.0),
 (True, 900.0),
 (False, 300.0),
 (True, 900.0),
 (False, 900.0),
 (True, 300.0),
 (False, 300.0),
 (True, 900.0),
 (False, 300.0),
 (True, 300.0),
 (False, 900.0),
 (True, 300.0),
 (False, 300.0),
 (True, 300.0),
 (False, 300.0),
 (True, 300.0),
 (False, 900.0),
 (True, 300.0),
 (False, 2100.0),
 
 (True, 900.0),
 (False, 300.0),
 (True, 300.0),
 (False, 300.0),
 (True, 900.0),
 (False, 300.0),
 (True, 300.0),
 (False, 900.0),
 (True, 900.0),
 (False, 300.0),
 (True, 900.0),
 (False, 300.0),
 (True, 900.0),
 (False, 900.0),
 (True, 900.0),
 (False, 300.0),
 (True, 300.0),
 (False, 300.0),
 (True, 300.0),
 (False, 900.0),
 (True, 300.0)]
```

Or a *.mor* file containing similar entries line by line (`True` and `False`
normalized to `1` and `0`) which can be retrieved by using the
`libmorse.get_mor_code` utility function, then you can automatically analyse
and convert them into text by using the `libmorse.translate_morse` coroutine:

```python
>>> import libmorse

>>> gen = libmorse.translate_morse()
>>> gen.next()
(<libmorse.translator.MorseTranslator at 0x7f324404ff50>, [])
>>> for item in items[:24]:    # items above
        gen.send(item)
    
>>> gen.send((True, 900.0))[1]
[]
>>> gen.send((False, 300.0))[1]
[u'M', u'O', u'R', u'S', u'E', u' ']
>>> gen.send((True, 300.0))[1]
[]
>>> gen.send((False, 300.0))[1]
[]
>>> gen.send((True, 900.0))[1]
[]
>>> gen.send((False, 300.0))[1]
[]
>>> gen.send((True, 300.0))[1]
[]
>>> gen.send((False, 900.0))[1]
[]
>>> gen.send((True, 900.0))[1]
[]
>>> gen.send((False, 300.0))[1]
[u'C']

# And so on, until we get the full text.
```

We've seen nothing for the first 24 quanta (12 signals and 12 silences) because
that's the minimum amount of data we must cluster and analyse in order to
correctly interpret each quanta and retrieve the text letter by letter starting
from that given threshold.

*For more details and examples, check the extensive API documentation described
below.*


## Development

If you want to develop **libmorse**, do the following:


#### Optionally install virtualenv:

*Linux*

```bash
$ sudo -H pip install -U virtualenv virtualenvwrapper
$ echo "export WORKON_HOME=~/Envs" >>~/.bashrc
$ source ~/.bashrc
$ mkdir -p $WORKON_HOME
$ echo "source /usr/local/bin/virtualenvwrapper.sh" >>~/.bashrc
$ source ~/.bashrc
$ mkvirtualenv morseus
```

*Windows*

Make sure that you have added your Python *Scripts* path to the system
path already (https://www.howtogeek.com/118594/how-to-edit-your-system-path-for-easy-command-line-access/).
The path you need to add is usually: `C:\Python27\Scripts`.

Now install the necessary pip packages and create your first virtual environment.

```bat
> pip install -U virtualenv virtualenvwrapper virtualenvwrapper-win
> mkvirtualenv morseus
```

Use `workon morseus` command to activate the virtual environment every time you
want to work through it and `deactivate` for leaving it.


#### Install requirements, develop and test:

Don't forget to uninstall the package first (if installed):

```bash
$ pip uninstall libmorse
```

Then:

```bash
$ pip install -Ur requirements/develop.txt
$ python setup.py develop
$ python setup.py test
```

Don't forget to run with `sudo -H` if you're working outside the virtualenv.


#### Run tests, create and serve documentation:

```bash
$ nosetests
$ cd docs && make html
$ cd build/html && python -m SimpleHTTPServer
```

Enter http://localhost:8000 to view documentation.

----

* Homepage: https://cosminpoieana.wordpress.com/
* Documentation: https://libmorse.readthedocs.io/
* Paper (RO): https://goo.gl/H6JfTw
* App: https://github.com/cmin764/morseus
* Source: https://github.com/cmin764/libmorse.git
* License: MIT
* Authors:
    + Cosmin Poieana <cmin764@gmail.com>
