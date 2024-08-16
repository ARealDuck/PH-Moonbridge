#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>
#include <vector>
// NOTE: make sure to install compiler later or else this dont work! -Chito

class Logger
{
private:
    //define log levels within the logger
    enum loglevel {
        INFO,
        DEBUG,
        WARN,
        ERROR,
        FATAL,
    };
    //define structure of logging message under 
    struct logstruct
    {
        string logtime;
        string loglevel;
        string logmessage;
    };
    
public:
    //function to call to add logs to the logger
    void logging() {
        
    }
}