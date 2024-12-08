#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <unordered_set>

enum Cell
{
    CELL_NONE,
    CELL_FILLED,
    CELL_VISITED
};

enum Direction
{
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
};

struct Guard
{
    int x;
    int y;
    Direction d;
};

constexpr int OFFSET[4][2] = {
    { 0, -1 },
    { 1, 0 },
    { 0, 1 },
    { -1, 0 }
};

Direction turn_right(Direction d)
{
    return Direction((int(d) + 1) % 4);
};

void read_input(std::vector<std::vector<Cell>>& map, Guard& guard)
{
    std::ifstream is("input.txt");

    std::string line;

    map.clear();

    int y = 0;

    while (std::getline(is, line))
    {
        map.push_back({});

        for (auto i = 0; i < line.size(); ++i) {
            auto c = line[i];

            if (c == '#') {
                map.back().push_back(CELL_FILLED);
                continue;
            }

            if (c == '^') {
                guard.x = i;
                guard.y = y;
                guard.d = DIR_UP;
            }

            map.back().push_back(CELL_NONE);
        }

        y += 1;
    }
};

void part1()
{
    std::vector<std::vector<Cell>> map;
    Guard guard;

    read_input(map, guard);

    auto visited = map;

    visited[guard.y][guard.x] = CELL_VISITED;

    while (true)
    {
        int new_x = guard.x + OFFSET[guard.d][0];
        int new_y = guard.y + OFFSET[guard.d][1];

        if (new_x < 0 || new_y < 0 || new_x >= map[0].size() || new_y >= map.size()) {
            break;
        }

        auto cell = map[new_y][new_x];

        if (cell == CELL_NONE) {
            guard.x = new_x;
            guard.y = new_y;

            visited[new_y][new_x] = CELL_VISITED;

            continue;
        }

        if (cell == CELL_FILLED) {
            guard.d = turn_right(guard.d);
        }
    }

    int count = 0;

    for (auto y : visited) {
        for (auto x : y) {
            if (x == CELL_VISITED) {
                count += 1;
            }
        }
    }

    printf("%d\n", count);
};

bool is_loop(std::vector<std::vector<Cell>> map, Guard guard)
{
    std::vector<std::vector<Cell>> visited[4];

    visited[0] = map;
    visited[1] = map;
    visited[2] = map;
    visited[3] = map;

    visited[guard.d][guard.y][guard.x] = CELL_VISITED;

    auto init = guard;

    while (true)
    {
        int new_x = guard.x + OFFSET[guard.d][0];
        int new_y = guard.y + OFFSET[guard.d][1];

        if (new_x < 0 || new_y < 0 || new_x >= map[0].size() || new_y >= map.size()) {
            return false;
        }

        auto cell = map[new_y][new_x];

        if (cell == CELL_NONE) {
            guard.x = new_x;
            guard.y = new_y;
        }
        else if (cell == CELL_FILLED) {
            guard.d = turn_right(guard.d);
        }

        if (visited[guard.d][guard.y][guard.x] == CELL_VISITED) {
            return true;
        }

        visited[guard.d][guard.y][guard.x] = CELL_VISITED;
    }

    return false;
};

void part2()
{
    std::vector<std::vector<Cell>> map;
    Guard guard;

    read_input(map, guard);

    auto init = guard;

    auto visited = map;

    visited[guard.y][guard.x] = CELL_VISITED;

    while (true)
    {
        int new_x = guard.x + OFFSET[guard.d][0];
        int new_y = guard.y + OFFSET[guard.d][1];

        if (new_x < 0 || new_y < 0 || new_x >= map[0].size() || new_y >= map.size()) {
            break;
        }

        auto cell = map[new_y][new_x];

        if (cell == CELL_NONE) {
            guard.x = new_x;
            guard.y = new_y;

            visited[new_y][new_x] = CELL_VISITED;

            continue;
        }

        if (cell == CELL_FILLED) {
            guard.d = turn_right(guard.d);
        }
    }

    int count = 0;

    for (auto y = 0; y < map.size(); ++y) {
        for (auto x = 0; x < map[0].size(); ++x) {
            if (y == init.y && x == init.x) {
                continue;
            }

            if (visited[y][x] == CELL_VISITED) {
                auto copy = map;

                copy[y][x] = CELL_FILLED;

                count += is_loop(copy, init);
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