#!/usr/bin/env python3
import cgi
import cgitb
import os

# Enable CGI script debugging
cgitb.enable()

# Function to handle file upload
def handle_file_upload(fileitem):
    # Check if the file was successfully uploaded
    if fileitem.filename:
        # Replace any spaces in the filename with underscores
        filename = os.path.basename(fileitem.filename.replace(' ', '_'))
        # Set the path where the uploaded file will be saved
        upload_dir = '/path/to/your/upload/directory/'  # Change this to your desired directory path
        filepath = os.path.join(upload_dir, filename)

        # Save the file to the specified directory
        with open(filepath, 'wb') as f:
            f.write(fileitem.file.read())

        return f"File '{filename}' uploaded successfully!"
    else:
        return "Error: No file selected for upload."

# Main CGI script logic
def main():
    # Parse the form data
    form = cgi.FieldStorage()

    # Get the uploaded file from the form data
    fileitem = form['file']

    # Set the content type to HTML
    print("Content-type: text/html\n")

    # HTML response
    print("<html>")
    print("<head><title>File Upload</title></head>")
    print("<body>")

    # Handle the file upload and display the result
    result = handle_file_upload(fileitem)
    print(f"<p>{result}</p>")

    print("</body>")
    print("</html>")

if __name__ == '__main__':
    main()
