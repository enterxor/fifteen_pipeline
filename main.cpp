#include <cstdint>
#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <list>
#include <map>
#include <set>
#include <memory>
constexpr const uint8_t SideSize = 4;
using sample = std::array<uint8_t, SideSize*SideSize>;

sample get_random_sample(){
    sample result{};

    std::iota(std::begin(result), std::end(result), 0);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (begin(result), end(result), std::default_random_engine(seed));

    return result;
}

void print_sample(const sample& _sample){
    for(size_t row = 0;row < SideSize; row++ ){
        for(size_t col = 0; col < SideSize; col++){
	    std::cout << static_cast<unsigned>(_sample[col + SideSize*row]) << " ";
	}
	std::cout << std::endl;
    }
}

std::list<sample> get_possible_moves(const sample& seed){
    std::list<sample> result{};
    for(size_t row =0;row < SideSize; row++){
        for(size_t col = 0; col< SideSize; col ++){
            if(seed[col + SideSize * row]==0){
                if(row < SideSize-1){
		    sample dow{seed};
		    std::swap(dow[col + row*SideSize],
                              dow[col + (row+1)*SideSize]);
		    result.push_back(dow);
                }
		if(row > 0){
		    sample up{seed};
		    std::swap(up[col + row*SideSize],
		              up[col + (row-1)*SideSize]
                    );
		    result.push_back(up);
		}
		if(col < SideSize){
		    sample right{seed};
                    std::swap(right[col + row*SideSize],
                              right[col+1 + row*SideSize]);
                    result.push_back(right);
		}
		if(col > 0){
		    sample left{seed};
                    std::swap(left[col + row*SideSize],
                              left[col-1 + row*SideSize]);
                    result.push_back(left);
		}
	    }
        }
    }
    return result;
}

uint32_t get_heuristic(const sample& samp){
    auto result = 0;
    for(auto i = 0; i < SideSize*SideSize; i ++){
        auto& element = samp[i];
	auto row = element/SideSize;
	auto col = element%SideSize;
	auto actual_row = i/SideSize;
	auto actual_col = i%SideSize;
	result += abs(actual_row - row) + abs(actual_col - col);
    }
    return result;
}

bool is_completed(const sample& seed){
    for(auto i =0 ; i < SideSize*SideSize; i++)
        if(seed[i] != i)
            return false;
    return true;
}

std::list<sample> get_solving(const sample& seed){
    struct tree_elem{
        sample value;
        std::list<tree_elem> moves;
        tree_elem* parent; 
    };

    std::multimap<uint32_t, tree_elem* > search_pool;
    std::set<sample> closed_pool;

    if(is_completed(seed))
	return {seed};

    auto root =  tree_elem{seed,{}, nullptr };
    search_pool.insert(std::make_pair(get_heuristic(root.value),&root));
    closed_pool.insert(root.value);

    uint32_t num_of_iterations =0;
    while(num_of_iterations < 400){
        auto candidate = search_pool.begin()->second;
        if(search_pool.begin()->first == 0){
            auto result = std::list<sample>{};
            for(tree_elem* i = candidate; i = i->parent; i != nullptr){
                result.push_back(i->value);
            }
            return result;
        }
        search_pool.erase(search_pool.begin());
        auto moves = get_possible_moves(candidate->value);

        for(auto& move: moves){
            if(closed_pool.find(move) == closed_pool.end()){
                closed_pool.insert(move);
                auto tree_node = candidate->moves.insert(candidate->moves.begin(),{move, {}, candidate});
                search_pool.insert(std::make_pair(get_heuristic(move),&*tree_node));

            }
        }

        

    }

    return {};
        
}

int main(int argc, char** argv) {
    std::cout << "Hello word" << std::endl;
    auto seed = get_random_sample();
    print_sample(seed);
    std::cout << std::endl;

    
    auto sa = sample { 1,2,0,3,
                       4,5,6,7,
                       8,9,10,11,
                       12,13,14,15
    };
    
    auto solve = get_solving(seed);
    for(auto& ent : solve){
        print_sample(ent);
        std::cout << "Heuristic is " << get_heuristic(ent) << std::endl;
    }
    std::cout<< "Solved for "<< solve.size() << " steps";
    return 0;
}

