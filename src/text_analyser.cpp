#include <iostream>
#include <sstream>
#include <iterator>
#include "text_analyser.h"
#include <algorithm>
#include <iomanip>

TextAnalyser::TextAnalyser()
{}

void TextAnalyser::analyseText(const std::string& text)
{
    // Count words
    wordCount = countWords(text);
    std::cout << "Word count: " << wordCount << "\n";

    // Count lines
    lineCount = countLines(text);
    std::cout << "Line count: " << lineCount << "\n";

    // Count characters
    charCount = countCharacters(text, true);
    charCountNoWhiteSp = countCharacters(text, false);
    std::cout << "Character count: " << charCount << "\n";
    std::cout << "Character count (without whitespace): " << charCountNoWhiteSp << "\n";

    // Average word length
    float wordLengthAvg = getAverageWordLength(text);
    std::cout << "Average word length: " << std::fixed << std::setprecision(2) << wordLengthAvg << "\n";

    // Word frequency
    std::vector<std::pair<std::string, int>> freqPairs = convertMapToVector(getMostFrequentWords(text));
    std::cout << "------------------\n Word : Frequency\n------------------\n";
    std::cout << formatFrequencyTable(freqPairs);

}

// Take a <str, int> vector pair and turn it into a pretty string
std::string TextAnalyser::formatFrequencyTable(std::vector<std::pair<std::string, int>> vector)
{
    std::ostringstream prettyVector;
    size_t maxWidth = 0;

    // Find the longest word from the pairs and store its length
    // Used for stw to ensure output "column" length is consistent
    for(const auto& pair : vector)
    {
        if(pair.first.length() > maxWidth)
        {maxWidth = pair.first.length();}
    }

    // Iterate through the pairs, pass the values to a string stream
    for(const auto& pair : vector)
    {
        // Ensure the divider for <word : frequency> always lines up
        // Align left and set width to the largest word + 2
        //     like this  : 1
        // and like this  : 2
        prettyVector << std::left << std::setw(maxWidth + 2)
            << pair.first << " : " << pair.second << "\n";
    }

    return prettyVector.str();
}

int TextAnalyser::countLines(const std::string& text)
{
    // Check if string is empty
    if(text.empty())
    {return 0;}

    int count = 0;

    // Separate concern, string becomes parsable stream
    std::istringstream textStream(text);

    // Buffer for each line in the string
    std::string line;

    // Extract lines, split on new lines until end of the string
    while(std::getline(textStream, line))
    {count++;}

    return count;
}

int TextAnalyser::countWords(const std::string& text)
{
    // Check if string is empty
    if(text.empty())
    {return 0;}

    int count = 0;

    // Separate concern, string becomes parsable stream
    std::istringstream textStream(text);

    // Buffer for each word in the string
    std::string word;
    // Extract words (delimited by spaces, newlines, or any whitespace)
    // Automatically splits on spaces, newlines, tabs, etc.
    while(textStream >> word)
    {count++;}

    return count;
}

// Take an argument of a string and a flag to decide whether to factor in whitespace e.g. ' ', '\n'
int TextAnalyser::countCharacters(const std::string& text, bool includeWhitespace)
{
    int count = 0;
    if(includeWhitespace)
    {
        // Text.length includes whitespace by default
        count = text.length();
        return count;
    }
    else
    {
        for(char c : text)
        {
            // Otherwise manually iterate through the string, ignoring whitespace
            if(!std::isspace(c))
            {
                count++;
            }
        }
        return count;
    }
}

float TextAnalyser::getAverageWordLength(const std::string& text)
{
    // Avoid dividing by zero
    if(text.empty())
    {return 0;}

    float wCount = countWords(text);
    float cCount = countCharacters(text, false);

    return cCount / wCount;
}

// Return a map -> word : frequency
std::map<std::string, int> TextAnalyser::getMostFrequentWords(const std::string& text)
{
    std::map<std::string, int> wordFrequencyMap;

    // Separate concern, string becomes parsable stream
    std::istringstream textStream(text);

    // Buffer for each word in the string
    std::string word;
    while(textStream >> word)
    {
        // Improve frequency accuracy by stripping capitilzation and punctuation
        word = toLowercase(word);
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

        if(!word.empty())
        {wordFrequencyMap[word]++;}
    }

    return wordFrequencyMap;

}

// Convert a <string : int> map into a sorted vector, in descending order based on the value, not the key
std::vector<std::pair<std::string, int>> TextAnalyser::convertMapToVector(std::map<std::string, int> map)
{
    std::vector<std::pair<std::string, int>> freqPairs;
    
    // For each key-value pair in the map
    // Iterate until the end of the map
    // Add the key and value as a pair in a vector of pairs
    for(auto i = map.begin(); i != map.end(); ++i)
    {freqPairs.push_back(std::make_pair(i->first, i->second));}

    // Sort the resulting vector of pairs, based on the second value in the pair; the word frequency count
    // Iterate the beginning -> end of the pairs, using a lambda function to make a comparitor that compares the second values
    std::sort(freqPairs.begin(), freqPairs.end(), [](const auto& a, const auto& b){return a.second > b.second;});

    return freqPairs;
}

std::string TextAnalyser::toLowercase(const std::string& text)
{
    // std::transform applies a function to each element in a range
    // it stores the result in an output range
    // data.begin(), data.end() - the range of characters processed
    // data.begin() - where to store the result - modifying the data in place
    std::string data = text;
    std::transform(data.begin(), data.end(), data.begin(),

    // [](unsigned char c) { return std::tolower(c); }
    // A lambda function, inline anonamous function
    // returns lowercase version of each char
    // unsigned char return type as tolower has undefined behaviour on negative value chars e.g. some UTF-8
    [](unsigned char c){return std::tolower(c);});
    // could be replaced with a non-lambda function

    return data;

    /* Lambda Functions
    [ capture ] ( parameters ) -> return_type { body }
        > capture - Tells the lambda what external variables to use (if any)
        > (parameters) - Like regular function parameters
        > return type - Optional, but can help with clarity or complex return types
        > body - The code that runs when the lambda is called
    */
}
