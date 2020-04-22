#include <random>
using namespace std;;

int saut_1(){
  return (rand() % 2) * 2 - 1;
}

int saut_3(){
  int a = rand() % 12;
  if (a < 1) return -3;
  else if (a < 3) return -2;
  else if (a < 6) return -1;
  else if (a < 9) return 1;
  else if (a < 11) return 2;
  else return 3;
}
