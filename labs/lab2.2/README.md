# Advanced Programming 
## Ap-lab
## Lab 2.2 Logger Library
### Programming language: C

Implement a Logger library in C that will be used for printing the following types of messages.

- INFO General information.
- WARN Warnings.
- ERROR Errors.
- PANIC Panics. Non recoverable issues with core dump.

This logger library will be used instead of printf function calls in all new labs and challenges that we'll be doing in the course. Below you can see the prototype for each function.

### Functions
```c
int infof(const char *format, ...)
int warnf(const char *format, ...)
int errorf(const char *format, ...)
int panicf(const char *format, ...)
```

### General Requirements and Considerations

- Use the logger.c file for your implementation.
- Update README.md with the proper steps for building and running your code.
- Use the testLogger.c file for testing all your logger functions.
- Use different font color for each of the log types. For colors references go to: https://www.linuxjournal.com/article/8603
- Don't forget to handle errors properly.
- Coding best practices implementation will be also considered.

#### Running the Code:
gcc testLogger.c logger.c -o testLogger &nbsp;
./testLogger
 

#### Expected Output:
22:57:47 INFO Test Logger, General information. &nbsp;
22:57:47 WARN Test Logger, Warning. &nbsp;
22:57:47 ERROR Test Logger, Error. &nbsp;
22:57:47 PANIC Test Logger, Panic. &nbsp;