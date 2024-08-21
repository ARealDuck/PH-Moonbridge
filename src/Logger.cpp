#include "Logger.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

// Date and Time functions
string getCurrenttime() {
    auto now = chrono::system_clock::now();
    time_t ttime = chrono::system_clock::to_time_t(now);
    tm* ltime = localtime(&ttime);
    stringstream ts;
    ts << put_time(ltime, "%H:%M:%S");
    return ts.str();
}

string getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t ttime = chrono::system_clock::to_time_t(now);
    tm* ltime = localtime(&ttime);
    stringstream ts;
    ts << put_time(ltime, "%Y-%m-%d");
    return ts.str();
}

class Logger
{
private:
// Define Parameters for Logger
string file;
string loggertime;
string loggermessage;
vector <string> loggerhistory;

string addlogformatter(const string&time, string&message) {
    ostringstream ss;
    ss << time << message;
    return ss.str();
}

// Logger Constructor
Logger(string&time, string&message)
    : loggertime(time), loggermessage(message) {}

public:
// Logger init function
static Logger initlogger (string&message) {
    string time = getCurrenttime();
    return Logger(time, message);
}
// Addlog function for adding logs to loggerhistory
void Logger::addlog(string&message) {
    string time = getCurrenttime();
    string finallog = addlogformatter(time, message);
    loggerhistory.push_back(finallog);
    logfile();
}
//logfile update function
void Logger::logfile() {
    string filename = getCurrentDate() + ".txt";
    ofstream logfile(filename);
    try {
    if(logfile.is_open()) {
        for (const auto&  item : loggerhistory) {
            logfile << item << endl;
        }
        logfile.close();
    } else { 
        throw 1;
    }
    }
    catch (...) {
        string error01 = "[WARN] Unable to create file:" + filename + ".txt";
        addlog(error01);
    }
}
};