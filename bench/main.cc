#include <celero/Celero.h>
#include "benchutils.h"

#include <chrono>
#include <random>

long getInt() {
  static std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count()+1048596);
  static std::uniform_int_distribution<long> dist(-100000, 100000);
  return dist(rng);
}

CELERO_MAIN
