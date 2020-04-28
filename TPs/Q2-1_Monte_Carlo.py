import numpy as np
import scipy
import matplotlib.pyplot as plt
from numba import jit
from numpy.random import exponential, randint
from numpy import array
from tqdm import tqdm

@jit(nopython=True)
def Q2_1_MC(P0, T, m):
  if m == 1:
    value = array([-1, 1])
    low = 2
  else:
    value = array([-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3])
    low = 12
  J2_0 = array([-1, 1])[randint(low=2)]

  somme = P0
  T1 = exponential(660)
  T2 = exponential(110)
  while T1 < T:
    while T2 < T1:
      somme += J2_0
      if somme < 0:
        return 1
      J2_0 *= -1
      T2 += exponential(110)
    somme += value[randint(low=low)]
    if somme < 0:
      return 1
    T1 += exponential(660)
  return 0

def Q2_1_MC_n(P0, T, m, size):
  somme = 0
  for i in tqdm(range(size)):
    somme += Q2_1_MC(P0, T, m)
  return somme / size

P0=35
T = 4*3600
m = 1
M=int(1e9)

p_r = Q2_1_MC_n(P0, T, 1, M)

R_IC = 1.96*np.sqrt(p_r*(1-p_r))/np.sqrt(M) #rayon de l'intervalle de confiance

print("Estimation de la probabilité de ruine pour m=3 par méthode de Monte-Carlo accélérée: {:09.8f}+/-{:09.8f}".format(p_r,R_IC))
