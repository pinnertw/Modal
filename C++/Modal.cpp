#include "preambule.hpp"
#include "Q1_naif.hpp"
#include "Q2_naif.hpp"

#include<ctime>
#include <chrono>
#include <iostream>
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//        TEST
void Q1_1_MC_naif(int size, int P0, int T, double lamb, int m){
    Q1_naif Q1 = Q1_naif(P0, T, lamb, m);
    cout<<"For Q1-1, we obtained "<<Q1.ruines(size)<<" with the method Monte-Carlo naif, coef P0 = "<<P0<<", T = "<<T<<", lamb = "<<lamb<<", m = "<<m<<endl;
}

void Q1_2_MC_naif(int size, int P0, int T, double lamb, int m, double quantile){
    Q1_naif Q1 = Q1_naif(P0, T, lamb, m);
    pi quants = Q1.quantiles(size, quantile);
    cout<<"For Q1-2, we obtained "<<quants.first<<" "<<quants.second<<" "<<" for quantile = "<<quantile<<" with the method Monte-Carlo naif, coef P0 = "<<P0<<", T = "<<T<<", lamb = "<<lamb<<", m = "<<m<<endl;
}

void Q2_1_MC_naif(int size, int P0, int T, double lamb1, double lamb2, int m){
    Q2_naif Q2 = Q2_naif(P0, T, lamb1, lamb2, m);
    cout<<"For Q2-1, we obtained "<<Q2.ruines(size)<<" with the method Monte-Carlo naif, coef P0 = "<<P0<<", T = "<<T<<", lamb1 = "<<lamb1<<", lamb2 = "<<lamb2<<", m = "<<m<<endl;
}

int main(){
    int t, Q, size, P0, T, m;
    double quant;
    string temp;
    getline(cin, temp);
    getline(cin, temp);
    cin>>t;
    while (t--){
        using namespace std::chrono;
        uint64_t t = -duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        cin>>Q>>size>>P0>>T>>m>>quant;
        if (Q == 1){
            Q1_1_MC_naif(size, P0, T, 1. / 300., m);
        }
        else if (Q == 2){
            Q1_2_MC_naif(size, P0, T, 1. / 300., m, quant);
        }
        else if (Q == 3){
            Q2_1_MC_naif(size, P0, T, 1. / 300., 1. / 110., m);
        }
        t += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout<<"Finished in "<<t<<" miliseconds\n"<<endl;
    }
  //Q1_1_MC_naif(size, P0, T, lamb, m);
  //Q1_2_MC_naif(size, P0, T, lamb, m, quant);
  //Q2_1_MC_naif(size, P0, T, lamb1, lamb2, m);
  return 0;
}
