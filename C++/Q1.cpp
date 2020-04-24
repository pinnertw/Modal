#include "preambule.hpp"
#include "Q1.hpp"
#include <vector>
#include <thread>
#include <algorithm>

using namespace std;

#define vi vector<int>
#define pi pair<int, int>
//    Q1

Q1::Q1(int P0_, int T_, double lamb_, int m_){
    P0 = P0_;
    T = T_;
    lamb = lamb_;
    m = m_;
}

Q1::~Q1(){}

void Q1::ruines_once(Sum& sum){
    preambule* pre = new preambule (m, T, lamb);
    int N = pre->poisson();
    int somme = P0;
    for (int i = 0; i < N; i++){
        somme += pre->saut();
        if (somme < 0){
            delete pre;
            sum.incre();
        }
    }
    delete pre;
}


double Q1::ruines(int size){
    Sum ruine;
    vector<thread> threads;
    // (size) echantillionages.
    for (int i = 0; i < size; i++){
        threads.push_back(thread(&Q1::ruines_once, this, ref(ruine)));
    }
    for (int i = 0; i < size; i++){
        threads[i].join();
    }
    return (double) ruine.sum / (double) size;
}

int Q1::quantiles_once(){
    preambule* pre = new preambule (m, T, lamb);
    int N = pre->poisson();
    int somme = P0;
    for (int i = 0; i < N; i++){
        somme += pre->saut();
    }
    delete pre;
    return somme;
}

pi Q1::quantiles(int size, double quantile){
    vi echant (size, 0);
    // (size) echantillionages.
    for (int i = 0; i < size; i++){
        echant[i] = quantiles_once();
    }
    int index_bot = int(ceil(size * quantile));
    nth_element(echant.begin(), echant.begin() + index_bot, echant.end());
    int bot = echant[index_bot];
 
    int index_top = int(ceil(size * (1. - quantile)));
    if (index_top == size) index_top--;
    nth_element(echant.begin(), echant.begin() + index_top, echant.end());
    int top = echant[index_top];
 
    return pi(bot, top);
}
