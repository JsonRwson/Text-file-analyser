#include <iostream>
#include <filesystem>
#include <fstream>
#include "file_loader.h"

using std::string;

// Constructor
// Store the file name
// Attempt to identify file type
// Attempt to load file content
// Update flag based on success or failure
FileLoader::FileLoader(string fPath)
{
    filePath = fPath;
    fileType = detectFileType(filePath);

    if(fileType == FileType::UNKNOWN)
    {
        std::cout << "The extension for: <" << filePath << "> is not recognised" << std::endl;
        exit(EXIT_FAILURE);
    }

    loaded = loadFile();
}

// Extract the file extension and return the appropriate enum type
FileType FileLoader::detectFileType(string fPath)
{   
    std::filesystem::path filePath = fPath;
    string extension = filePath.extension().string();

    if(extension == ".txt")
    {
        return FileType::TXT;
    }
    else if(extension == ".csv")
    {
        return FileType::CSV;
    }
    else
    {
        return FileType::UNKNOWN;
    }
}

bool FileLoader::loadFile()
{
    // ifstream is read only
    // ofstream is create + write
    // fstream is a combination of both

    std::ifstream textFile(filePath);

    if (!textFile.is_open())
    {return false;}

    std::stringstream buffer;
    buffer << textFile.rdbuf();
    fileContent = buffer.str();

    return true;
}

// using const string&, return a reference to the private member
// Avoids copying the entire string when returning
// Ensures the caller can’t modify internal data
const std::string& FileLoader::getContent()
{
    return fileContent;
}

const std::string& FileLoader::getFileName()
{
    return filePath;
}

FileType FileLoader::getFileType()
{
    return fileType;
}


