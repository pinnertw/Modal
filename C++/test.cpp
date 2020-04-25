#include<iostream>
#include<cmath>
#include<chrono>
using namespace std;

int main(){
    using namespace chrono;
    cout<< duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count()<<endl;
    int i = 2, t0 = 3, t = 5;
    cout<<"Processing..."<<i<<"/"<<10000<<", ETA : "<<t0 + (t - t0) * 10000 / i<<"s";
    int ruine = 5;
    int size = 10000000;
    cout<<(long double) ruine / (long double) size;
}
