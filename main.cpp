#include <algorithm>
#include <array>

#include <cstdint>
#include <list>

#include <memory>
#include <numeric>
#include <random>

#include <fmt/format.h>

#include "src/fifteen_solve.h"

void print_sample(const sample& _sample)
{
    for (size_t row = 0; row < SideSize; row++) {
        for (size_t col = 0; col < SideSize; col++) {
            fmt::print("{:2} ", static_cast<unsigned>(_sample[col + SideSize * row]));
        }
        fmt::print("\n");
    }
}

int main(int, char**)
{
    auto seed = get_random_sample();
    print_sample(seed);

    auto solve = get_solving(seed, 400);
    for (auto& ent : solve) {
        print_sample(ent);
        fmt::print("Heuristic is {} \n", get_heuristic(ent));
    }
    fmt::print("Solved for {} steps.\n", solve.size());
    return 0;
}
