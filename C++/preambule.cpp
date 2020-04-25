#include "preambule.hpp"
#include <chrono>
using namespace std;;

preambule::preambule(int m_, int T_, double lamb_){
    m = m_;
    T = T_;
    lamb = lamb_;
    using namespace chrono;
    gen_poisson.seed(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    dist_poisson = poisson_distribution<int> (T_ * lamb_);

    gen = mt19937(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
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
