# Party Pigeon
## Overview

### What?
A simple TCP-like custom network protocol with basic client and server applications written in C.

### Why?
This was originally made as a fun project to test my knowledge and to develop technical skills on low level networking and programming.

### How?
This program is essentially divided into two key components:
    - The "wing" protocol library which will contain code for server and client connections
    - The "PartyPigeon" app which will let users connect to a server to send messages

The protocol, client, and server, all use raw sockets which means that elevated permissions might be required to run and play around with it

[A quick demo!](https://youtu.be/1UKUZtn2j7I)

## Development Environment

This project was built and managed by a healthy combination of Makefiles and the CMake build utilities.

This project was built in C. An extensive list of all of the libraries that were used can be found in the codebase, but for reference they are mostly standard C libraries.

## Useful Websites

- [w3Schools C](https://www.w3schools.com/c/c_intro.php)
- [Geeks for Geeks](https://www.geeksforgeeks.org/c-language-introduction/)

## Future Work

- Add dynamic messaging
- Add dynamic server addresses
- Clean and make the code base more modular.

