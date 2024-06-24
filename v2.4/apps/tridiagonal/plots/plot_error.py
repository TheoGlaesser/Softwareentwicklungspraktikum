import numpy as np
import matplotlib.pyplot as plt

x = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130])
y_gs = np.array([5.30687e-14, 3.33067e-13, 7.61575e-11, 5.21691e-08, 7.89435e-09, 5.35279e-06, 4.39261e-06, 6.83977e-06, 9.3961e-06, 2.04637e-06, 1.6075e-05, 2.09589e-07, 1.72158e-05 ])
y_llt = np.array([1.38778e-16, 7.77156e-16, 3.77476e-15, 2.77556e-16, 3.77476e-15, 1.11022e-16, 7.21645e-16, 1.55431e-15, 6.66134e-16, 1.11022e-15, 2.22045e-15, 5.55112e-16, 1.9873e-14 ])  

plt.figure(figsize=(10, 6))
plt.plot(x, y_gs, label='gs_error', color='blue')  
plt.plot(x, y_llt, label='llt_error', color='red')  

plt.xlabel('n')
plt.ylabel('error')
plt.title('plot of max||x|| gs_result and llt_result in different dimensions')
plt.legend()

plt.show()
