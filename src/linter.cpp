#include "Linter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

Linter::Linter(const std::string& filename) : filename(filename) {}

std::vector<std::string> Linter::loadFile() {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

void Linter::checkLineLength(const std::vector<std::string>& lines, size_t maxLength) {
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].length() > maxLength) {
            std::cout << "Line " << i + 1 << ": Exceeds " << maxLength << " characters.\n";
        }
    }
}

// void Linter::checkNamingConventions(const std::vector<std::string>& lines) {
//     std::regex camelCaseRegex("^[a-z]+[a-zA-Z0-9]*$");

//     for (size_t i = 0; i < lines.size(); ++i) {
//         std::smatch match;
//         if (std::regex_search(lines[i], match, std::regex(R"(\b(?:int|float|void|char|double|bool)\s+(\w+)\b)"))) { // basic types like int, float, void are checked. Can add custom types to the regex
//             std::string name = match[1];
//             if (!std::regex_match(name, camelCaseRegex)) {
//                 std::cout << "Line " << i + 1 << ": Variable/function '" << name << "' does not follow camelCase naming convention.\n";
//             }
//         }
//     }
// }

void Linter::checkTabsForIndentation(const std::vector<std::string>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find_first_not_of('\t') != std::string::npos && lines[i][0] == ' ') {
            std::cout << "Line " << i + 1 << ": Spaces used for indentation; use tabs instead.\n";
        }
    }
}

void Linter::checkTrailingWhitespace(const std::vector<std::string>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        if (!lines[i].empty() && lines[i].back() == ' ') {
            std::cout << "Line " << i + 1 << ": Line ends with trailing whitespace.\n";
        }
    }
}

void Linter::checkBracePlacement(const std::vector<std::string>& lines) {
    std::regex controlStatementRegex(R"(\b(if|else|for|while|switch|do|try|catch)\b)");
    std::regex functionDeclarationRegex(R"((\b(?:int|float|void|char|double|bool)\b|\w+\s+\w+\s*)\([^)]*\))");
    
    for (size_t i = 0; i < lines.size(); ++i) {
        std::smatch match;

        if (std::regex_search(lines[i], match, controlStatementRegex) || 
            std::regex_search(lines[i], match, functionDeclarationRegex)) {
            
            size_t bracePos = lines[i].find('{');
            if (bracePos != std::string::npos) {
                std::cout << "Line " << i + 1 << ": '{' should be on the next line.\n";
            }
        }
    }
}

void Linter::checkElsePlacement(const std::vector<std::string>& lines) {
    for (size_t i = 1; i < lines.size(); ++i) {
        if (lines[i].find("else") != std::string::npos) {
            if (lines[i - 1].find('}') == std::string::npos) {
                std::cout << "Line " << i + 1 << ": 'else' should start on the line immediately after the closing '}' of the corresponding 'if' block.\n";
            }
        }
    }
}

void Linter::lint() {
    auto lines = loadFile();
    checkLineLength(lines, 150);
    // checkNamingConventions(lines);
    checkTabsForIndentation(lines);
    checkTrailingWhitespace(lines);
    checkBracePlacement(lines);
    checkElsePlacement(lines);
}