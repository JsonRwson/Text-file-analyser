#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
using std::string;

// user-defined type that represents a set of named constants
// used to make code more readable instead of magic numbers
enum class FileType
{
    TXT,
    CSV,
    UNKNOWN
};

class FileLoader
{
    public:
        FileLoader(string fPath);  // Constructor
        bool isFileLoaded();
        FileType getFileType();
        const string& getContent();
        const string& getFileName();
    
    private:
        string filePath;
        string fileContent;
        bool loaded;
        FileType fileType;

        bool loadFile();
        FileType detectFileType(string fPath);
};

#endif
