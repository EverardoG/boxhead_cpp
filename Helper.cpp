#include "Helper.h"

int Helper::generateRandomInt(int low, int high) {

    std::string hi_lo = std::to_string(low) + "to" + std::to_string(high);

    // check if the low and high exist in the random map
    if (this->rand_map.count(hi_lo) > 0) {
        // use the existing generator and distribution if so

        std::default_random_engine* gen  = &this->rand_map[hi_lo].generator;
        std::uniform_int_distribution<int>* dist = &this->rand_map[hi_lo].distribution;

        // *gen derefernces the pointer
        return dist->operator()(*gen);
    }

    else {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        gen_dist* gd = new gen_dist();
        gd->distribution = *(new std::uniform_int_distribution<int>(low, high));
        gd->generator = *(new std::default_random_engine(seed));

        std::pair<std::string, gen_dist> new_pair (hi_lo, *gd);

        this->rand_map.insert(new_pair);
        return generateRandomInt(low, high);
    }
}

Helper helper;
