#include "Log_Command.h"
#include "Logger.h"

namespace fs=boost::filesystem;

namespace LogTools
{
    ///////////
    // Loggers
    /////////

    //FileLogger [command]
    void FileLogger::changeDirectory (std::string dir) {
        FileLog_TOOL->changeDirectory(dir);
    }
    void FileLogger::changeLogBuffer (std::string text) {
        FileLog_TOOL->changeLogBuffer(text);
    }
    void FileLogger::changeIosMode   (std::ios_base::openmode mode) {
        FileLog_TOOL->changeIosMode(mode);
    }
    void FileLogger::writeData() {
        FileLog_TOOL->writeData();
    }
    bool FileLogger::writeSuccess() {
        bool bSuccess = FileLog_TOOL->writeSuccess();
        return bSuccess;
    }

    //TermLogger [command]
    void TermLogger::changeLogBuffer (std::string text) {
        TermLog_TOOL->changeLogBuffer(text);
    }
    void TermLogger::writeData() {
        TermLog_TOOL->writeData();
    }
    bool TermLogger::writeSuccess() {
        bool bSuccess = TermLog_TOOL->writeSuccess();
        return bSuccess;
    }


    //LogFile [concrete code]
    void LogFile::writeData() {
        //ios open_modes:
        // app => set output position to end of stream before every operation
        // ate => set output position to end of stream on opening
        // binary => consider stream as binary instead of text
        // in => enable input on stream
        // out => enable output on stream
        // trunc => destroy everything upon operation, and assume length of zero
        // upon opening
        std::fstream fileStream(directory, iosMode);

        if( fileStream.is_open() )
            fileStream << text << std::endl;

        else { fileStream.close(); bSuccess = false; }
        fileStream.close();
        bSuccess = true;
    }


    //LogTerminal [concrete code]
    void LogTerminal::writeData() {
        std::cout << text << std::endl;
        bSuccess = true;
    }


    //////////////////////////
    // Main Logging Interface
    ////////////////////////
    void BasicLogging::changeMediums(std::vector<LogData*> newLogTools) {
        logMediums = newLogTools;
    }

    void BasicLogging::changeVerbosity(int newVerbosity) {
        verbosityLevel = newVerbosity;
    }

    int BasicLogging::currentVerbosity() {
        return verbosityLevel;
    }

    void BasicLogging::reportWrite(std::string message) {
        if(message != "") {
            for(auto it : logMediums) {
               it->changeLogBuffer(message);
               it->writeData();
            }
        }
    }

    void BasicLogging::reportFormat(std::string message, std::string file,
        std::string function, unsigned errorLine, int verbosity) {

        std::string tempMessage = fmt::format(formatStr,
          verbosityOptions.at(verbosity), message, file, errorLine, function);

        reportWrite(tempMessage);
    }

    bool BasicLogging::verbosityCheck(int verbosity) {
        switch(verbosity)
        {
            case 0: // ERROR
            case 1: // WARNING
            case 2: // DEBUG
                if( verbosity >= verbosityLevel ) {
                    return true;
                }
            case 3: // E_ONLY
            case 4: // W_ONLY
            case 5: // D_ONLY
                if( verbosity == verbosityLevel ||
                  ( verbosity == ( verbosityLevel -3) ) ) {
                    return true;
                }

            return false;
        }
    }

    void BasicLogging::report(std::string message, std::string file,
        std::string function, unsigned errorLine, int verbosity) {

        if( verbosityCheck(verbosity) )
            reportFormat(message, file, function, errorLine, verbosity);
    }

    void BasicLogging::report(std::string message, int verbosity) {
        if( verbosityCheck(verbosity) )
            reportWrite(message);
    }

}
