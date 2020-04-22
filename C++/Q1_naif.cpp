#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

extern int saut_1();
extern int saut_3();

//    Q1
double ruines_Q1(int size, int P0, int T, double lamb, int m){
  int ruine = 0;
  int N;
  int somme;
  default_random_engine generator;
  generator.seed(time(nullptr));
  poisson_distribution<int> distribution(T * lamb);

  // (size) echantillionages.
  for (int i = 0; i < size; i++){
    N = distribution(generator);
    somme = P0;
    if (m == 1){
      for (int j = 0; j < N; j++){
        somme += saut_1();
        if (somme < 0){
          ruine += 1;
          break;
        }
      }
    }
    else if (m == 3){
      for (int j = 0; j < N; j++){
        somme += saut_3();
        if (somme < 0){
          ruine += 1;
          break;
        }
      }
    }
  }
  return (double) ruine / (double) size;
}

pi quantiles_Q1(int size, int P0, int T, double lamb, int m, double quantile){
  vi echant (size, 0);
  int N;
  int somme;
  default_random_engine generator;
  generator.seed(time(nullptr));
  poisson_distribution<int> distribution(T * lamb);

  // (size) echantillionages.
  for (int i = 0; i < size; i++){
    N = distribution(generator);
    somme = P0;
    if (m == 1){
      for (int j = 0; j < N; j++){
        somme += saut_1();
      }
    }
    else if (m == 3){
      for (int j = 0; j < N; j++){
        somme += saut_3();
      }
    }
    echant[i] = somme;
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
