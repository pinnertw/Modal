#pragma once
#include <random>
#include <mutex>
#include <iostream>
#include <chrono>
using namespace std;;

struct Sum{
    int sum = 0;
    mutex mu;
    void incre(){
        mu.lock();
        sum++;
        mu.unlock();
    }
};

static const int values [12]= {-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3};
class preambule{
    private:
        int m;
        int T;
        double lamb;
        default_random_engine gen_poisson;
        // Loi poisson
        poisson_distribution<int> dist_poisson;
        // Loi uniforme
        mt19937 gen;
        uniform_real_distribution<> dist_uniform;
        // Loi exponential
        exponential_distribution<> dist_exp;
    public:
        preambule(int, int, double);
        ~preambule();
        int saut();
        int poisson();
        double uniform_time();
        double exponential_time();
};

