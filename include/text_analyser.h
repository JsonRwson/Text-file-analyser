#ifndef TEXT_ANALYSER_H
#define TEXT_ANALYSER_H

#include <string>
#include <vector>
#include <map>

class TextAnalyser
{
    public:
        TextAnalyser();
        void analyseText(const std::string& text);
        int countWords(const std::string& text);
        int countLines(const std::string& text);
        int countCharacters(const std::string& text, bool includeWhitespace);
        float getAverageWordLength(const std::string& text);
        const std::string& searchWord(const std::string& text);
        std::string getStrMapDesc(std::map<int, std::string> inputMap);
        std::map<std::string, int> getMostFrequentWords(const std::string& text);
        std::vector<std::pair<std::string, int>> convertMapToVector(std::map<std::string, int> map);
        std::string formatFrequencyTable(std::vector<std::pair<std::string, int>>);
        std::string toLowercase(const std::string& text);

    private:
        int wordCount;
        int lineCount;
        int charCount;
        int charCountNoWhiteSp;
};

#endif
