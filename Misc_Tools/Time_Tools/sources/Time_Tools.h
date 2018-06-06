#ifndef  TIME_TOOLS_H
#define  TIME_TOOLS_H

#include <string>

namespace Time_Tools {

    extern const char* timeFormat[];
    extern int timeFormatSize;

    /*Function for retrieving local time*/
    std::string getDate(const char* format="%d %m %Y");
    // 0: date, 1: date & time, 2: 24 hour time, 3: 12 hour time
    std::string getDate(int format);
}

#endif //TIME_TOOLS_H
