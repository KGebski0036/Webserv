# Webserv

This project is about writing own HTTP server.

## Tehnologies

<div align="center">
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" height="30" alt="cplusplus  logo"  />
</div>

## Requirements

- Use C++ features wherever possible, preferring C++ versions of functions over C functions.
- Avoid using external libraries and specifically exclude Boost libraries.
- The server should be executable with a configuration file argument.
- Implement a non-blocking HTTP server.
- Use a single poll() or equivalent mechanism for all I/O operations.
- Ensure simultaneous checking for read and write operations.
- Avoid direct read or write operations without going through the polling mechanism.
- Use system calls and functions as listed, including but not limited to `socket`, `accept`, `listen`, `send`, `recv`.
- Handle HTTP methods like GET, POST, DELETE.
- Serve static websites, handle client file uploads.
- Stress test the server to ensure availability.
- Do not use fork for purposes other than CGI, ensuring the server's primary function is not compromised.

## Screenshots

Start of webserv:
![Screenshot](screenshots/00.png)
Start of webserv with diffrent config:
![Screenshot](screenshots/01.png)
Example of hosted htmls files:
![Screenshot](screenshots/02.gif)
Logger logging actions on page:
![Screenshot](screenshots/03.png)
Login form:
![Screenshot](screenshots/04.png)
Fresh user page:
![Screenshot](screenshots/05.png)
User can update avatar:
![Screenshot](screenshots/06.png)
Indexing:
![Screenshot](screenshots/07.png)
