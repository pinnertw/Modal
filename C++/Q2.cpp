#include "Q2.hpp"
#include"ThreadPool.h"
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//    Q2
Q2::Q2(int P0_, int T_, double lamb1_, double lamb2_, int m_){
    P0 = P0_;
    T = T_;
    lamb1 = lamb1_;
    lamb2 = lamb2_;
    m = m_;
}

Q2::~Q2(){}

void Q2::ruines_once(Sum& sum){
    preambule* pre1 = new preambule(m, T, lamb1);
    preambule* pre2 = new preambule(1, T, lamb2);
    int J2 = pre2->saut();
    int somme = P0;
    double T1 = pre1->exponential_time();
    double T2 = pre2->exponential_time();
    while (T1 <= T){
        while ((T2 < T) && T2 < T1){
            somme += J2;
            if (somme < 0) {
                delete pre1;
                delete pre2;
                sum.incre();
                return;
            }
            J2 *= -1;
            T2 += pre2->exponential_time();
        }
        somme += pre1->saut();
        if (somme < 0) {
            delete pre1;
            delete pre2;
            sum.incre();
            return;
        }
        T1 += pre1->exponential_time();
    }
    delete pre1;
    delete pre2;
    return;
}


long double Q2::ruines(int size){
    Sum ruine;
    ctpl::thread_pool p(thread_max_2);
    int i = 0;
    while(i < size){
        auto task = bind(&Q2::ruines_once, this, ref(ruine));
        p.push(task);
        i++;
    }
    p.stop();
    return (long double) ruine.sum / (long double) size;
}
