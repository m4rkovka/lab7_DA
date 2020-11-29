#include <iostream>
#include <string>

const int MAX_STRING_SIZE = 100;

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

int main() {
    std::string input;
    std::cin >> input;
    std::cout << get_count_unique_sub_palindrome(input) << "\n";
    return 0;
}