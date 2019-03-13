# Advanced Programming 
## Ap-lab
## Lab 2.4 Add syslog support to your logger
### Programming language: C


Now it's time to add support for Linux system logging into your logger that you implemented on lab2.2.

A new initLoggerfunction will be added in order to add support for choosing between stdout or syslog logging.

```c
int initLogger(char *logType)
```

##### You will handle the following log types:
- stdout or empty string for STDOUT logging
- syslog for SYSLOG logging

### General Requirements and Considerations

- Use the testLogger.c file for testing your logger.c library implementation.
- Use the Makefile for compilation.
- Update README.md with the proper steps for building and running your code.
- Don't forget to handle errors properly.
- Coding best practices implementation will be also considered.

The Logger library in C will be used for printing the following types of messages.

- INFO General information.
- WARN Warnings.
- ERROR Errors.
- PANIC Panics. Non recoverable issues with core dump.

#### Compile the Code:
Use the Makefile,just by typing:
```c
make
```

#### To run the program:
```c
./testLogger
```
#### Output:
An example of each type of message (stdout and syslog) will print.