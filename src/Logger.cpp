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
string logger::get_current_time() {
    auto now = chrono::system_clock::now();
    time_t ttime = chrono::system_clock::to_time_t(now);
    tm* ltime = localtime(&ttime);
    stringstream ts;
    ts << put_time(ltime, "%H:%M:%S");
    return ts.str();
}

string logger::get_current_date() {
    auto now = chrono::system_clock::now();
    time_t ttime = chrono::system_clock::to_time_t(now);
    tm* ltime = localtime(&ttime);
    stringstream ts;
    ts << put_time(ltime, "%Y-%m-%d");
    return ts.str();
}

// Define Parameters for Logger
string logger::addlogformatter(const string&time, string&message) {
    ostringstream ss;
    ss << time << message;
    return ss.str();
}

public:
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
