int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char** argv){
    infof("Test Logger, General information; type: STDOUT\n");
    warnf("Test Logger, Warning; type: STDOUT \n");
    errorf("Test Logger, Error; type: STDOUT \n");
    panicf("Test Logger, Panic; type: STDOUT \n");

    infof("Printing on SYSLOG (/var/log/syslog)\n");
    initLogger("syslog");

    infof("Test Logger, General information; type: SYSLOG\n");
    warnf("Test Logger, Warning; type: SYSLOG \n");
    errorf("Test Logger, Error; type: SYSLOG \n");
    panicf("Test Logger, Panic; type: SYSLOG \n");
}