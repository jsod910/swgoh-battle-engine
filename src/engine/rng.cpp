#include "rng.h"

namespace BattleRNG {
    // The actual definition lives here safely in a single translation unit
    thread_local std::mt19937 engine(std::random_device{}());
}
