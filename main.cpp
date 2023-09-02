
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void searchRepositories(const std::string& searchTerm) {
    std::string path = "<путь к корневому каталогу репозиториев>"; // Замените на ваш путь

    for (const auto& dirEntry : fs::recursive_directory_iterator(path)) {
        if (dirEntry.is_regular_file()) {
            std::ifstream file(dirEntry.path());
            std::string line;
            int lineNumber = 1;

            while (std::getline(file, line)) {
                if (line.find(searchTerm) != std::string::npos) {
                    std::cout << dirEntry.path() << ": " << lineNumber << ": " << line << std::endl;
                }
                lineNumber++;
            }

            file.close();
        }
    }
}

int main() {
    std::string searchTerm;
    std::cout << "Введите слово для поиска: ";
    std::cin >> searchTerm;

    searchRepositories(searchTerm);

    return 0;
}