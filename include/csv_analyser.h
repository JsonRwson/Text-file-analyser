#ifndef CSV_ANALYSER_H
#define CSV_ANALYSER_H
#include <vector>
#include <string>

class CSVAnalyser
{
    public:
        void analyseCSV(std::string csvContent);
        std::vector<std::vector<std::string>> convertToVector(std::string csvContent);
        std::string printFromVector(std::vector<std::vector<std::string>> vector);

    private:
        std::vector<std::vector<std::string>> csvVector;
};

#endif
