import numpy as np
import matplotlib.pyplot as plt

x = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
y_gs = np.array([833, 3202, 21111, 79681, 141470, 218767, 434676, 696115, 1123463, 1695081])
y_llt = np.array([957, 8334, 39410, 62358, 140923, 256549, 436836, 742891, 1100520, 1703395])  

plt.figure(figsize=(10, 6))
plt.plot(x, y_gs, label='gs_runtime', color='blue')  
plt.plot(x, y_llt, label='llt_runtime', color='red')  

plt.xlabel('x')
plt.ylabel('y')
plt.title('plot of gs_runtime and llt_runtime in different dimensions')
plt.legend()

plt.show()
