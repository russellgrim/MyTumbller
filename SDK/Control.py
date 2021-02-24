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


Kp = 200
Ki = 1
Kd = 0
# for Kp in [ 300]:
for Kp in [ Kp]:
    # for Ki in [   3 , 5, 7 , 20 , 50 ]:
    for Ki in [Ki]:
        C = control.tf( [Kp,Ki] , [1,0] )
        sys_ol = control.series (sys , C)

        sys_cl = control.feedback ( sys_ol , 1 ,  -1) # Output TF
        sys_cl_e = control.feedback (  1 , sys_ol ,   -1) # Error TF
        sys_cl_u = control.feedback (  C , sys ,   -1) # Input TF

        fig, axs = plt.subplots(2, 1)
        t, y = control.step_response(sys_cl)
        # plt.plot(t, y, label=("Kp = " + str(Kp) + " , Ki = " + str(Ki) ))
        axs[0].plot(t, y, label="sys_cl")

        t, y = control.step_response(sys_cl_e)
        axs[0].plot(t, y, label="sys_cl_e")
        axs[0].legend()
        t, y = control.step_response(sys_cl_u)
        axs[1].plot(t, y, label="sys_cl_u")

# sys_cl2 = sys_ol/(1+sys_ol)
# denom = control.parallel( [1] , sys_ol )




# breakpoint()
axs[1].legend()
# plt.show()
# plt.clf

# rlist, klist = control.rlocus(sys_cl)
# plt.plot(t, y)
# plt.show()
# plt.clf()
# plt.plot(rlist)
# plt.show()
# sisotool(sys_cl)
plt.show()
# print (klist[86])

