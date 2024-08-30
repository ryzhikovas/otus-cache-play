#include <benchmark/benchmark.h>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>

const size_t unitsCount = 100'000;

std::mt19937_64 randomGenerator;

int genPos() {
    static std::uniform_int_distribution<int> distr(0, 1000);
    return distr(randomGenerator);
}

template <class Container> void play(Container& units) {
    for (auto& unit : units) {
        unit.x += unit.dx;
        unit.y += unit.dy;
    }
}

template <class U>
void vec(benchmark::State& state) {
    std::vector<U> units(unitsCount);
    for (auto _ : state)
        play(units);

    benchmark::DoNotOptimize(units);
}

struct SimpleUnit {
    SimpleUnit() : x{genPos()}, y{genPos()}, dx{genPos()}, dy{genPos()} {}
    int x;
    int y;
    int dx;
    int dy;
};

BENCHMARK(vec<SimpleUnit>);

struct Unit {
    Unit() : x{genPos()}, y{genPos()}, dx{genPos()}, dy{genPos()} {}
    std::string name;
    int health;
    int mana;
    int damage;
    int x;
    int y;
    int dx;
    int dy;
};
BENCHMARK(vec<Unit>);

template <class U>
void list(benchmark::State& state) {
    std::list<U> units;
    for (size_t i = 0; i < unitsCount; ++i) {
        std::uniform_int_distribution<size_t> ui(0, units.size());
        units.emplace(std::next(units.begin(), ui(randomGenerator)));
    }

    for (auto _ : state)
        play(units);

    benchmark::DoNotOptimize(units);
}

BENCHMARK(list<SimpleUnit>)->Iterations(5);
BENCHMARK(list<Unit>)->Iterations(5);

// sudo cpupower frequency-set --governor performance
BENCHMARK_MAIN();