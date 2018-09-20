import numpy as np
import matplotlib.pyplot as plt


# results from serial version of matrix multiplication with size of matrices: 10, 100, 1000, 10000, 20000, 30000, 40000, 50000, ...
pthread_version = [0.001, 0.002, 0.467, 4.224, 18.451, 48.641, 100.98]
# results from serial version of matrix multiplication with size of matrices: 10, 100, 1000, 10000, 20000, 30000, 40000, 50000, ...
serial_version = [0.017, 0.005, 5.374, 107.893, 426.068]

matrix_sizes = ('10', '100', '1000', '2000', '3000', '4000' ,'5000')
x_pos = np.arange(len(serial_version))
x_pos = np.arange(len(pthread_version))


plt.plot(serial_version, label = 'Serial Version')
plt.plot(pthread_version, label = 'Pthread Version')

plt.xlabel('Matrix sizes (N)')
plt.xticks(x_pos, matrix_sizes)
plt.ylabel('Execution time (s)')
plt.title('Matrix Multiplication in Parallel Computing')
plt.grid(True)
plt.legend()

plt.show()

