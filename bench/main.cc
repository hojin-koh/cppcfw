#include <celero/Celero.h>
#include "benchutils.h"

#include <chrono>
#include <random>
#include <string>

long getInt() {
  static std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count()+1048596);
  static std::uniform_int_distribution<long> dist(-100000, 100000);
  return dist(rng);
}

std::string getStr() {
  static const char aLet[] {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  const auto len {std::abs(getInt()) % 12};
  const auto idx {std::abs(getInt()) % (sizeof(aLet)/sizeof(aLet[0]))};
  std::string rslt (len, aLet[idx]);
  return rslt;
}

CELERO_MAIN
