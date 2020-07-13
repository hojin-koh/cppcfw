#include <celero/Celero.h>

CELERO_MAIN

BASELINE(Dumb, Post, 500, 0) {
    int zzz;
    celero::DoNotOptimizeAway(zzz++);
    celero::DoNotOptimizeAway(zzz--);
}

BENCHMARK(Dumb, Pre, 500, 0) {
    int zzz;
    celero::DoNotOptimizeAway(++zzz);
    celero::DoNotOptimizeAway(--zzz);
}
