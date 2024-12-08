#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <regex>

void part1()
{
    int result = 0;

    std::ifstream is("input.txt");

    std::string line;

    while(std::getline(is, line))
    {
        for (auto i = 0; i < line.size() - 8; ++i) {
            if (line[i] != 'm' || line[i + 1] != 'u' || line[i + 2] != 'l' || line[i + 3] != '(') {
                continue;
            }

            bool invalid = false;

            std::string num1;

            for (int k = 0; k < 4; ++k) {
                if (i + 4 + k > line.size() - 1) {
                    invalid = true;
                    break;
                }

                auto c = line[i + 4 + k];

                if (k == 3 && c != ',') {
                    invalid = true;
                    break;
                }
                
                if (c == ',') {
                    break;
                }

                if (!isdigit(c)) {
                    invalid = true;
                    break;
                }

                num1.push_back(c);
            }

            if (invalid || num1.empty()) {
                continue;
            }

            int v1 = std::stoi(num1);

            std::string num2;

            for (int k = 0; k < 4; ++k) {
                if (i + 4 + k + 1 + num1.size() > line.size() - 1) {
                    invalid = true;
                    break;
                }

                char c = line[i + 4 + k + 1 + num1.size()];

                if (k == 3 && c != ')') {
                    invalid = true;
                    break;
                }
                
                if (c == ')') {
                    break;
                }

                if (!isdigit(c)) {
                    invalid = true;
                    break;
                }

                num2.push_back(c);
            }

            if (invalid || num2.empty()) {
                continue;
            }

            int v2 = std::stoi(num2);

            result += v1 * v2;
        }
    }

    printf("%d\n", result);
};

void part2()
{
    int result = 0;

    std::ifstream is("input.txt");

    std::string line;

    bool enable = true;

    while(std::getline(is, line))
    {

        for (auto i = 0; i < line.size() - 8; ++i) {
            if (line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == '(' && line[i + 3] == ')') {
                enable = true;
                continue;
            }

            if (line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == 'n' && line[i + 3] == '\'' && line[i + 4] == 't' && line[i + 5] == '(' && line[i + 6] == ')') {
                enable = false;
                continue;
            }

            if (!enable) {
                continue;
            }

            if (line[i] != 'm' || line[i + 1] != 'u' || line[i + 2] != 'l' || line[i + 3] != '(') {
                continue;
            }

            bool invalid = false;

            std::string num1;

            for (int k = 0; k < 4; ++k) {
                if (i + 4 + k > line.size() - 1) {
                    invalid = true;
                    break;
                }

                auto c = line[i + 4 + k];

                if (k == 3 && c != ',') {
                    invalid = true;
                    break;
                }
                
                if (c == ',') {
                    break;
                }

                if (!isdigit(c)) {
                    invalid = true;
                    break;
                }

                num1.push_back(c);
            }

            if (invalid || num1.empty()) {
                continue;
            }

            int v1 = std::stoi(num1);

            std::string num2;

            for (int k = 0; k < 4; ++k) {
                if (i + 4 + k + 1 + num1.size() > line.size() - 1) {
                    invalid = true;
                    break;
                }

                char c = line[i + 4 + k + 1 + num1.size()];

                if (k == 3 && c != ')') {
                    invalid = true;
                    break;
                }
                
                if (c == ')') {
                    break;
                }

                if (!isdigit(c)) {
                    invalid = true;
                    break;
                }

                num2.push_back(c);
            }

            if (invalid || num2.empty()) {
                continue;
            }

            int v2 = std::stoi(num2);

            result += v1 * v2;
        }
    }

    printf("%d\n", result);
};

int main()
{
    part1();
    part2();

    return 0;
};