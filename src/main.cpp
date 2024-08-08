#include "iostream"
#include "Linter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: cpplint_clone <filename>\n";
        return 1;
    }

    std::string filename = argv[1];
    Linter linter(filename);
    linter.lint();

    return 0;
}