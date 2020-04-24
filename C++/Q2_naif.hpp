#pragma once
#include "preambule.hpp"
using namespace std;

#define pi pair<int, int>
//    Q2
class Q2_naif{
    private:
        int P0;
        int T;
        double lamb1;
        double lamb2;
        int m;
    public:
        Q2_naif(int, int, double, double, int);
        ~Q2_naif();
        int ruines_once();
        double ruines(int);
};
