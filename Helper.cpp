#include "Helper.h"

int Helper::generateRandomInt(int low, int high) {

    std::vector<int> hi_lo;
    hi_lo.push_back(low);
    hi_lo.push_back(high);

    // check if the low and high exist in the random map
    if (this->rand_map.count(hi_lo) > 0) {
        // use the existing generator and distribution if so

        std::default_random_engine* gen  = &this->rand_map[hi_lo].generator;
        std::uniform_int_distribution<int>* dist = &this->rand_map[hi_lo].distribution;

        // *gen derefernces the pointer
        return dist->operator()(*gen);
    }

    else {
        gen_dist* gd = new gen_dist();
        gd->distribution = *(new std::uniform_int_distribution<int>(low, high));
        gd->generator = *(new std::default_random_engine);

        std::pair<std::vector<int>, gen_dist> new_pair (hi_lo, *gd);

        this->rand_map.insert(new_pair);
        return generateRandomInt(low, high);
    }
}
