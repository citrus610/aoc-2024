#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

bool is_safe(std::vector<int> v)
{
    if (v.size() < 2) {
        return true;
    }

    int total_dt_raw = 0;
    int total_dt = 0;

    for (auto i = 0; i < v.size() - 1; ++i) {
        int dt_raw = v[i] - v[i + 1];
        int dt = std::abs(dt_raw);

        if (dt < 1 || dt > 3) {
            return false;
        }

        total_dt_raw += dt_raw;
        total_dt += dt;
    }

    return std::abs(total_dt_raw) == total_dt;
};

void part1()
{
    int safe = 0;

    std::ifstream is("input.txt");

    std::string line;

    while(std::getline(is, line))
    {
        std::vector<int> v;

        std::string num;

        for (auto c : line) {
            if (c == ' ') {
                v.push_back(std::stoi(num));
                num.clear();
                continue;
            }

            num.push_back(c);
        }

        v.push_back(std::stoi(num));

        safe += is_safe(v);

        line.clear();
    }

    printf("%d\n", safe);
};

void part2()
{
    int safe = 0;

    std::ifstream is("input.txt");

    std::string line;

    while(std::getline(is, line))
    {
        std::vector<int> v;

        std::string num;

        for (auto c : line) {
            if (c == ' ') {
                v.push_back(std::stoi(num));
                num.clear();
                continue;
            }

            num.push_back(c);
        }

        v.push_back(std::stoi(num));

        if (is_safe(v)) {
            safe += 1;
        }
        else {
            for (auto i = 0; i < v.size(); ++i) {
                auto v_copy = v;

                v_copy.erase(v_copy.begin() + i);

                if (is_safe(v_copy)) {
                    safe += 1;
                    break;
                }
            }
        }

        line.clear();
    }

    printf("%d\n", safe);
};

int main()
{
    part1();
    part2();

    return 0;
};