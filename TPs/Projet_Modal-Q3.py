import numpy as cp
import math
from tqdm import tqdm
alpha = -0.875

value_2 = cp.array([1, 1, 1, 2, 2, 3])
saut_1 = lambda x: cp.ones(shape=x) #correspond à m=1
saut_2 = lambda x: value_2[cp.random.randint(low=6, size=x)] #correspond à m=3

# ### Limite macroscopique

# #### prix negatif

# In[24]:


#Monte-Carlo 
from numba import jit

@jit(nopython=True)
def proba_negatif(N, signes, increments, P0):
    ruines = 0
    for i in range(len(N) - 1):
        somme = P0
        ruine = 0
        signe = signes[N[i]]
        for j in range(N[i], N[i+1]):
            somme += signe * increments[j]
            if somme < 0:
                ruine = 1
                break
            signe *= signes[j+1]
        ruines += ruine
    return ruines
    

def Q3_limite_macro(lamb, T,saut,P0,M,alpha):
    # Sauts
    N = cp.random.poisson(lamb*T, size=M + 1)
    N[0] = 0
    N = N.cumsum()
    
    increments = saut(N[-1] + 1)
    # Signes
    signes = -1 + 2 * cp.random.binomial(1, (1 + alpha) / 2, size=N[-1] + 1) # 1 : rester le même signe
    signes[N[:-1]] = -1 + cp.random.binomial(1, 0.5, size=M) * 2 # Début : -1 ou 1 de proba 1/2

    proba = 0
    return proba_negatif(N, signes, increments, P0)


T = 8*250*24*60*60
lamb = 1/300
M = int(1e7)
P0=1000

print("Q3 prix negatif m = 3")
proba = 0
for i in tqdm(range(M // 1000)):
    proba += Q3_limite_macro(lamb,T,saut_2,P0,1000,alpha)
proba /= M
print(proba)
print(1.96 * cp.sqrt(proba * (1 - proba) / M))


# In[26]:


print("Q3 prix negatif m = 1")
proba = 0
for i in tqdm(range(M // 1000)):
    proba += Q3_limite_macro(lamb,T,saut_1,P0,1000,alpha)
proba /= M
print(proba)
print(1.96 * cp.sqrt(proba * (1 - proba) / M))


# #### Quantile

# In[28]:


from numba import jit

def Q3_limite_macro_quantile(lamb, T,saut,P0,M,alpha):
    quantiles = cp.zeros(M)
    for i in tqdm(range(M)):
        N = cp.random.poisson(lamb * T)
        increments = saut(N)
        signes = -1 + 2 * cp.random.binomial(1, (1 + alpha) / 2, size=N)
        signes[0] = -1 + 2 * cp.random.binomial(1, 0.5, size=1)
        signes = signes.cumprod()
        quantiles[i] = (increments * signes).sum() + P0
    return quantiles


# In[29]:


print("Q3 prix negatif m = 1")
proba = Q3_limite_macro_quantile(lamb,T,saut_1,P0,M,alpha)
proba = cp.sort(proba)
print(proba[int(M*1e-6)], proba[int(M - M*1e-6)])


# In[ ]:


print("Q3 prix negatif m = 3")
proba = Q3_limite_macro_quantile(lamb,T,saut_2,P0,M,alpha)
proba = cp.sort(proba)
print(proba[int(M*1e-6)], proba[int(M - M*1e-6)])
