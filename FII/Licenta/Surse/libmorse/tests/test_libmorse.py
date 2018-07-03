import unittest

import libmorse


class TestMorse(unittest.TestCase):

    def test_basic_length(self):
        mor_code = libmorse.get_mor_code("basic.mor")
        self.assertEqual(47, len(mor_code))
