#include <iostream>
#include <vector>
#include <string>
using namespace std;

// The Logger Object to be created
class Logger
{
private:
    // Block to set loglevel data member
    // enum function to restrict loglevels to a specific string
    enum loglevels {
        INFO,
        WARN,
        ERROR,
        FATAL,
        DEBUG
    };

    // function to set enum values to string characters
    string to_string(loglevels allowedloglevels) {
        switch (allowedloglevels)
        {
        case INFO: return "[INFO]";
            break;
        case WARN: return "[WARN]";
            break;
        case ERROR: return "[ERROR]";
            break;
        case FATAL: return "[FATAL]";
            break;
        case DEBUG: return "[DEBUG]";
            break;
        default: return "[ERROR]";
            break;
        }

    }

    // Block to set the logtime data member
    // NOTE: data member should be set by a getlogtime function call made by the createlog function within public class section.
    string logtime;

    // Block to set logmessage data member
    // NOTE: data member should be set by the createlog function within the public class section.

    // Block to set the finallog data member
    // This should be created upon program launch
    struct finallog {
        string logtime; 
        string loglevels; 
        string logmessage;
    };
    
    // Log storage identifier 
    vector<finallog> logstorage;

public:
    //function to call to add logs to the logger
    void logging() {
        
    }
};