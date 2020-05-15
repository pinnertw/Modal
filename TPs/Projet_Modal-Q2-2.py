#!/usr/bin/env python
# coding: utf-8
import numpy as np
import math
import matplotlib.pyplot as plt
from tqdm import tqdm
# Ancien : plus lent
saut_1_ancien = lambda x: np.random.choice([-1, 1], size=x, replace=True, p=[0.5, 0.5]) #correspond à m=1
saut_2_ancien = lambda x: np.random.choice([-3, -2, -1, 1, 2, 3], size=x, replace=True, p=0.5*np.array([1/6, 1/3, 1/2, 1/2, 1/3, 1/6])) #correspond à m=3

# Nouveau : beaucoup plus vite
value_1 = np.array([-1, 1])
value_2 = np.array([-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3])
saut_1 = lambda x : value_1[np.random.randint(low=2, size=x)]
saut_2 = lambda x : value_2[np.random.randint(low=12, size=x)]

# #### MCMC numba

#MC Accéléré - Méthode 2 (pas plus rapide ?)

# On identifie le processus par le processus de Poisson composé, qui finit à un temps fixé T
# On crée des fonctions pour modéliser le processus.


def Q2_2_MC(P0, T, lamb1, lamb2, saut):
  # saut : une fonction qui prend la taille de sortie comme entrée pour les sauts.
  N1 = np.random.poisson(lam=lamb1 * T)
  T1 = np.sort(np.random.uniform(low=0.0, high=T, size=N1))
  J1 = saut(N1)

  N2 = np.random.poisson(lam=lamb2 * T)
  T2 = np.sort(np.random.uniform(low=0.0, high=T, size=N2))

  J2_0 = saut_1(1)[0]

  somme = P0
  index_T2 = 0
  for i in range(len(T1)):
    while index_T2 < N2 and T2[index_T2] < T1[i]:
      somme += J2_0
      J2_0 *= -1
      index_T2 += 1
    somme += J1[i]
  return somme                      # 1 échantillon

def Q2_2_MC_n(P0, T, lamb1, lamb2, saut, size):
  res = []
  for i in tqdm(range(size)):
    res.append(Q2_2_MC(P0, T, lamb1, lamb2, saut))
  return np.array(res)

P0 = 35
T = 4*60*60
lamb1 = 1/660
lamb2 = 1/110
n = int(1e8)
seuil1 = int(n * 1e-4)
seuil2 = int(n * 1e-5)
seuil3 = int(n * 1e-6)

# m = 1
quantiles = Q2_2_MC_n(P0, T, lamb1, lamb2, saut_1, n)
quantiles.sort()
print(quantiles[seuil3 - 1], quantiles[seuil2 - 1], quantiles[seuil1 - 1], quantiles[n - seuil1], quantiles[n - seuil2], quantiles[n - seuil3])

# m = 3
quantiles = Q2_2_MC_n(P0, T, lamb1, lamb2, saut_2, n)
quantiles.sort()
print(quantiles[seuil3 - 1], quantiles[seuil2 - 1], quantiles[seuil1 - 1], quantiles[n - seuil1], quantiles[n - seuil2], quantiles[n - seuil3])
