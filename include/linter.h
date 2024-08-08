#ifndef LINTER_H
#define LINTER_H

#include <string>
#include <vector>

class Linter {
public:
    Linter(const std::string& filename);
    void lint();
private:
    std::string filename;
    std::vector<std::string> loadFile();
    void checkLineLength(const std::vector<std::string>& lines, size_t maxLength);
    void checkNamingConventions(const std::vector<std::string>& lines);
    void checkTabsForIndentation(const std::vector<std::string>& lines);
    void checkTrailingWhitespace(const std::vector<std::string>& lines);
    void checkBracePlacement(const std::vector<std::string>& lines);
    void checkElsePlacement(const std::vector<std::string>& lines);
};

#endif // LINTER_H