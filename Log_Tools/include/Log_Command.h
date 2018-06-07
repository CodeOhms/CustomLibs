#ifndef LOG_COMMAND_H
#define LOG_COMMAND_H

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Logger.h"

namespace fs=boost::filesystem;

namespace LogTools
{
    ///////////////////////////
    // Basic logging interface
    /////////////////////////

    /*Logging  | implementation |  interface*/
    class LogData {
        public:
            virtual void changeLogBuffer(std::string) = 0;
            virtual void writeData() = 0;
            virtual bool writeSuccess() = 0;

    };

    class FileLogger : public LogData {
        private:
            LogFile* FileLog_TOOL;
            LogFile  Log;

        public:
            FileLogger() { }

            FileLogger(std::string directory, std::string text,
                std::ios_base::openmode mode) : Log(directory, text, mode) {

                FileLog_TOOL = &Log;
            }

            virtual void changeDirectory (std::string dir);
            virtual void changeLogBuffer (std::string text);
            virtual void changeIosMode   (std::ios_base::openmode mode);


            virtual void writeData();
            virtual bool writeSuccess();

    };

    class TermLogger : public LogData {
        private:
            LogTerminal* TermLog_TOOL;
            LogTerminal  Log;

        public:
            TermLogger(std::string text) : Log(text) {
                TermLog_TOOL = &Log;
            }

            virtual void changeLogBuffer(std::string text);
            virtual void writeData();
            virtual bool writeSuccess();
    };


    //////////////////////////
    // Main logging interface
    ////////////////////////

    class LoggingInterfaceBase {

        protected:
            std::string formatStr;
            std::vector<LogData*> logMediums;

            int       verbosityLevel = 0; //Default level is ERROR

        public:

            LoggingInterfaceBase(std::vector<LogData*> logTools) :
              logMediums(logTools) { }

            const std::map<int, const char*> verbosityOptions = {
                { 0, "ERROR" },  { 1, "WARNING" }, { 2, "DEBUG" },
                { 3, "E_ONLY" }, { 4, "W_ONLY" },  { 5, "D_ONLY" } };

            virtual void changeMediums(std::vector<LogData*> newLogTools) = 0;

            virtual void changeVerbosity(int newVerbosity) = 0;
            virtual int  currentVerbosity() = 0;

            virtual void report(std::string message, std::string file,
                std::string function, unsigned errorLine, int verbosity=0) = 0;
            virtual void report(std::string message, int verbosity=0) { };

    };

    class BasicLogging : public LoggingInterfaceBase {
        private:
            void reportWrite(std::string message="");
            void reportFormat(std::string message, std::string file,
                std::string function, unsigned errorLine, int verbosity);
            bool verbosityCheck(int verbosity);

        public:
            BasicLogging(std::vector<LogData*> logMediums) :
              LoggingInterfaceBase(logMediums)
            {
                formatStr = "[{}]: '{}' occured in\n" \
                            "'{}' @ line {} in '{}' function";

                reportWrite();
            }

            virtual void changeMediums(std::vector<LogData*> newLogTools);
            virtual void changeVerbosity(int newVerbosity);
            virtual int  currentVerbosity();

            virtual void report(std::string message, std::string file,
                std::string function, unsigned errorLine, int verbosity=0);
            virtual void report(std::string message, int verbosity=0);

    };

}

#endif //LOG_COMMAND_H
