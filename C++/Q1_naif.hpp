#pragma once
#include "preambule.hpp"
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//    Q1
class Q1_naif{
    private:
        int P0;
        int T;
        double lamb;
        int m;

    public:
        Q1_naif(int, int, double, int);
        ~Q1_naif();
        int ruines_once();
        double ruines(int);
        int quantiles_once();
        pi quantiles(int, double);
};
