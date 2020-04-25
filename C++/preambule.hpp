#pragma once
#include <random>
using namespace std;;


static const bool DEBUG = true;
static const int values [12]= {-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3};
class preambule{
    private:
        int m = 1;
        int T = 4 * 60 * 60;
        double lamb = 1. / 300.;
        double lamb2 = 1. / 660.;
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
