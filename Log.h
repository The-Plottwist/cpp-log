//BISMILLAH

/* -------------------------------- COPYRIGHT -------------------------------

    <C++ Thread safe Logging library>
    Copyright (C) <2020>  <Fatih Yeğin>

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

-------------------------------------------------------------------------- */

//USAGE:
//Define a global object:
//Log lg{"FILE_NAME.log", "DIR_NAME or PATH", CONSOLE_LEVEL, FILE_LEVEL};

//Use that object for logging.

//Available commands are:

/*
debug("message", variable OPTIONAL),
info(...),
error(...),
warning(...)
critical(...)


set_path("some string");
set_file_name("...");

get_path();      //returns std::stirng
get_file_name(); //returns std::stirng
*/

//Example program:

/*
#//include <iostream>
#//include "cpp-log/Log.h"
Log lg{"Experiment.log", "LOG", Log::LEVEL::WARNING, Log::LEVEL::INFO};

...

int main () {
  int some_var {5};
  bool some_other_var{false};
  
  lg.info("This message will not be printed to the console but it will be written to the \"LOG/Experiment.log\" file.")
  lg.warning("This message will be printed to console and will be written to the \"LOG/Experiment.log\" file.");
  lg.critical("some_var equals: ", some_var);
  lg.critical("some_var equals: ", some_other_var);
  
  return 0;
} */

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

#ifdef _GLIBCXX_THREAD
#define MUTEX_LOCK_ write.lock();
#define MUTEX_UNLOCK_ write.unlock();
#else
#define MUTEX_LOCK_ 
#define MUTEX_UNLOCK_ 
#endif

#include <iostream>
#include <string>

#include <mutex>

//file error
#include <cassert>

//write file
#include <fstream>

//date time
#include <chrono>
#include <ctime>


class Log {

public:
    
    enum LEVEL {
    
        DEBUG,
        INFO,
        ERROR,
        WARNING,
        CRITICAL,
        DISABLED = 999
    };
    
private:

    enum VAR_TYPE {
    
        BOOL,
        CHAR,
        INT,
        LONG_INT,
        LONG_LONG_INT,
        UNSIGNED_INT,
        LONG_UNSIGNED_INT,
        LONG_LONG_UNSIGNED_INT,
        FLOAT,
        DOUBLE,
        LONG_DOUBLE
    };

    std::mutex write;

    std::string Path;
    std::string File_Name;
    
    LEVEL file_level;
    LEVEL console_level;

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
    
/* -------------------------------- VARIABLES ------------------------------- */

    bool *bool_;

    char *char_;

    int *int_;
    long int *li;
    long long int *lli;
    
    unsigned int *ui;
    long unsigned int *lui;
    long long unsigned int *llui;
    
    float *float_;

    double *double_;
    long double *ld;
    
/* -------------------------------- VARIABLES ------------------------------- */
    
public:

    Log (const std::string &fname, const std::string &pth, const LEVEL cn_lvl, const LEVEL fl_lvl)
    :rawdate(nullptr), rawms_start(std::chrono::system_clock::now()),
    bool_{nullptr}, char_{nullptr}, int_{nullptr}, li{nullptr}, lli{nullptr}, ui{nullptr}, lui{nullptr}, llui{nullptr}, float_{nullptr}, double_{nullptr}, ld{nullptr} {

        set_path(pth);
        set_file_name(fname);
        set_fl_lvl(fl_lvl);
        set_cn_lvl(cn_lvl);

        //clear/make log
        std::ofstream clear(Path + FOLDER_SEPERATOR + File_Name, std::ios::trunc);
        clear.close();
    }

    ~Log () {
        
        delete bool_;
        delete char_;
        delete int_;
        delete li;
        delete lli;
        delete ui;
        delete lui;
        delete llui;
        delete float_;
        delete double_;
        delete ld;
    }

/* ------------------------------- File values ------------------------------ */

    void set_path(const std::string &pth) { Path = pth; }
    
    void set_file_name(const std::string &fname) { File_Name = fname; }

    std::string path() const { return Path; }
    
    std::string file_name() const { return File_Name; }

/* --------------------------------- Levels --------------------------------- */

    void set_fl_lvl(const LEVEL &fl_lvl) { file_level = fl_lvl; }
    
    void set_cn_lvl(const LEVEL &cn_lvl) { console_level = cn_lvl; }

/* ------------------------------ Log functions ----------------------------- */


    /* ---------------------------------- DEBUG --------------------------------- */

