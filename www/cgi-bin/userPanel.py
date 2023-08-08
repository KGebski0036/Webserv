#!/usr/bin/env python3

import cgitb
import os
import sys

cgitb.enable()

def get_modified_html(username):
	with open('www/html/userPanel.html', 'r') as file:
		html_content = file.read()

	modified_html = html_content.replace('%USERNAME%', username)
	return modified_html

def get_error_html(message):
	with open('www/html/uncorrectLogin.html', 'r') as file:
		html_content = file.read()

	modified_html = html_content.replace('%MESSAGE%', message)
	return modified_html

request_method = os.environ.get('REQUEST_METHOD', '')
modified_html = ""

if request_method == 'POST':

	bodyDict = dict()

	rawbody = os.environ.get('BODY', "login=Guest")
	body = rawbody.split("&")

	for el in body:
		if '=' in el:
			key, val = el.strip().split("=")
			bodyDict[key] = val
		else:
			modified_html = get_error_html("Empty request")
			print(modified_html)
			sys.exit()
		
	credentials_dict = dict()
	with open("www/html/userFiles/databse.csv", "r+") as file:
		for line in file:
			login, password = line.strip().split(",")
			credentials_dict[login] = password

		login = bodyDict.get("login")
		password = bodyDict.get("password")

		if login in credentials_dict:
			saved_password = credentials_dict[login]

			if (password == saved_password):
				modified_html = get_modified_html(login)
			else:
				modified_html = get_error_html("Inccorect password")

		else:
			
			if (login != "" and password != ""):
				modified_html = get_modified_html(login)
				file.write(login + "," + password + "\n")

else:
	modified_html = get_error_html("Invalid method")

print(modified_html)
