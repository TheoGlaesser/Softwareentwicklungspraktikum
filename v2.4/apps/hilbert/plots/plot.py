import numpy as np
import matplotlib.pyplot as plt

x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11])
y_gs = np.array([4.44089e-15, 2.87326e-13, 0.000233812, 0.00255051, 0.174556, 1, 1, 1, 1, 1, 1])
y_llt = np.array([1.11022e-16, 2.14273e-14, 1.60982e-13, 9.02062e-12, 3.3777e-11, 1.16167e-10, 5.45042e-08, 1.36288e-07, 0.000210916, 0.00272818, 0.0409507]) 

plt.figure(figsize=(10, 6))
plt.plot(x, y_gs, label='gs_error', color='blue')  
plt.plot(x, y_llt, label='llt_error', color='red')  

plt.xlabel('n')
plt.ylabel('error')
plt.ylim([0,0.04])
plt.title('plot of max||x|| gs_result and llt_result in different dimensions')
plt.legend()

plt.show()
