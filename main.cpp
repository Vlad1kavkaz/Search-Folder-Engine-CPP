#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::set<std::string> searchRepositories(const std::set<std::string>& input, const std::string& path) {
    std::set<std::string> collectedFiles;
    for (const auto& searchTerm : input) {
        for (const auto& dirEntry : fs::recursive_directory_iterator(path)) {
            if (dirEntry.is_regular_file() && dirEntry.path().parent_path().filename() != "cmake-build-debug" &&
                dirEntry.path().parent_path().filename() != ".idea" &&
                dirEntry.path().parent_path().filename() != ".vs") {
                if (dirEntry.is_regular_file()) {
                    std::ifstream file(dirEntry.path());
                    std::string line;
                    int lineNumber = 1;

                    while (std::getline(file, line)) {
                        if (line.find(searchTerm) != std::string::npos) {
                            collectedFiles.insert(dirEntry.path().generic_string());
                        }
                        lineNumber++;
                    }

                    file.close();
                }
            }
        }
    }
    return collectedFiles;
}

int main() {
    std::string searchTerm;
    std::set<std::string> input;
    std::cout << "Enter phrase to search: ";
    std::getline(std::cin, searchTerm);
    std::stringstream ss(searchTerm);
    std::string s;
    while (std::getline(ss, s)) {
        input.insert(s);
    }

    std::string path;
    std::cout << "Enter the directory to search in: ";
    std::getline(std::cin, path);

    std::set<std::string> pathSet = searchRepositories(input, path);

    std::ofstream outputFile("C:\\Users\\28218\\CLionProjects\\search\\output.txt");
    for (const auto& p : pathSet) {
        outputFile << p << std::endl;
    }
    outputFile.close();

    std::cout << "Program finished successfully." << std::endl;
    std::cout << "Results have been saved to 'output.txt'." << std::endl;

    std::string openFileChoice;
    std::cout << "Do you want to open a specific file? (y/n): ";
    std::getline(std::cin, openFileChoice);

    if (openFileChoice == "y" || openFileChoice == "Y") {
        std::ifstream inputFile("output.txt");
        if (!inputFile.is_open()) {
            std::cout << "Error opening file 'output.txt'" << std::endl;
            return 1;
        }

        int lineIndex = 0;
        std::string fileLine;
        while (std::getline(inputFile, fileLine)) {
            std::cout << "[" << lineIndex << "] " << fileLine << std::endl;
            lineIndex++;
        }

        std::string openFileIndex;
        std::cout << "Enter the number of the file to open: ";
        std::getline(std::cin, openFileIndex);

        int fileIndex = std::stoi(openFileIndex);
        if (fileIndex >= 0 && fileIndex < lineIndex) {
            std::string matchCode;
            inputFile.clear();
            inputFile.seekg(0); // Перемотка файла inputFile в начало
            for (int i = 0; i <= fileIndex; i++) {
                std::getline(inputFile, matchCode);
            }

            int choice;
            std::cout << "Please select your operating system:" << std::endl;
            std::cout << "1. Windows" << std::endl;
            std::cout << "2. macOS" << std::endl;
            std::cout << "3. Linux" << std::endl;
            std::cout << "Choice: ";
            std::cin >> choice;

            std::string command;
            switch (choice) {
                case 1:
                    command = "start " + matchCode; // Открытие файла в Windows
                    break;
                case 2:
                    command = "open " + matchCode; // Открытие файла в macOS
                    break;
                case 3:
                    command = "xdg-open " + matchCode; // Открытие файла в Linux
                    break;
                default:
                    std::cout << "Invalid choice. Please try again" << std::endl;
                    return 1;
            }

            if (system(command.c_str()) == 0) {
                std::cout << "File opened successfully" << std::endl;
            } else {
                std::cout << "Failed to open file" << std::endl;
            }
        } else {
            std::cout << "Invalid file index. Program will exit." << std::endl;
            return 1;
        }

        inputFile.close();
    }

    return 0;
}
