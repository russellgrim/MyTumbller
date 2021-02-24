from API import *
import pandas as pd
import matplotlib.pyplot as plt

class SDK():
    """!
    """
    def __init__(self, comPort):
        # self.comport = comPort
        self.api = API(comPort)

    def get_data(self):
        d = {'Time (ms)': [],
            'Speed (counts per ms)': [],
            'Position (counts)' : [],
            'Speed Target (counts per ms)' : [],
            'Position Target (counts)' : [],
            'PWM (0-255)' : []
            }
        line = "none"
        while (True):
            line = self.api.read_line()
            if line == "Done":
                break
            time , speed, position , speed_target, position_target, pwm = self.process_line(line)
            d['Time (ms)'].append(time)
            d['Speed (counts per ms)'].append(speed)
            d['Position (counts)'].append(position)
            d['Speed Target (counts per ms)'].append(speed_target)
            d['Position Target (counts)'].append(position_target)
            d['PWM (0-255)'].append(pwm)
            
        
        pf = pd.DataFrame(data=d)
        return pf

    def process_line(self, line):
        myList = line.split(',')
        time = float(myList[0])
        speed = float(myList[1])
        position = float(myList[2])
        speed_target = float(myList[3])
        position_target = float(myList[4])
        pwm = float(myList[5])

        return time , speed, position , speed_target, position_target, pwm

    def run_pid_speed_test(self):
        self.api.send_command("pid")
        df = self.get_data()
        plt.plot(df['Time (ms)'], df['Speed (counts per ms)'])
        plt.xlabel("Time (ms)")
        plt.ylabel('Speed (counts per ms)')
        plt.title("PID Speed Control Test")
        plt.savefig("../Results/pid_test_1_raw.png")
        df.to_csv("../Results/pid_test_2_raw.csv")
        return df

    def run_pid_position_control_test(self):
        self.api.send_command("position control")
        df = self.get_data()
        fig, axs = plt.subplots(3,1)
        axs[0].plot(df['Time (ms)'], df['Speed (counts per ms)'], label="Speed (counts per ms)")
        axs[0].plot(df['Time (ms)'], df['Speed Target (counts per ms)'], label='Speed Target (counts per ms)')
        axs[0].legend()
        axs[1].plot(df['Time (ms)'], df['Position (counts)'], label='Position (counts)')
        axs[1].plot(df['Time (ms)'], df['Position Target (counts)'], label='Position Target (counts)')
        axs[1].legend()
        axs[2].plot(df['Time (ms)'], df['PWM (0-255)'], label='PWM (0-255)')
        axs[2].legend()
        
        axs[2].set_xlabel("Time (ms)")
        axs[0].set_ylabel('Speed (counts per ms)')
        axs[1].set_ylabel('Position (counts)')
        axs[2].set_ylabel('PWM (0-255)')
        axs[0].set_title("PID Position Control Test")
        fig.show()
        fig.savefig("../Results/pid_test_9_raw.png")
        df.to_csv("../Results/pid_test_9_raw.csv")
        return df
    
    
    def disconnect(self):
        self.api.disconnect()



if __name__ == '__main__':
    sdk = SDK("COM3")
    sdk.run_pid_speed_test()
    sdk.disconnect()