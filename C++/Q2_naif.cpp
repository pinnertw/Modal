#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

extern int saut_1();
extern int saut_3();

//    Q2
double ruines_Q2(int size, int P0, int T, double lamb1, double lamb2, int m){
  int ruine = 0;
  int ruine_loc;
  int N1;
  int N2;
  vector<double> T1;
  vector<double> T2;
  vi J1;
  int J2;
  int index_T2;
  int somme;
  default_random_engine generator;
  generator.seed(time(nullptr));
  poisson_distribution<int> distribution1(T * lamb1);
  poisson_distribution<int> distribution2(T * lamb2);

  random_device rd;  //Will be used to obtain a seed for the random number engine
  mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  uniform_real_distribution<> dis(0.0, (double)T);

  // (size) echantillionages.
  for (int i = 0; i < size; i++){
    N1 = distribution1(generator);
    N2 = distribution2(generator);
    J2 = saut_1();

    for (int j = 0; j < N1; j++){
      T1.push_back(dis(gen));
    }
    for (int j = 0; j < N2; j++){
      T2.push_back(dis(gen));
    }
    sort(T1.begin(), T1.end());
    sort(T2.begin(), T2.end());

    somme = P0;
    ruine_loc = 0;
    index_T2 = 0;

    if (m == 1){
      for (int j = 0; j < N1; j++){
        if (ruine_loc == 1) break;
        while ((index_T2 < N2) && (T2[index_T2] < T1[j])){
          somme += J2;
          if (somme < 0){
            ruine_loc = 1;
            break;
          }
          J2 *= -1;
          index_T2++;
        }
        somme += saut_1();
        if (somme < 0){
          ruine_loc = 1;
          break;
        }
      }
    }
    else if (m == 3){
      for (int j = 0; j < N1; j++){
        if (ruine_loc == 1) break;
        while ((index_T2 < N2) && (T2[index_T2] < T1[j])){
          somme += J2;
          if (somme < 0){
            ruine_loc = 1;
            break;
          }
          J2 *= -1;
          index_T2++;
        }
        somme += saut_3();
        if (somme < 0){
          ruine_loc = 1;
          break;
        }
      }
    }
    T1.clear();
    T2.clear();
    ruine += ruine_loc;
  }

  return (double) ruine / (double) size;
}
