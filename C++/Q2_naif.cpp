#include "Q2_naif.hpp"
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//    Q2
Q2_naif::Q2_naif(int P0_, int T_, double lamb1_, double lamb2_, int m_){
    P0 = P0_;
    T = T_;
    lamb1 = lamb1_;
    lamb2 = lamb2_;
    m = m_;
}

Q2_naif::~Q2_naif(){}
/*
int Q2_naif::ruines_once(){
    vector<double> T1, T2;
    int N1 = pre1->poisson();
    int N2 = pre2->poisson();
    int J2 = pre2->saut();
    for (int j = 0; j < N1; j++) T1.push_back(pre1->uniform_time());
    for (int j = 0; j < N2; j++) T2.push_back(pre2->uniform_time());
    sort(T1.begin(), T1.end());
    sort(T2.begin(), T2.end());
    int somme = P0, index_T2 = 0;
    for (int j = 0; j < N1; j++){
        while ((index_T2 < N2) && (T2[index_T2] < T1[j])){
            somme += J2;
            if (somme < 0) return 1;
            J2 *= -1;
            index_T2++;
        }
        somme += pre1->saut();
        if (somme < 0) return 1;
    }
    return 0;

}
*/
int Q2_naif::ruines_once(){
    preambule* pre1 = new preambule(m, T, lamb1);
    preambule* pre2 = new preambule(1, T, lamb2);
    int J2 = pre2->saut();
    int somme = P0;
    double T1 = pre1->exponential_time();
    double T2 = pre2->exponential_time();
    while (T1 <= T){
        while ((T2 < T) && T2 < T1){
            somme += J2;
            if (somme < 0) return 1;
            J2 *= -1;
            T2 += pre2->exponential_time();
        }
        somme += pre1->saut();
        if (somme < 0) return 1;
        T1 += pre1->exponential_time();
    }
    return 0;
}


double Q2_naif::ruines(int size){
    int ruine = 0;
    // (size) echantillionages.
    for (int i = 0; i < size; i++){
        ruine += ruines_once();
    }
    return (double) ruine / (double) size;
}
