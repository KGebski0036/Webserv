#!/usr/bin/env python3
import cgi
import cgitb
import os

cgitb.enable()

def handle_file_upload(fileitem):
    if fileitem.filename:
        filename = os.path.basename(fileitem.filename.replace(' ', '_'))
        upload_dir = '/path/to/your/upload/directory/'
        filepath = os.path.join(upload_dir, filename)

        with open(filepath, 'wb') as f:
            f.write(fileitem.file.read())

        return f"File '{filename}' uploaded successfully!"
    else:
        return "Error: No file selected for upload."


form = cgi.FieldStorage()

fileitem = form['file']

print("Content-type: text/html\n")

print("<html>")
print("<head><title>File Upload</title></head>")
print("<body>")

result = handle_file_upload(fileitem)
print(f"<p>{result}</p>")
print("</body>")
print("</html>")

