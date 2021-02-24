import control
from control.matlab import *
import matplotlib.pyplot as plt

A = 1/255
T = 200
dt = 0.1

num = [A]
den = [T, 1]



# sys = TransferFunction(num, den, dt)
sys = control.tf(num, den)
t, y = control.step_response(sys)
# t, y = control.impulse_response(sys)
# plt.plot(t, y)
# plt.show()
# control.bode_plot(sys)

H = control.tf([1],[1])


Kp = 300
Ki = 3
Kd = 0
# for Kp in [ 300]:
for Kp in [ Kp]:
    # for Ki in [   3 , 5, 7 , 20 , 50 ]:
    for Ki in [Ki]:
        C = control.tf( [Kp,Ki] , [1,0] )
        sys_ol = control.series (sys , C)

        sys_cl = control.feedback ( sys_ol , H ,  -1)

        t, y = control.step_response(sys_cl)
        plt.plot(t, y, label=("Kp = " + str(Kp) + " , Ki = " + str(Ki) ))
plt.legend()


rlist, klist = control.rlocus(sys_cl)
breakpoint()



plt.show()



plt.show()
