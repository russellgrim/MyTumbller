from log_config import *
import pandas as pd
from scipy.optimize import curve_fit
import numpy as np
from numpy import exp, linspace, random
import matplotlib.pyplot as plt

class Processor():
    """!

    """

    def __init__(self, test_name ):
        """!
    
        """
        self.test_name = test_name

    def unpack_df_from_csv(self):
        """!
    
        """
        raw_file_name = "../Results/" + self.test_name + "_raw.csv"
        self.df = pd.read_csv (raw_file_name)
        return self.df

    def first_order_responce(self, t, A, T ):
        """!
    
        """
        return A * ( 1 - exp(- t/T) )

    def fit_first_order_responce(self):
        """!
    
        """
        popt, pcov = curve_fit( self.first_order_responce , df['Time (ms)'] , df['Speed (counts per ms)'] , p0=[1, 500])
        self.A = popt[0]
        self.T = popt[1]

    def func(self, x):
        """!
    
        """
        return self.first_order_responce (x, self.A, self.T)
    
    def view (self):
        """!
    
        """
        self.df['Speed Model (counts per ms)'] = self.df['Time (ms)'].apply( lambda x: self.func(x) )

        plt.plot(self.df['Time (ms)'], self.df['Speed (counts per ms)'])
        plt.plot(self.df['Time (ms)'], self.df['Speed Model (counts per ms)'])
        plt.xlabel("Time (ms)")
        plt.ylabel('Speed (counts per ms)')
        plt.title("PID Speed Control Test")
        plt.savefig("../Results/" + self.test_name + "_raw_model.png")

if __name__ == '__main__':
    p = Processor("pid_test_1")
    df = p.unpack_df_from_csv()
    print ( df.head() )
    p.fit_first_order_responce()
    p.view()

    