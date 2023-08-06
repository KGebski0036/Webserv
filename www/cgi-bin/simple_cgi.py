#!/usr/bin/env python

import cgi

# Get the input from the query string
form = cgi.FieldStorage()
input_name = form.getvalue("name", "Anonymous")

print("Content-type: text/html\r\n\r\n")
print("<html><head><title>Simple CGI Script</title></head><body>")
print("<h1>Hello, {}!</h1>".format(input_name))
print("</body></html>")
