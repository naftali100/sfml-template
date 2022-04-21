#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Randomizer {
public:
    Randomizer() : device_(), engine_(device_()){};
    int rnd(int a, int b) {
        std::uniform_int_distribution<int> uni_dist(a, b);
        return uni_dist(engine_);
    };
    double rnd(double a, double b) {
        std::uniform_real_distribution<double> uni_dist(a, b);
        return uni_dist(engine_);
    };

private:
    std::random_device device_;
    std::default_random_engine engine_;
};


#endif