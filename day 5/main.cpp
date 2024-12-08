#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>

void read_input(bool map[100][100], std::vector<std::vector<int>>& list)
{
    std::vector<std::string> result;

    std::ifstream is("input.txt");

    std::string line;

    list.clear();

    bool mapping = true;

    while (std::getline(is, line))
    {
        if (line.empty()) {
            mapping = false;
            continue;
        }

        if (mapping) {
            std::string s1;
            std::string s2;

            s1.push_back(line[0]);
            s1.push_back(line[1]);

            s2.push_back(line[3]);
            s2.push_back(line[4]);

            int n1 = std::stoi(s1);
            int n2 = std::stoi(s2);

            map[n1][n2] = true;

            continue;
        }

        list.push_back({});

        std::string num;

        for (auto c : line) {
            if (c == ',') {
                list.back().push_back(std::stoi(num));
                num.clear();
                continue;
            }

            num.push_back(c);
        }

        list.back().push_back(std::stoi(num));
    }
};

void part1()
{
    bool map[100][100] = { false };
    std::vector<std::vector<int>> list;

    read_input(map, list);

    int count = 0;

    for (auto line : list) {
        bool line_ok = true;

        for (auto i = 1; i < line.size(); ++i) {
            for (auto k = 1; k < i; ++k) {
                if (map[line[i]][line[k]]) {
                    line_ok = false;
                    break;
                }
            }

            if (!line_ok) {
                break;
            }
        }

        if (line_ok) {
            count += line[line.size() / 2];
        }
    }

    printf("%d\n", count);
};

void part2()
{
    bool map[100][100] = { false };
    std::vector<std::vector<int>> list;

    read_input(map, list);

    int count = 0;

    for (auto line : list) {
        bool line_ok = true;

        for (auto i = 1; i < line.size(); ++i) {
            for (auto k = 1; k < i; ++k) {
                if (map[line[i]][line[k]]) {
                    line_ok = false;
                    break;
                }
            }

            if (!line_ok) {
                break;
            }
        }

        if (line_ok) {
            continue;
        }

        std::sort(
            line.begin(),
            line.end(),
            [&] (int a, int b) {
                return map[a][b];
            }
        );

        count += line[line.size() / 2];
    }

    printf("%d\n", count);
};

int main()
{
    part1();
    part2();

    return 0;
};