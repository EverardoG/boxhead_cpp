#ifndef HELPER_H
#define HELPER_H

#include <random>
#include <chrono>
#include <unordered_map>

// struct gen_dist;
struct gen_dist {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
};

class Helper
{
    public:
        int generateRandomInt(int low, int high);

    private:
        std::unordered_map<std::vector<int>,gen_dist> rand_map;
};


#endif