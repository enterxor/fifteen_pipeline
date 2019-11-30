#pragma once

#include <array>
#include <cstdint>
#include <list>

constexpr const uint8_t SideSize = 4;

using sample = std::array<uint8_t, SideSize * SideSize>;

sample get_random_sample();

std::list<sample> get_possible_moves(const sample& seed);

uint32_t get_heuristic(const sample& samp);

bool is_completed(const sample& seed);

std::list<sample> get_solving(const sample& seed, uint32_t iteration_count);
