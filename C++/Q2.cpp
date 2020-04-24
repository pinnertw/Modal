#include "Q2.hpp"
#include<iostream>
#include <thread>
#include <vector>
#include <algorithm>
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


double Q2::ruines(int size){
    Sum ruine;
    vector<thread> threads;
    // (size) echantillionages.
    for (int i = 0; i < size; i++){
        threads.push_back(thread(&Q2::ruines_once, this, ref(ruine)));
    }
    for (int i = 0; i < size; i++){
        threads[i].join();
    }
    return (double) ruine.sum / (double) size;
}
