#include "Time_Tools.h"

namespace Time_Tools {

    // 0: date, 1: date & time, 2: 24 hour time, 3: 12 hour time
    const char* timeFormats[] = { "%d %m %Y", "%c", "%R", "%r" };
    int timeFormatSize        = sizeof(timeFormats)/sizeof(*timeFormats);

    /*Function for retrieving local time*/
    std::string getDate(const char* format) {

        time_t rawtime = time(NULL);
        char the_date[80];

        //Check to see if time_t didn't fail
        if(rawtime != -1)
            strftime(the_date, 80, format, localtime(&rawtime));

        return the_date;
    }
    std::string getDate(int format) {

        if( format > (timeFormatSize -1) )
            return "format index must not be larger than "
              + std::to_string(timeFormatSize);

        return getDate(timeFormats[format]);
    }

}
