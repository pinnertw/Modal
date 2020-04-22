#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "preambule.cpp"
#include "Q1_naif.cpp"
#include "Q2_naif.cpp"
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//        TEST
void Q1_1_MC_naif(int size, int P0, int T, double lamb, int m){
  time_t t = -time(nullptr);
  double ruine = ruines_Q1(size, P0, T, lamb, m);
  cout<<ruine<<endl;
  t += time(nullptr);
  cout<<"Finished in "<<t<<" seconds"<<endl;
}

void Q1_2_MC_naif(int size, int P0, int T, double lamb, int m, double quantile){
  time_t t = -time(nullptr);
  pi quants = quantiles_Q1(size, P0, T, lamb, 3, quantile);
  cout<<quants.first<<' '<<quants.second<<endl;
  t += time(nullptr);
  cout<<"Finished in "<<t<<" seconds"<<endl;
}

void Q2_1_MC_naif(int size, int P0, int T, double lamb1, double lamb2, int m){
  time_t t = -time(nullptr);
  double ruine = ruines_Q2(size, P0, T, lamb1, lamb2, m);
  cout<<ruine<<endl;
  t += time(nullptr);
  cout<<"Finished in "<<t<<" seconds"<<endl;
}

int main(){
  int size = 1000000;
  int P0 = 35;
  int T = 4 * 60 * 60;
  double lamb = 1. / 300.;
  double lamb1 = 1. / 660.;
  double lamb2 = 1. / 110.;
  int m = 1;
  double quant = 0.0001;
  cin>>size>>P0>>T>>m>>quant;

  //Q1_1_MC_naif(size, P0, T, lamb, m);
  //Q1_2_MC_naif(size, P0, T, lamb, m, quant);

  Q2_1_MC_naif(size, P0, T, lamb1, lamb2, m);
  return 0;
}
