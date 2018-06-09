#ifndef  LOGGER_H
#define  LOGGER_H

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <fmt/format.h>
#include <iostream>

namespace fs=boost::filesystem;

namespace LogTools {

    ///////////
    // Loggers
    /////////

    /*Concrete implementation*/
    class DataLoggerBase {
        public:
            virtual void changeLogBuffer(std::string) = 0;
            virtual void writeData() = 0;
            virtual bool writeSuccess() = 0;

    };

    /*Concrete code*/
    class LogFile : public DataLoggerBase {
        private:
            std::string              directory;
            std::string              text;
            std::ios_base::openmode  iosMode;
            bool                     bSuccess = true;

        public:
            LogFile() {
                directory = fs::current_path().string() + "\\Debug.log";
                iosMode = std::ios::app;
            }

            LogFile( std::string directory, std::string firstMessage,
              std::ios_base::openmode iosMode=std::ios::app ) \
                : directory(directory), text(firstMessage), iosMode(iosMode) { }

            void changeDirectory(std::string dir) { directory =  dir; }
            virtual void changeLogBuffer(std::string text) { this->text = text; }
            void changeIosMode(std::ios_base::openmode mode) { iosMode = mode; }


            virtual void writeData();
            virtual bool writeSuccess() { return bSuccess; }

    };


    class LogTerminal : public DataLoggerBase {
        private:
            std::string text;
            bool bSuccess;

        public:
            LogTerminal(std::string firstMessage) : text(firstMessage) { }

            virtual void changeLogBuffer(std::string text) { this->text = text; }

            virtual void writeData();
            virtual bool writeSuccess() { return bSuccess; }

    };

}
#endif //LOGGER_H
