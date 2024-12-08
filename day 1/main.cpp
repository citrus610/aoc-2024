#include "list.h"

void part1()
{
    int v1[1000] = { 0 };
    int v2[1000] = { 0 };

    for (int i = 0; i < 1000; ++i) {
        v1[i] = list[i * 2];
        v2[i] = list[i * 2 + 1];
    }

    std::sort(v1, v1 + 1000);
    std::sort(v2, v2 + 1000);

    int v = 0;

    for (int i = 0; i < 1000; ++i) {
        v += std::abs(v1[i] - v2[i]);
    }

    printf("%d\n", v);
};

void part2()
{
    int v1[1000] = { 0 };
    int v2[1000] = { 0 };

    for (int i = 0; i < 1000; ++i) {
        v1[i] = list[i * 2];
        v2[i] = list[i * 2 + 1];
    }

    int map[100000] = { 0 };

    for (int i = 0; i < 1000; ++i) {
        map[v2[i]] += 1;
    }

    int v = 0;

    for (int i = 0; i < 1000; ++i) {
        v += v1[i] * map[v1[i]];
    }

    printf("%d\n", v);
};

int main()
{
    part1();
    part2();

    return 0;
};