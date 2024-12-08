#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>

std::vector<std::string> read_input()
{
    std::vector<std::string> result;

    std::ifstream is("input.txt");

    std::string line;

    while (std::getline(is, line))
    {
        result.push_back(line);
    }

    return result;
};

bool check_1(std::vector<std::string>& input, int x, int y, int dt_x, int dt_y) {
    const char str[] = "XMAS";

    for (auto i = 0; i < 4; ++i) {
        int c_x = x + dt_x * i;
        int c_y = y + dt_y * i;

        if (c_x < 0 || c_x >= input[y].size()) {
            return false;
        }

        if (c_y < 0 || c_y >= input.size()) {
            return false;
        }

        if (input[c_y][c_x] != str[i]) {
            return false;
        }
    }

    return true;
}

void part1()
{
    auto input = read_input();

    int count = 0;

    for (auto y = 0; y < input.size(); ++y) {
        for (auto x = 0; x < input[y].size(); ++x) {
            count += check_1(input, x, y, 1, 0);
            count += check_1(input, x, y, -1, 0);
            count += check_1(input, x, y, 0, 1);
            count += check_1(input, x, y, 0, -1);
            count += check_1(input, x, y, 1, 1);
            count += check_1(input, x, y, 1, -1);
            count += check_1(input, x, y, -1, 1);
            count += check_1(input, x, y, -1, -1);
        }
    }

    printf("%d\n", count);
};

bool check_2(std::vector<std::string>& input, int x, int y) {
    if (input[y][x] != 'A') {
        return false;
    }

    const int offset[4][2] = {
        { -1, -1 },
        { 1, -1 },
        { -1, 1 },
        { 1, 1 },
    };

    for (int i = 0; i < 4; ++i) {
        int c_x = x + offset[i][0];
        int c_y = y + offset[i][1];

        int n_x = x - offset[i][0];
        int n_y = y - offset[i][1];

        if (input[c_y][c_x] == 'M') {
            if (input[n_y][n_x] != 'S') {
                return false;
            }
        }
        else if (input[c_y][c_x] == 'S') {
            if (input[n_y][n_x] != 'M') {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return true;
}

void part2()
{
    auto input = read_input();

    int count = 0;

    for (auto y = 1; y < input.size() - 1; ++y) {
        for (auto x = 1; x < input[y].size() - 1; ++x) {
            count += check_2(input, x, y);
        }
    }

    printf("%d\n", count);
};

int main()
{
    part1();
    part2();

    return 0;
};