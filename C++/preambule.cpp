#include "preambule.hpp"
#include <ctime>
using namespace std;;

preambule::preambule(int m_, int T_, double lamb_){
    m = m_;
    T = T_;
    lamb = lamb_;
    gen_poisson.seed(time(nullptr));
    dist_poisson = poisson_distribution<int> (T_ * lamb_);
    gen = mt19937(rd());
    dist_uniform = uniform_real_distribution<> (0.0, (double)T);
    dist_exp = exponential_distribution<> (lamb_);
}
preambule::~preambule(){}

int preambule::saut(){
  return (m = 1)? (rand() % 2) * 2 - 1 : values[rand() % 12];
}

int preambule::poisson(){
    return dist_poisson(gen_poisson);
}

double preambule::uniform_time(){
    return dist_uniform(gen);
}

double preambule::exponential_time(){
    return dist_exp(gen);
}
