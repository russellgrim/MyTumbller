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
            'Speed (counts per ms)': []}
        line = "none"
        while (True):
            line = self.api.read_line()
            if line == "Done":
                break
            time , speed = self.process_line(line)
            d['Time (ms)'].append(time)
            d['Speed (counts per ms)'].append(speed)
        
        pf = pd.DataFrame(data=d)
        return pf

    def process_line(self, line):
        myList = line.split(',')
        time = float(myList[0])
        speed = float(myList[1])

        return time , speed

    def run_pid_speed_test(self):
        self.api.send_command("pid")
        df = sdk.get_data()
        plt.plot(df['Time (ms)'], df['Speed (counts per ms)'])
        plt.xlabel("Time (ms)")
        plt.ylabel('Speed (counts per ms)')
        plt.title("PID Speed Control Test")
        plt.savefig("../Results/pid_test.png")
        df.to_csv("../Results/pid_test.csv")
        return df

    def disconnect(self):
        self.api.disconnect()



if __name__ == '__main__':
    sdk = SDK("COM3")
    sdk.run_pid_speed_test()
    sdk.disconnect()