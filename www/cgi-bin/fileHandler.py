#!/usr/bin/env python3

import cgitb
import os
import sys

cgitb.enable()

if request_method == 'POST':
    f = open("www/html/userFiles/asd", "a")
    f.write("Now the file has more content!")
    f.close()
