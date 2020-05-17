import cupy as cp
import math
from tqdm import tqdm
alpha = -0.875

value_2 = cp.array([1, 1, 1, 2, 2, 3])
saut_1 = lambda x: cp.ones(shape=x) #correspond à m=1
saut_2 = lambda x: value_2[cp.random.randint(low=6, size=x)] #correspond à m=3

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

T = 8*250*24*60*60
lamb = 1/300
M = int(1e3)
P0=1000

print("Q3 prix negatif m = 1")
proba = Q3_limite_macro_quantile(lamb,T,saut_1,P0,M,alpha)
proba = cp.sort(proba)
np.save("proba_m=3" + sys.argv[1], proba)
#print(proba[int(M*1e-6)], proba[int(M - M*1e-6)])


# In[ ]:


print("Q3 prix negatif m = 3")
proba = Q3_limite_macro_quantile(lamb,T,saut_2,P0,M,alpha)
proba = cp.sort(proba)
np.save("proba_m=3" + sys.argv[1], proba)
#print(proba[int(M*1e-6)], proba[int(M - M*1e-6)])
