#include <iostream>
#include "file_loader.h"
#include "text_analyser.h"
#include "csv_analyser.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {std::cout << "Supply a path to a file" << "\n";}
    else
    {
        FileLoader txtFile = FileLoader(argv[1]);
        std::string fileContent = txtFile.getContent();;

        switch(txtFile.getFileType())
        {
            //--------------------------------------------------
            case FileType::TXT:
            {
                TextAnalyser txtAnalyser;
                txtAnalyser.analyseText(fileContent);
                break;
            }
            //--------------------------------------------------
            case FileType::CSV:
            {
                CSVAnalyser csvAnalyser;
                csvAnalyser.analyseCSV(fileContent);
                break;
            }
            //--------------------------------------------------
            default:
                break;
            //--------------------------------------------------
        }
    }

    return 0;
}
