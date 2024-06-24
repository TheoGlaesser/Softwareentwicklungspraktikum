import numpy as np
import matplotlib.pyplot as plt

x = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
y_gs = np.array([3.4972e-15, 6.44009e-15, 3.56312e-15, 5.05151e-15, 6.88338e-15, 3.88578e-15, 2.24043e-13, 7.44405e-14, 5.87308e-14, 3.77476e-15])
y_llt = np.array([3.4972e-16, 5.55112e-16, 7.77156e-16,  5.55112e-16, 6.66134e-16, 1.11022e-15, 1.33227e-15, 8.88178e-16,  1.33227e-15, 2.44249e-15])  

plt.figure(figsize=(10, 6))
plt.plot(x, y_gs, label='gs_error', color='blue')  
plt.plot(x, y_llt, label='llt_error', color='red')  

plt.xlabel('n')
plt.ylabel('error')
plt.title('plot of max||x|| gs_error and llt_error in different dimensions')
plt.legend()

plt.show()
