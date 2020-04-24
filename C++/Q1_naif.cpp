#include "preambule.hpp"
#include "Q1_naif.hpp"
#include <vector>
#include <algorithm>

using namespace std;

#define vi vector<int>
#define pi pair<int, int>
//    Q1

Q1_naif::Q1_naif(int P0_, int T_, double lamb_, int m_){
    P0 = P0_;
    T = T_;
    lamb = lamb_;
    m = m_;
}

Q1_naif::~Q1_naif(){}

int Q1_naif::ruines_once(){
    preambule* pre = new preambule (m, T, lamb);
    int N = pre->poisson();
    int somme = P0;
    for (int i = 0; i < N; i++){
        somme += pre->saut();
        if (somme < 0){
            return 1;
        }
    }
    return 0;
}


double Q1_naif::ruines(int size){
    int ruine = 0;
  // (size) echantillionages.
  for (int i = 0; i < size; i++){
      ruine += ruines_once();
  }
  return (double) ruine / (double) size;
}

int Q1_naif::quantiles_once(){
    preambule* pre = new preambule (m, T, lamb);
    int N = pre->poisson();
    int somme = P0;
    for (int i = 0; i < N; i++){
        somme += pre->saut();
    }
    return somme;
}

pi Q1_naif::quantiles(int size, double quantile){
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
