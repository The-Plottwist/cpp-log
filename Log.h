//BISMILLAH

/*
<For logging in c++. "Log.h" header file.>
    Copyright (C) <2020>  <The_Plottwist>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//USAGE:
//To use this library you must first define a global variable.
//Log lg{"FILE_NAME.log", "DIR_NAME or PATH", "CONSOLE_LEVEL", "FILE_LEVEL"};

//You can only access the commands with that variable.
//Available commands: 
/*
lg.debug("message", variable *OPTIONAL, variable *OPTIONAL),
lg.info(...),
lg.error(...),
lg.warning(...)
lg.critical(...)
lg.get_path();
lg.get_file_name();

//Example program:

//#include <iostream>
//Log lg{"Experiment.log", "LOG", "warning", "info"};

//...

//int main () {
//  int some_var = 5;
//  lg.info("This message will not be printed to the console but it will be written to the \"LOG/Experiment.log\" file.")
//  lg.critical("This message will be printed to console and will be written to the \"LOG/Experiment.log\" file.");
//  lg.critical("some_var equals: ", some_var);
//  return 0;
//}


#ifndef Log_H
#define Log_H

#ifdef _WIN32
#define FOLDER_SEPERATOR "\\"
#include <direct.h>
#define MAKE_DIRECTORY mkdir(Path.c_str());

#else
#define FOLDER_SEPERATOR "/"
#include <sys/stat.h>
#define MAKE_DIRECTORY mkdir(Path.c_str(),0777);
#endif


#include <iostream>
#include <string>

//write file
#include <fstream>

//date time
#include <chrono>
#include <ctime>


class Log {

    enum LOG_LEVELS {

        DEBUG,
        INFO,
        ERROR,
        WARNING,
        CRITICAL
    };

    //file
    std::string Path;
    std::string File_Name;
    LOG_LEVELS file_level;
    LOG_LEVELS console_level;
    std::ofstream File;

    //time
    std::time_t rawtime;
    std::tm *rawdate;
    const std::chrono::system_clock::time_point rawms_start;
    std::chrono::milliseconds rawms;

    int year;
    int month;
    int day;

    int hour;
    int min;
    int sec;
    int ms;

public:

    Log (std::string fname, std::string pth, std::string cn_lvl, std::string fl_lvl)
    :rawdate(nullptr), rawms_start(std::chrono::system_clock::now()), File(Path + FOLDER_SEPERATOR + File_Name, std::ios::app) {

        set_path(pth);
        set_file(fname);
        set_fl_lvl(fl_lvl);
        set_cn_lvl(cn_lvl);

        //clear/make log
        std::ofstream clear(Path + FOLDER_SEPERATOR + File_Name);
        clear << "";
        clear.close();
    }

    //File
    void set_path(const std::string &pth) { Path = pth; }
    void set_file(const std::string &fname) { File_Name = fname; }
    void set_fl_lvl(const std::string &fl_lvl) {

        if (fl_lvl == "debug")
            file_level = DEBUG;
        if (fl_lvl == "info")
            file_level = INFO;
        if (fl_lvl == "error")
            file_level = ERROR;
        if (fl_lvl == "warning")
            file_level = WARNING;
        if (fl_lvl == "critical")
            file_level = CRITICAL;
    }
    void set_cn_lvl(const std::string &cn_lvl) {

        if (cn_lvl == "debug")
            console_level = DEBUG;
        if (cn_lvl == "info")
            console_level = INFO;
        if (cn_lvl == "error")
            console_level = ERROR;
        if (cn_lvl == "warning")
            console_level = WARNING;
        if (cn_lvl == "critical")
            console_level = CRITICAL;
    }
    std::string get_path() const { return Path; }
    std::string get_file_name() const { return File_Name; }

    //Log functions
    void debug(const std::string &message) { Write_LOG(DEBUG, message); }
    void debug(const std::string &message, const double &variable) { Write_LOG(DEBUG, message, variable); }
    void debug(const std::string &message, const double &variable, const double &variable2) { Write_LOG(DEBUG, message, variable, variable2); }

    void info(const std::string &message) { Write_LOG(INFO, message); }
    void info(const std::string &message, const double &variable) { Write_LOG(INFO, message, variable); }
    void info(const std::string &message, const double &variable, const double &variable2) { Write_LOG(INFO, message, variable, variable2); }

    void error(const std::string &message) { Write_LOG(ERROR, message); }
    void error(const std::string &message, const double &variable) { Write_LOG(ERROR, message, variable); }
    void error(const std::string &message, const double &variable, const double &variable2) { Write_LOG(ERROR, message, variable, variable2); }

    void warning(const std::string &message) { Write_LOG(WARNING, message); }
    void warning(const std::string &message, const double &variable) { Write_LOG(WARNING, message, variable); }
    void warning(const std::string &message, const double &variable, const double &variable2) { Write_LOG(WARNING, message, variable, variable2); }

    void critical(const std::string &message) { Write_LOG(CRITICAL, message); }
    void critical(const std::string &message, const double &variable) { Write_LOG(CRITICAL, message, variable); }
    void critical(const std::string &message, const double &variable, const double &variable2) { Write_LOG(CRITICAL, message, variable, variable2); }

    void Write_LOG(const LOG_LEVELS &lg_lvl, const std::string &message) {

        std::string level = "";
        switch (lg_lvl) {
            case DEBUG:
                level = "DEBUG";
                break;
            case INFO:
                level = "INFO";
                break;
            case ERROR:
                level = "ERROR";
                break;
            case WARNING:
                level = "WARNING";
                break;
            case CRITICAL:
                level = "CRITICAL";
                break;
            default:
                level = "UNKNOWN_LEVEL";
                break;
        }

        using namespace std::chrono;
        system_clock::time_point now = system_clock::now();
        rawtime = system_clock::to_time_t(now);
        rawdate = localtime(&rawtime);

        year = 1900 + rawdate->tm_year;
        month = 1 + rawdate->tm_mon;
        day = rawdate->tm_mday;

        hour = rawdate->tm_hour;
        min = rawdate->tm_min;
        sec = rawdate->tm_sec;

        rawms = duration_cast <milliseconds> (now - rawms_start) %1000;
        ms = rawms.count();

        MAKE_DIRECTORY
        if (lg_lvl >= console_level) {

            std::cout << "[";
            if (day < 10)
                std::cout << "0";
            std::cout << day << "-";
            if (month < 10)
                std::cout << "0";
            std::cout << month << "-" << year << "]" << " ";

            std::cout << "[";
            if (hour < 10)
                std::cout << "0";
            std::cout << hour << ":";
            if (min < 10)
                std::cout << "0";
            std::cout << min << ":" << sec << "] " << ms << "ms";

            std::cout << " :" << level << ": ";
            std::cout << message << std::endl;
        }
        if (lg_lvl >= file_level) {

            File << "[";
            if (day < 10)
                File << "0";
            File << day << "-";
            if (month < 10)
                File << "0";
            File << month << "-" << year << "]" << " ";

            File << "[";
            if (hour < 10)
                File << "0";
            File << hour << ":";
            if (min < 10)
                File << 0;
            File << min << ":" << sec << "] " << ms << "ms";

            File << " :" << level << ": ";
            File << message << std::endl;
        }
    }
    void Write_LOG(const LOG_LEVELS &lg_lvl, const std::string &message, const double &variable) {

        std::string level = "";
        switch (lg_lvl) {
            case DEBUG:
                level = "DEBUG";
                break;
            case INFO:
                level = "INFO";
                break;
            case ERROR:
                level = "ERROR";
                break;
            case WARNING:
                level = "WARNING";
                break;
            case CRITICAL:
                level = "CRITICAL";
                break;
            default:
                level = "UNKNOWN_LEVEL";
                break;
        }

        using namespace std::chrono;
        system_clock::time_point now = system_clock::now();
        rawtime = system_clock::to_time_t(now);
        rawdate = localtime(&rawtime);

        year = 1900 + rawdate->tm_year;
        month = 1 + rawdate->tm_mon;
        day = rawdate->tm_mday;

        hour = rawdate->tm_hour;
        min = rawdate->tm_min;
        sec = rawdate->tm_sec;

        rawms = duration_cast <milliseconds> (now - rawms_start) %1000;
        ms = rawms.count();

        MAKE_DIRECTORY
        if (lg_lvl >= console_level) {

            std::cout << "[";
            if (day < 10)
                std::cout << "0";
            std::cout << day << "-";
            if (month < 10)
                std::cout << "0";
            std::cout << month << "-" << year << "]" << " ";

            std::cout << "[";
            if (hour < 10)
                std::cout << "0";
            std::cout << hour << ":";
            if (min < 10)
                std::cout << "0";
            std::cout << min << ":" << sec << "] " << ms << "ms";

            std::cout << " :" << level << ": ";
            std::cout << message << variable << std::endl;
        }
        if (lg_lvl >= file_level) {

            File << "[";
            if (day < 10)
                File << "0";
            File << day << "-";
            if (month < 10)
                File << "0";
            File << month << "-" << year << "]" << " ";

            File << "[";
            if (hour < 10)
                File << "0";
            File << hour << ":";
            if (min < 10)
                File << 0;
            File << min << ":" << sec << "] " << ms << "ms";

            File << " :" << level << ": ";
            File << message << variable << std::endl;
        }
    }
    void Write_LOG(const LOG_LEVELS &lg_lvl, const std::string &message, const double &variable, const double &variable2) {

        std::string level = "";
        switch (lg_lvl) {
            case DEBUG:
                level = "DEBUG";
                break;
            case INFO:
                level = "INFO";
                break;
            case ERROR:
                level = "ERROR";
                break;
            case WARNING:
                level = "WARNING";
                break;
            case CRITICAL:
                level = "CRITICAL";
                break;
            default:
                level = "UNKNOWN_LEVEL";
                break;
        }

        using namespace std::chrono;
        system_clock::time_point now = system_clock::now();
        rawtime = system_clock::to_time_t(now);
        rawdate = localtime(&rawtime);

        year = 1900 + rawdate->tm_year;
        month = 1 + rawdate->tm_mon;
        day = rawdate->tm_mday;

        hour = rawdate->tm_hour;
        min = rawdate->tm_min;
        sec = rawdate->tm_sec;

        rawms = duration_cast <milliseconds> (now - rawms_start) %1000;
        ms = rawms.count();

        MAKE_DIRECTORY
        if (lg_lvl >= console_level) {

            std::cout << "[";
            if (day < 10)
                std::cout << "0";
            std::cout << day << "-";
            if (month < 10)
                std::cout << "0";
            std::cout << month << "-" << year << "]" << " ";

            std::cout << "[";
            if (hour < 10)
                std::cout << "0";
            std::cout << hour << ":";
            if (min < 10)
                std::cout << "0";
            std::cout << min << ":" << sec << "] " << ms << "ms";

            std::cout << " :" << level << ": ";
            std::cout << message << variable << ", " << variable2 << std::endl;
        }
        if (lg_lvl >= file_level) {

            File << "[";
            if (day < 10)
                File << "0";
            File << day << "-";
            if (month < 10)
                File << "0";
            File << month << "-" << year << "]" << " ";

            File << "[";
            if (hour < 10)
                File << "0";
            File << hour << ":";
            if (min < 10)
                File << 0;
            File << min << ":" << sec << "] " << ms << "ms";

            File << " :" << level << ": ";
            File << message << variable << ", " << variable2 << std::endl;
        }
    }
    ~Log () {

        //closing the file
        std::ofstream File(Path + FOLDER_SEPERATOR + File_Name, std::ios::app);
        File.close();
    }


};

#endif
