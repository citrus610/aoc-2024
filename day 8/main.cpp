#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>

struct Coord
{
    int x;
    int y;
};

void read_input(std::unordered_map<char, std::vector<Coord>>& map, int& w, int& h)
{
    std::ifstream is("input.txt");

    std::string line;

    h = 0;

    while (std::getline(is, line))
    {
        w = line.size();

        for (auto i = 0; i < line.size(); ++i) {
            if (line[i] == '.') {
                continue;
            }

            auto itr = map.find(line[i]);

            if (itr == map.end()) {
                map.insert({ line[i], { { .x = i, .y = h } } });
            }
            else {
                map[line[i]].push_back({ .x = i, .y = h });
            }
        }

        h += 1;
    }
};

void part1()
{
    std::unordered_map<char, std::vector<Coord>> map;
    int w;
    int h;

    read_input(map, w, h);

    uint64_t count = 0;

    std::vector<std::vector<bool>> antinodes;

    for (int i = 0; i < h; ++i) {
        antinodes.push_back({});

        for (int k = 0; k < w; ++k) {
            antinodes.back().push_back(false);
        }
    }

    for (auto [c, list] : map) {
        for (int i = 0; i < list.size(); ++i) {
            for (int k = i + 1; k < list.size(); ++k) {
                auto node_1 = list[i];
                auto node_2 = list[k];

                auto antinode_1 = Coord {
                    .x = node_1.x * 2 - node_2.x,
                    .y = node_1.y * 2 - node_2.y
                };

                auto antinode_2 = Coord {
                    .x = node_2.x * 2 - node_1.x,
                    .y = node_2.y * 2 - node_1.y
                };

                if (antinode_1.x >= 0 && antinode_1.x < w && antinode_1.y >= 0 && antinode_1.y < h) {
                    antinodes[antinode_1.y][antinode_1.x] = true;
                }

                if (antinode_2.x >= 0 && antinode_2.x < w && antinode_2.y >= 0 && antinode_2.y < h) {
                    antinodes[antinode_2.y][antinode_2.x] = true;
                }
            }
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int k = 0; k < w; ++k) {
            count += antinodes[i][k];
        }
    }

    printf("%d\n", count);
};

void part2()
{
    std::unordered_map<char, std::vector<Coord>> map;
    int w;
    int h;

    read_input(map, w, h);

    uint64_t count = 0;

    std::vector<std::vector<bool>> antinodes;

    for (int i = 0; i < h; ++i) {
        antinodes.push_back({});

        for (int k = 0; k < w; ++k) {
            antinodes.back().push_back(false);
        }
    }

    for (auto [c, list] : map) {
        for (int i = 0; i < list.size(); ++i) {
            for (int k = i + 1; k < list.size(); ++k) {
                auto node_1 = list[i];
                auto node_2 = list[k];

                auto antinode_1 = node_1;

                while (antinode_1.x >= 0 && antinode_1.x < w && antinode_1.y >= 0 && antinode_1.y < h) {
                    antinodes[antinode_1.y][antinode_1.x] = true;

                    antinode_1.x += node_1.x - node_2.x;
                    antinode_1.y += node_1.y - node_2.y;
                }

                auto antinode_2 = node_2;

                while (antinode_2.x >= 0 && antinode_2.x < w && antinode_2.y >= 0 && antinode_2.y < h) {
                    antinodes[antinode_2.y][antinode_2.x] = true;

                    antinode_2.x += node_2.x - node_1.x;
                    antinode_2.y += node_2.y - node_1.y;
                }
            }
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int k = 0; k < w; ++k) {
            if (antinodes[i][k]) {
                count += 1;
            }
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