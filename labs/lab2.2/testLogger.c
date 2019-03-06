int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char** argv){
    infof("Test Logger, General information. \n");
    warnf("Test Logger, Warning. \n");
    errorf("Test Logger, Error. \n");
    panicf("Test Logger, Panic. \n");
}