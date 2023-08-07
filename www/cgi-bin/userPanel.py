#!/usr/bin/env python3
import cgi
import cgitb
import sys
import os

cgitb.enable()

def get_modified_html(username):
    with open('www/html/userPanel.html', 'r') as file:
        html_content = file.read()

    modified_html = html_content.replace('%USERNAME%', username)
    return modified_html

form = cgi.FieldStorage()

if 'CONTENT_LENGTH' in os.environ:
    content_length = int(os.environ['CONTENT_LENGTH'])
    request_body = sys.stdin.read(content_length)
    form = cgi.FieldStorage(fp=sys.stdin, environ=os.environ, keep_blank_values=True)


username = form.getvalue('username', 'Guest')
modified_html = get_modified_html(username)
print(modified_html)
