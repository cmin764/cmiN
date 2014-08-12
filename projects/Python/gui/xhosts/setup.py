#! /usr/bin/env python


try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup


setup(
    name="xhosts",
    version="0.2",
    description=("Hosts file editor with web support"),
    long_description=open("README").read(),
    author="Cosmin Poieana",
    author_email="cmin@ropython.org",
    url="https://github.com/cmin764/xhosts",
    packages=["xhosts"],
    scripts=["scripts/xhosts"]
)
