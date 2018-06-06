#include "FSystem_Tools.h"

namespace fs=boost::filesystem;

namespace File_System_Tools
{
    std::vector<int> errorList = { };

    int LastError_Int() {
        int temp = errorList.back();
        errorList.pop_back();
        return temp;
    }
    std::string LastError_Str() {
        std::string temp = errors.at( errorList.size() );
        errorList.pop_back();
        return temp;
    }

    /*File System Explorer*/
    void ListEntries::execute() {

        if ( !fs::exists(root) )
        {
            errorList.push_back(1);
            return;
        }

        for ( fs::directory_iterator it(root); it != fs::end(it); ++it )
        {
            switch(filter)
            {
                case directory:
                    if( fs::is_directory( it->path() ) )
                        resultsList.push_back( it->path().string() );
                    break;

                case file:
                    if( fs::is_regular_file( it->path().string() ) )
                        resultsList.push_back( it->path().string() );
                    break;

                case none:
                    resultsList.push_back( it->path().string() );
                    break;

            }
        }
    }

    void createDir(std::string dir) {
        if( !fs::create_directories(dir) )
            errorList.push_back(2);
    }


    /*Configuration file parser*/
    bool ConfigTool::initialise( std::string& error )
    {
        if( parse.valid() )
            return true;

        error = parse.errorReason;
        return false;
    }
}
