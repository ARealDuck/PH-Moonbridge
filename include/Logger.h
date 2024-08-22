#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
using namespace std;
class logger {
private:
// Storage methods declared for object
    string file;
    string loggertime;
    string loggermessage;
    vector <string> loggerhistory;
    // time and date methods
    string get_current_time();
    string get_current_date();
    // formatter method used by the addlog function
    string addlogformatter(const string &time, string &message);

    // Constructor to create log storage
    logger(string &time, string &message)
        : loggertime(time), loggermessage(message) {}

public:
// logger contructor init function
static logger initlogger (string&message) {
    string time = getCurrenttime();
    return logger(time, message);
}


}
#endif