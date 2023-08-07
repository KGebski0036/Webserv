#!/usr/bin/env python3
import cgi
import cgitb
import sys
import os

# Enable CGI script debugging
cgitb.enable()

# Function to read and modify the template HTML file
def get_modified_html(username):
    with open('/home/sztorm/webserv/www/html/uploadFile.html', 'r') as file:
        html_content = file.read()

    # Replace the placeholder %USERNAME% with the actual username
    modified_html = html_content.replace('%USERNAME%', username)
    return modified_html

# Main CGI script logic
def main():
    # Parse the form data
    form = cgi.FieldStorage()

    # If the script is called with HTTP POST, read the request body data
    if 'CONTENT_LENGTH' in os.environ:
        content_length = int(os.environ['CONTENT_LENGTH'])
        request_body = sys.stdin.read(content_length)
        form = cgi.FieldStorage(fp=sys.stdin, environ=os.environ, keep_blank_values=True)

    # Get the value of the 'username' parameter from the form
    username = form.getvalue('username', 'Guest')

    # Set the content type to HTML
    # print("Content-type: text/html\n")

    # Get the modified HTML content
    modified_html = get_modified_html(username)

    # Return the modified HTML content as the response
    print(modified_html)

if __name__ == '__main__':
    main()
