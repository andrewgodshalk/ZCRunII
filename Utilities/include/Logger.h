#ifndef GUARD_logger_h
#define GUARD_logger_h

/*------------------------------------------------------------------------------
  Logger class

  Created:  2016-10-?
  Modified: 2016-11-21

  Wrapper for spdlog library: https://github.com/gabime/spdlog
  Fomatting for spdlog is drawn from fmt library: https://github.com/fmtlib/fmt
  Formatting syntax almost identical to printf syntax (http://www.cplusplus.com/reference/cstdio/printf/),
    the main exception being that the preceeding ("%4.2f") is replaced with
    curly brackets ("{4.2f}").

  To do:
  - Find some way to make debug output prefix a standard length (see
      specification in NtupleProcessor.cpp :: processCommandLineInput())
  - Implement indentation levels?

  2016-11-21 - Added option to set usage for testing (no file output).

------------------------------------------------------------------------------*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"
#include "TimeStamp.h"

class Logger
{
  public:
    Logger( const char* ln,               // Name of the logger. Used as fileName unless otherwise specified.
            const std::string& pfx = "",  // Prefix output at beginning of line in log file.
            const std::string& fn = "",   // File name for file output.
            const std::string& fp = ""    // Path of file output.
          ) : logName_(ln), logPrefix_(pfx), logFormat_("%v"), fileName_(fn), logDir_(fp)
    { // Check for existing logger with same name.
        logger_ = spdlog::get(logName_);

      // Create logger if logger not found.
        if(!logger_)
        {   try
            { // Set up file name and location.
                if(logDir_=="") logDir_ = "logs/";
                if(fileName_=="") fileName_ = logName_;
                if(fileName_ != "NULL") fileName_ += "_" + TimeStamp().fn_str() + ".log";

              // Create sinks (outputs) for loggers
                sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
                sinks.push_back(std::make_shared<spdlog::sinks::stderr_sink_st>());
                if(fileName_ != "NULL") sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_st>((logDir_+fileName_).c_str()));

              // Create logger, to be accessed globally from all classes.
                logger_ = std::make_shared<spdlog::logger>(logName_.c_str(), begin(sinks), end(sinks));

              // Set logger and sink levels.
                logger_ ->set_level(spdlog::level::info);
                sinks[0]->set_level(spdlog::level::info);
                sinks[1]->set_level(spdlog::level::err );
                if(fileName_ != "NULL") sinks[2]->set_level(spdlog::level::info);

              // Set attributes and register logger in global list
                setFormat(logFormat_);
                spdlog::set_async_mode(4096);
                spdlog::register_logger(logger_);
            }
            catch (const spdlog::spdlog_ex& ex)
            {
                std::cout << "Log failed: " << ex.what() << std::endl;
            }
        }
    }

    ~Logger(){}

    void setPrefix(const std::string& pfx)
    { // Set prefix to logger
        logPrefix_ = pfx;
    }

    void setFormat(const std::string& fmt)
    { // Set log format
        logFormat_ = fmt;
        logger_->set_pattern(logFormat_.c_str());
    }

    void setDebug(bool dbg = true)
    { // Set logger and sinks to print at debug levels.
        if(dbg)
        {
            logger_ ->set_level(spdlog::level::trace);
            sinks[0]->set_level(spdlog::level::debug);
            if(fileName_ != "NULL") sinks[2]->set_level(spdlog::level::trace);
        }
        else
        {
            logger_ ->set_level(spdlog::level::info);
            sinks[1]->set_level(spdlog::level::info);
            if(fileName_ != "NULL") sinks[2]->set_level(spdlog::level::info);
        }
    }

    void setQuiet(bool qt = true)
    { // Sets stdout sink to print only on error
        if(qt) sinks[0]->set_level(spdlog::level::err );
        else   sinks[0]->set_level(spdlog::level::info);
    }

    // Functions that pass along messages to logger.
    template<typename... Args>void trace   (std::string msg, const Args&... args) { logger_->trace   ((logPrefix_+msg).c_str(), args...); }
    template<typename... Args>void debug   (std::string msg, const Args&... args) { logger_->debug   ((logPrefix_+msg).c_str(), args...); }
    template<typename... Args>void info    (std::string msg, const Args&... args) { logger_->info    ((logPrefix_+msg).c_str(), args...); }
    template<typename... Args>void warn    (std::string msg, const Args&... args) { logger_->warn    ((logPrefix_+msg).c_str(), args...); }
    template<typename... Args>void error   (std::string msg, const Args&... args) { logger_->error   ((logPrefix_+msg).c_str(), args...); }
    template<typename... Args>void critical(std::string msg, const Args&... args) { logger_->critical((logPrefix_+msg).c_str(), args...); }

  private:
    std::shared_ptr<spdlog::logger> logger_;
    std::vector<spdlog::sink_ptr> sinks;
    std::string logName_;
    std::string logPrefix_;
    std::string logFormat_;
    std::string fileName_;
    std::string logDir_;
};

#endif
