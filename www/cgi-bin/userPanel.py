#!/usr/bin/env python3

import cgitb
import os

cgitb.enable()

def get_modified_html(username):
    with open('www/html/userPanel.html', 'r') as file:
        html_content = file.read()

    modified_html = html_content.replace('%USERNAME%', username)
    return modified_html

request_method = os.environ.get('REQUEST_METHOD', '')
bodyDict = dict()

if request_method == 'POST':
    rawbody = os.environ.get('BODY', "login=Guest")
    body = rawbody.split("&")
    for el in body:
        key, val = el.split("=")
        bodyDict[key] = val

    # for key, val in bodyDict.items():
    #     print(key + " " + val + "<br>")

modified_html = get_modified_html(bodyDict.get("login", "Guest"))
print(modified_html)
