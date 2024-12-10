#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <unordered_set>
#include <cstdint>

void read_input(std::vector<std::pair<uint64_t, std::vector<uint64_t>>>& list)
{
    std::ifstream is("input.txt");

    std::string line;

    while (std::getline(is, line))
    {
        std::pair<uint64_t, std::vector<uint64_t>> pair;

        std::string str_value;

        uint64_t colon = 0;

        for (uint64_t i = 0; i < line.size(); ++i) {
            if (line[i] == ':') {
                colon = i;
                break;
            }

            str_value.push_back(line[i]);
        }

        pair.first = std::stoull(str_value);

        pair.second = {};

        std::string num;

        for (uint64_t i = colon + 2; i < line.size(); ++i) {
            if (line[i] == ' ') {
                pair.second.push_back(std::stoull(num));
                num.clear();
                continue;
            }

            num.push_back(line[i]);
        }

        pair.second.push_back(std::stoull(num));

        list.push_back(pair);
    }
};

bool dfs(uint64_t value, std::vector<uint64_t> q, int index, uint64_t node)
{
    if (index >= q.size()) {
        return node == value;
    }

    if (node > value) {
        return false;
    }

    if (dfs(value, q, index + 1, node + q[index])){
        return true;
    }

    if (dfs(value, q, index + 1, node * q[index])){
        return true;
    }

    return false;
}

bool check1(uint64_t value, std::vector<uint64_t> q)
{
    return dfs(value, q, 1, q[0]);
}

void part1()
{
    std::vector<std::pair<uint64_t, std::vector<uint64_t>>> list;

    read_input(list);

    uint64_t count = 0;

    for (auto& line : list) {
        uint64_t value = line.first;

        auto queue = line.second;

        for (auto v : queue) {
            printf("%llu ", v);
        }

        printf("%llu\n", value);

        if (check1(value, queue)) {
            printf("ok\n");
            count += value;
        }
    }

    printf("%d\n", count);
};

void part2()
{
    // read_input(map, guard);

    uint64_t count = 0;

    printf("%d\n", count);
};

int main()
{
    part1();
    part2();

    return 0;
};