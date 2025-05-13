#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "csv_analyser.h"

void CSVAnalyser::analyseCSV(std::string csvContent)
{
    csvVector = convertToVector(csvContent);
    std::cout << printFromVector(csvVector);
}

// Convert the content of a CSV file (string) to a 2D Vector 
std::vector<std::vector<std::string>> CSVAnalyser::convertToVector(std::string csvContent)
{
    std::vector<std::vector<std::string>> data;
    std::string lineBuffer;
    std::istringstream csvStream(csvContent);

    while(std::getline(csvStream, lineBuffer))
    {
        std::stringstream lineStream(lineBuffer);
        std::string cellBuffer;
        std::vector<std::string> row;

        while(std::getline(lineStream, cellBuffer, ','))
        {
            row.push_back(cellBuffer);
        }

        data.push_back(row);
    }

    return data;
}

#include <iomanip>  // for std::setw

std::string CSVAnalyser::printFromVector(std::vector<std::vector<std::string>> vector)
{
    std::ostringstream table;

    if(vector.empty()) return "";

    // Determine max width per column
    size_t numCols = 0;
    for(const auto& row : vector)
        numCols = std::max(numCols, row.size());

    std::vector<size_t> colWidths(numCols, 0);

    for(const auto& row : vector)
    {
        for(size_t col = 0; col < row.size(); ++col)
        {
            colWidths[col] = std::max(colWidths[col], row[col].length());
        }
    }

    // Print rows with padding
    for(const auto& row : vector)
    {
        table << "+";
        for(size_t col = 0; col < numCols; ++col)
        {
            table << std::string(colWidths[col] + 2, '-') << "+";
        }
        table << "\n|";

        for(size_t col = 0; col < numCols; ++col)
        {
            std::string cell = (col < row.size()) ? row[col] : "";
            table << " " << std::left << std::setw(colWidths[col]) << cell << " |";
        }
        table << "\n";
    }

    // Bottom line
    table << "+";
    for(size_t col = 0; col < numCols; ++col)
    {
        table << std::string(colWidths[col] + 2, '-') << "+";
    }
    table << "\n";

    return table.str();
}

