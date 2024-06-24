import numpy as np
import matplotlib.pyplot as plt

x = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130])
y_gs = np.array([639, 3306, 35720, 50104, 243852, 574221, 1397095, 2168925, 4547800, 8555813, 11212898, 21110550, 35454899])
y_llt = np.array([603, 7162, 31659, 81026, 141394, 254805, 440022, 725046, 1133933, 1706305, 2486919, 3483417, 4788639])  

plt.figure(figsize=(10, 6))
plt.plot(x, y_gs, label='gs_runtime', color='blue')  
plt.plot(x, y_llt, label='llt_runtime', color='red')  

plt.xlabel('n')
plt.ylabel('runtime')
plt.title('plot of gs_runtime and llt_runtime in different dimensions')
plt.legend()

plt.show()
