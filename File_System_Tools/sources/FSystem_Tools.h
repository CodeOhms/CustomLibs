#ifndef FSYSTEM_TOOLS_H
#define FSYSTEM_TOOLS_H

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <toml.h>
#include <string>
#include <vector>
#include <map>

namespace fs=boost::filesystem;

namespace File_System_Tools {

    const std::map<int, std::string> errors = {
        { 0, "Folder or file cannot be accessed" },
        { 1, "Folder or file doesn't exist"      },
        { 2, "Cannot create directory"           }
    };

    extern std::vector<int> errorList;
    // |WARNING| Retrieving an error deletes after accessing
    int LastError_Int();
    std::string LastError_Str();


    void createDir(std::string dir);


    int checkPermissions();


    enum SearchFilter
    {
        directory,
        file,
        none
    };
    class ListEntries {
        private:
            const fs::path& root;
            const std::string extension;
            SearchFilter filter;

            std::vector<std::string> resultsList;

        public:
            ListEntries(const fs::path& root, const std::string ext,
                SearchFilter filter=file) : \
                    root(root), extension(ext),
                    filter(filter) { }

            virtual void execute();

    };


    //Configuration file tool -> data
    class ConfigTool
    {
        const toml::ParseResult parse;

        public:
            const toml::Value& all;

            ConfigTool(std::string fileName) :
              parse( toml::parseFile(fileName) ), all(parse.value) { }
            bool initialise(std::string& error);

            std::string getError;
            template <typename T>
            typename toml::call_traits<T>::return_type get(bool& bSuccess,
              std::string variable, const toml::Value& parse=toml::Value())
            {
                bSuccess = true;
                try
                {
                    if(parse.empty())
                        return all.get<T>(variable);
                    return parse.get<T>(variable);
                } catch(std::runtime_error& e) {
                    bSuccess = false;
                    getError = e.what();
                    return all.as<T>();
                }
            }

    };
}

#endif //FSYSTEM_TOOLS_H
