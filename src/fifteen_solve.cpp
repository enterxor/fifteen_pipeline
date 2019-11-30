#include "fifteen_solve.h"

#include <algorithm>
#include <chrono>
#include <map>
#include <numeric>
#include <random>
#include <set>

sample get_random_sample()
{
    sample result{};

    std::iota(std::begin(result), std::end(result), 0);

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(begin(result), end(result), std::default_random_engine(seed));

    return result;
}

std::list<sample> get_possible_moves(const sample& seed)
{
    std::list<sample> result{};
    for (size_t row = 0; row < SideSize; row++) {
        for (size_t col = 0; col < SideSize; col++) {
            if (seed[col + SideSize * row] == 0) {
                if (row < SideSize - 1) {
                    sample dow{seed};
                    std::swap(dow[col + row * SideSize], dow[col + (row + 1) * SideSize]);
                    result.push_back(dow);
                }
                if (row > 0) {
                    sample up{seed};
                    std::swap(up[col + row * SideSize], up[col + (row - 1) * SideSize]);
                    result.push_back(up);
                }
                if (col < SideSize) {
                    sample right{seed};
                    std::swap(right[col + row * SideSize], right[col + 1 + row * SideSize]);
                    result.push_back(right);
                }
                if (col > 0) {
                    sample left{seed};
                    std::swap(left[col + row * SideSize], left[col - 1 + row * SideSize]);
                    result.push_back(left);
                }
            }
        }
    }
    return result;
}

uint32_t get_heuristic(const sample& samp)
{
    uint32_t result = 0;
    for (sample::size_type i = 0; i < samp.size(); i++) {
        auto& element = samp[i];
        auto row = static_cast<int>(element) / SideSize;
        auto col = static_cast<int>(element) % SideSize;
        auto actual_row = static_cast<int>(i) / SideSize;
        auto actual_col = static_cast<int>(i) % SideSize;
        result += static_cast<uint32_t>(abs(actual_row - row) + abs(actual_col - col));
    }
    return result;
}

bool is_completed(const sample& seed)
{
    for (sample::size_type i = 0; i < SideSize * SideSize; i++)
        if (seed[i] != i)
            return false;
    return true;
}

std::list<sample> get_solving(const sample& seed, uint32_t iteration_count)
{
    struct tree_elem {
        sample value;
        std::list<tree_elem> moves;
        tree_elem* parent;
    };

    std::multimap<uint32_t, tree_elem*> search_pool;
    std::set<sample> closed_pool;

    if (is_completed(seed))
        return {seed};

    auto root = tree_elem{seed, {}, nullptr};
    search_pool.insert(std::make_pair(get_heuristic(root.value), &root));
    closed_pool.insert(root.value);

    uint32_t num_of_iterations = 0;
    while (num_of_iterations < iteration_count) {
        auto candidate = search_pool.begin()->second;
        if (search_pool.begin()->first == 0) {
            auto result = std::list<sample>{};
            for (tree_elem* i = candidate; i != nullptr; i = i->parent) {
                result.push_back(i->value);
            }
            return result;
        }
        search_pool.erase(search_pool.begin());
        auto moves = get_possible_moves(candidate->value);

        for (auto& move : moves) {
            if (closed_pool.find(move) == closed_pool.end()) {
                closed_pool.insert(move);
                auto tree_node = candidate->moves.insert(
                    candidate->moves.begin(), {move, {}, candidate});
                search_pool.insert(std::make_pair(get_heuristic(move), &*tree_node));
            }
        }
    }

    return {};
}
