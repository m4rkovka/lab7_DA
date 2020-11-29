#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

const int MAX_STRING_SIZE = 10000;

long long helpMatrix[MAX_STRING_SIZE][MAX_STRING_SIZE];

long long get_count_unique_sub_palindrome(const std::string &str) {
    int strSize = static_cast<int>(str.size());

    if (strSize == 0) {
        return 0;
    }

    for (int i = 0; i < strSize; i++) {
        for (int j = 0; j < strSize; j++) {
            if (i == j) {
                helpMatrix[i][j] = 1;
                continue;
            }
            if (i != strSize - 1) {
                if (j == i + 1 && str[i] == str[j]) {
                    helpMatrix[i][j] = 3;
                    continue;
                } else if (j == i + 1 && str[i] != str[j]) {
                    helpMatrix[i][j] = 2;
                    continue;
                }
            }
            helpMatrix[i][j] = 0;
        }
    }

    for (int l = 2; l < strSize; l++) {
        for (int i = 0, j = l; j < strSize; i++, j++) {
            if (str[i] == str[j]) {
                helpMatrix[i][j] = 1 + helpMatrix[i + 1][j] + helpMatrix[i][j - 1];
            } else {
                helpMatrix[i][j] = helpMatrix[i + 1][j] + helpMatrix[i][j - 1] - helpMatrix[i + 1][j - 1];
            }
        }
    }

    return helpMatrix[0][strSize - 1];
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cout << "File doesn't open\n";
        return 1;
    }
    std::string input_string;
    in >> input_string;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    get_count_unique_sub_palindrome(input_string);
    end = std::chrono::system_clock::now();

    int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "STRING SIZE: " << input_string.size() << "\n";
    std::cout << "TIME: " << time << "\n";
    in.close();
    return 0;
}