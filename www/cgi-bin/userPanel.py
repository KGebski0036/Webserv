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

# for key, value in form:
#     print("{}: {}<br>".format(key, value))

s = os.environ.get("BODY", '')

    
request_method = os.environ.get('REQUEST_METHOD', '')

if request_method == 'POST':
    # Get the length of the request body
    content_length = int(os.environ.get('CONTENT_LENGTH', 0))

    # Read the request body
    request_body = sys.stdin.read(content_length)
    parsed_body = cgi.parse_qs(request_body)

    # Get the username from the parsed body
    username = s.get('username', ['Guest'])[0]

else:
    # For other request methods (GET, etc.), get the username from the query string
    form = cgi.FieldStorage()
    username = form.getvalue('username', 'Guest')

modified_html = get_modified_html(username)
print(modified_html)
