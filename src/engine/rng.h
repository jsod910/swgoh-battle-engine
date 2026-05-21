#include <random>

namespace BattleRNG {
    inline thread_local std::mt19937 engine(std::random_device{}());

    inline void setSeed(unsigned int seed) {
        engine.seed(seed);
    }

    inline double roll() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(engine);
    }
}

// class RNG {
// public:
//     RNG(unsigned int seed) : engine(seed) {}

//     double getRoll() {
//         std::uniform_real_distribution<double> dist(0.0, 1.0);
//         return dist(engine);
//     }
// private:
//     std::mt19937 engine;
// };