    void debug(const std::string &message) {
    
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- BOOL ---------------------------------- */
    void debug(const std::string &message, const bool variable) {
        
        if (bool_ == nullptr) bool_ = new bool;
        *bool_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::BOOL);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- CHAR ---------------------------------- */
    void debug(const std::string &message, const char &variable) {
        
        if (char_ == nullptr) char_ = new char;
        *char_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::CHAR);
        MUTEX_UNLOCK_
    }
    


    void debug(const std::string &message, const int variable) {
        
        if (int_ == nullptr) int_ = new int;
        *int_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::INT);
        MUTEX_UNLOCK_
    }
    
    void debug(const std::string &message, const long int &variable) {
        
        if (li == nullptr) li = new long int;
        *li = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void debug(const std::string &message, const long long int &variable) {
        
        if (lli == nullptr) lli = new long long int;
        *lli = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::LONG_LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void debug(const std::string &message, const unsigned int &variable) {
        
        if (ui == nullptr) ui = new unsigned int;
        *ui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void debug(const std::string &message, const long unsigned int &variable) {
        
        if (lui == nullptr) lui = new long unsigned int;
        *lui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void debug(const std::string &message, const long long unsigned int &variable) {
        
        if (llui == nullptr) llui = new long long unsigned int;
        *llui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::LONG_LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    

    /* ---------------------------------- FLOAT --------------------------------- */
    void debug(const std::string &message, const float &variable) {
        
        if (float_ == nullptr) float_ = new float;
        *float_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::FLOAT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- DOUBLE --------------------------------- */
    void debug(const std::string &message, const double &variable) {
        
        if (double_ == nullptr) double_ = new double;
        *double_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::DOUBLE);
        MUTEX_UNLOCK_
    }
    
    void debug(const std::string &message, const long double &variable) {
        
        if (ld == nullptr) ld = new long double;
        *ld = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::DEBUG, message, VAR_TYPE::LONG_DOUBLE);
        MUTEX_UNLOCK_
    }
    

    /* ---------------------------------- DEBUG --------------------------------- */


    /* ---------------------------------- INFO ---------------------------------- */

    void info(const std::string &message) {
    
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- BOOL ---------------------------------- */
    void info(const std::string &message, const bool variable) {
        
        if (bool_ == nullptr) bool_ = new bool;
        *bool_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::BOOL);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- CHAR ---------------------------------- */
    void info(const std::string &message, const char &variable) {
        
        if (char_ == nullptr) char_ = new char;
        *char_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::CHAR);
        MUTEX_UNLOCK_
    }
    

    /* ----------------------------------- INT ---------------------------------- */
    void info(const std::string &message, const int variable) {
        
        if (int_ == nullptr) int_ = new int;
        *int_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::INT);
        MUTEX_UNLOCK_
    }
    
    void info(const std::string &message, const long int &variable) {
        
        if (li == nullptr) li = new long int;
        *li = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void info(const std::string &message, const long long int &variable) {
        
        if (lli == nullptr) lli = new long long int;
        *lli = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::LONG_LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void info(const std::string &message, const unsigned int &variable) {
        
        if (ui == nullptr) ui = new unsigned int;
        *ui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void info(const std::string &message, const long unsigned int &variable) {
        
        if (lui == nullptr) lui = new long unsigned int;
        *lui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void info(const std::string &message, const long long unsigned int &variable) {
        
        if (llui == nullptr) llui = new long long unsigned int;
        *llui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::LONG_LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    

    /* ---------------------------------- FLOAT --------------------------------- */
    void info(const std::string &message, const float &variable) {
        
        if (float_ == nullptr) float_ = new float;
        *float_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::FLOAT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- DOUBLE --------------------------------- */
    void info(const std::string &message, const double &variable) {
        
        if (double_ == nullptr) double_ = new double;
        *double_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::DOUBLE);
        MUTEX_UNLOCK_
    }
    
    void info(const std::string &message, const long double &variable) {
        
        if (ld == nullptr) ld = new long double;
        *ld = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::INFO, message, VAR_TYPE::LONG_DOUBLE);
        MUTEX_UNLOCK_
    }
    

    /* ---------------------------------- INFO ---------------------------------- */


    /* ---------------------------------- ERROR --------------------------------- */
    
    void error(const std::string &message) {
    
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- BOOL ---------------------------------- */
    void error(const std::string &message, const bool variable) {
        
        if (bool_ == nullptr) bool_ = new bool;
        *bool_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::BOOL);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- CHAR ---------------------------------- */
    void error(const std::string &message, const char &variable) {
        
        if (char_ == nullptr) char_ = new char;
        *char_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::CHAR);
        MUTEX_UNLOCK_
    }
    

    /* ----------------------------------- INT ---------------------------------- */
    void error(const std::string &message, const int variable) {
        
        if (int_ == nullptr) int_ = new int;
        *int_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::INT);
        MUTEX_UNLOCK_
    }
    
    void error(const std::string &message, const long int &variable) {
        
        if (li == nullptr) li = new long int;
        *li = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void error(const std::string &message, const long long int &variable) {
        
        if (lli == nullptr) lli = new long long int;
        *lli = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::LONG_LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void error(const std::string &message, const unsigned int &variable) {
        
        if (ui == nullptr) ui = new unsigned int;
        *ui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void error(const std::string &message, const long unsigned int &variable) {
        
        if (lui == nullptr) lui = new long unsigned int;
        *lui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void error(const std::string &message, const long long unsigned int &variable) {
        
        if (llui == nullptr) llui = new long long unsigned int;
        *llui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::LONG_LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- FLOAT --------------------------------- */
    void error(const std::string &message, const float &variable) {
        
        if (float_ == nullptr) float_ = new float;
        *float_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::FLOAT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- DOUBLE --------------------------------- */

    void error(const std::string &message, const double &variable) {
        
        if (double_ == nullptr) double_ = new double;
        *double_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::DOUBLE);
        MUTEX_UNLOCK_
    }
    
    void error(const std::string &message, const long double &variable) {
        
        if (ld == nullptr) ld = new long double;
        *ld = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::ERROR, message, VAR_TYPE::LONG_DOUBLE);
        MUTEX_UNLOCK_
    }
    

    /* ---------------------------------- ERROR --------------------------------- */


    /* --------------------------------- WARNING -------------------------------- */
    
    void warning(const std::string &message) {
    
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- BOOL ---------------------------------- */
    void warning(const std::string &message, const bool variable) {
        
        if (bool_ == nullptr) bool_ = new bool;
        *bool_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::BOOL);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- CHAR ---------------------------------- */
    void warning(const std::string &message, const char &variable) {
        
        if (char_ == nullptr) char_ = new char;
        *char_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::CHAR);
        MUTEX_UNLOCK_
    }
    

    /* ----------------------------------- INT ---------------------------------- */
    void warning(const std::string &message, const int variable) {
        
        if (int_ == nullptr) int_ = new int;
        *int_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::INT);
        MUTEX_UNLOCK_
    }
    
    void warning(const std::string &message, const long int &variable) {
        
        if (li == nullptr) li = new long int;
        *li = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void warning(const std::string &message, const long long int &variable) {
        
        if (lli == nullptr) lli = new long long int;
        *lli = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::LONG_LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void warning(const std::string &message, const unsigned int &variable) {
        
        if (ui == nullptr) ui = new unsigned int;
        *ui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void warning(const std::string &message, const long unsigned int &variable) {
        
        if (lui == nullptr) lui = new long unsigned int;
        *lui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void warning(const std::string &message, const long long unsigned int &variable) {
        
        if (llui == nullptr) llui = new long long unsigned int;
        *llui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::LONG_LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- FLOAT --------------------------------- */
    void warning(const std::string &message, const float &variable) {
        
        if (float_ == nullptr) float_ = new float;
        *float_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::FLOAT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- DOUBLE --------------------------------- */
    void warning(const std::string &message, const double &variable) {
        
        if (double_ == nullptr) double_ = new double;
        *double_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::DOUBLE);
        MUTEX_UNLOCK_
    }
    
    void warning(const std::string &message, const long double &variable) {
        
        if (ld == nullptr) ld = new long double;
        *ld = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::WARNING, message, VAR_TYPE::LONG_DOUBLE);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- WARNING -------------------------------- */
    
    
    /* -------------------------------- CRITICAL -------------------------------- */
    
    void critical(const std::string &message) {
    
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- BOOL ---------------------------------- */
    void critical(const std::string &message, const bool variable) {
        
        if (bool_ == nullptr) bool_ = new bool;
        *bool_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::BOOL);
        MUTEX_UNLOCK_
    }
    
    /* ---------------------------------- CHAR ---------------------------------- */
    void critical(const std::string &message, const char &variable) {
        
        if (char_ == nullptr) char_ = new char;
        *char_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::CHAR);
        MUTEX_UNLOCK_
    }
    

    /* ----------------------------------- INT ---------------------------------- */
    void critical(const std::string &message, const int variable) {
        
        if (int_ == nullptr) int_ = new int;
        *int_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::INT);
        MUTEX_UNLOCK_
    }
    
    void critical(const std::string &message, const long int &variable) {
        
        if (li == nullptr) li = new long int;
        *li = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void critical(const std::string &message, const long long int &variable) {
        
        if (lli == nullptr) lli = new long long int;
        *lli = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::LONG_LONG_INT);
        MUTEX_UNLOCK_
    }
    
    void critical(const std::string &message, const unsigned int &variable) {
        
        if (ui == nullptr) ui = new unsigned int;
        *ui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void critical(const std::string &message, const long unsigned int &variable) {
        
        if (lui == nullptr) lui = new long unsigned int;
        *lui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    
    void critical(const std::string &message, const long long unsigned int &variable) {
        
        if (llui == nullptr) llui = new long long unsigned int;
        *llui = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::LONG_LONG_UNSIGNED_INT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- FLOAT --------------------------------- */
    void critical(const std::string &message, const float &variable) {
        
        if (float_ == nullptr) float_ = new float;
        *float_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::FLOAT);
        MUTEX_UNLOCK_
    }
    

    /* --------------------------------- DOUBLE --------------------------------- */
    void critical(const std::string &message, const double &variable) {
        
        if (double_ == nullptr) double_ = new double;
        *double_ = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::DOUBLE);
        MUTEX_UNLOCK_
    }
    
    void critical(const std::string &message, const long double &variable) {
        
        if (ld == nullptr) ld = new long double;
        *ld = variable;
        
        MUTEX_LOCK_
        Write_LOG(LEVEL::CRITICAL, message, VAR_TYPE::LONG_DOUBLE);
        MUTEX_UNLOCK_
    }
    

    /* -------------------------------- CRITICAL -------------------------------- */


/* --------------------------------- Writing -------------------------------- */

    void Write_LOG(const LEVEL &lg_lvl, const std::string &message) {

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
    
    std::ofstream File(Path + FOLDER_SEPERATOR + File_Name, std::ios::app);
        
        assert((File.is_open()) && "Log file couldn't opened.");
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
    
    File.close();
    }
    
    void Write_LOG(const LEVEL &lg_lvl, const std::string &message, const VAR_TYPE type_) {

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
            std::cout << message; 
            
            switch (type_) {
        
                case BOOL:
                    if (*bool_) std::cout << "TRUE";
                    else std::cout << "FALSE";
                    break;
                
                case CHAR:
                    std::cout << *char_;
                    break;
                
                case INT:
                    std::cout << *int_;
                    break;
                
                case LONG_INT:
                    std::cout << *li;
                    break;
                    
                case LONG_LONG_INT:
                    std::cout << *lli;
                    break;
                
                case UNSIGNED_INT:
                    std::cout << *ui;
                    break;
                
                case LONG_UNSIGNED_INT:
                    std::cout << *lui;
                    break;
                    
                case LONG_LONG_UNSIGNED_INT:
                    std::cout << *llui;
                    break;
                
                case FLOAT:
                    std::cout << *float_;
                    break;
                
                case DOUBLE:
                    std::cout << *double_;
                    break;
                
                case LONG_DOUBLE:
                    std::cout << *ld;
                    break;
                
                default:
                    break;
            }
        
            std::cout << std::endl;
        }
    
    std::ofstream File(Path + FOLDER_SEPERATOR + File_Name, std::ios::app);
        
        assert((File.is_open()) && "Log file couldn't opened.");
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
            File << message;
            
            switch (type_) {
        
                case BOOL:
                    if (*bool_) File << "TRUE";
                    else File << "FALSE";
                    break;
                
                case CHAR:
                    File << *char_;
                    break;
                
                case INT:
                    File << *int_;
                    break;
                
                case LONG_INT:
                    File << *li;
                    break;
                    
                case LONG_LONG_INT:
                    File << *lli;
                    break;
                
                case UNSIGNED_INT:
                    File << *ui;
                    break;
                
                case LONG_UNSIGNED_INT:
                    File << *lui;
                    break;
                    
                case LONG_LONG_UNSIGNED_INT:
                    File << *llui;
                    break;
                
                case FLOAT:
                    File << *float_;
                    break;
                
                case DOUBLE:
                    File << *double_;
                    break;
                
                case LONG_DOUBLE:
                    File << *ld;
                    break;
                
                default:
                    break;
            }
    
            File << std::endl;
        }
    
    File.close();
    }
};

#endif
