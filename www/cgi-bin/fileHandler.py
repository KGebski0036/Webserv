#!/usr/bin/env python3

import cgitb
import os
import sys

import base64
import io

cgitb.enable()

paramDict = dict()


request_method = os.environ.get('REQUEST_METHOD', '')
rawParams = os.environ.get('PARAMS', '')
params = rawParams.split("&")
for el in params:
	if '=' in el:
		key, val = el.strip().split("=")
		paramDict[key] = val

user = paramDict.get('login')
if request_method == 'POST':
	f = open("www/html/userFiles/" + user + ".png", "wb+")
	content_length = int(os.environ.get("CONTENT_LENGTH", 0))

	base64_data = sys.stdin.read(content_length)
	binary_data = base64.b64decode(base64_data)
	f.write(binary_data)
	f.close()

elif request_method == 'DELETE':
	os.remove("www/html/userFiles/" + user + ".png")
