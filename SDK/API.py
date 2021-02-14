import serial
import logging
from log_config import *
import time



class API():
    """!
    sends commads to the firmware and listens for 
    """
    def __init__(self , comPort ):
        """!

        @param comPort
        """
        self.logger = logging.getLogger(__name__) # log differenciate between classes
        self.comPort = comPort
        self._is_connected = None
        
        # functions
        self.ser = serial.Serial() # Create the serial port object
        self._connect()
        
    
    def _connect(self):
        try:
            # Configure the COM port
            self.ser.port = self.comPort
            self.ser.baudrate = 115200
            self.ser.parity = serial.PARITY_NONE
            self.ser.stopbits = serial.STOPBITS_ONE
            self.ser.bytesize = serial.EIGHTBITS
            self.ser.open() # Open the COM port
            self._is_connected = True
            self.logger.info("Connected to port: {}".format(self.comPort))
            time.sleep(2)
        except:
            self._is_connected = False
            self.logger.critical("Connection failed")
    
    def disconnect(self):
        """!

        @param comPort
        """
        self.ser.close() # Close the COM port
        self.logger.info("Disconnected from port: {}".format(self.comPort))

    def send_command(self, command):
        """!

        @param comPort
        """
        try:
            self.ser.write( ("{}\r").format(command).encode() )
            self.logger.info("Sent message: '{}'".format(command))
        except:
            self.logger.critical("Could not send message: '{}'".format(command))




    
# Getters
    def is_connected():
        return self._is_connected

if __name__ == '__main__':
    api = API("COM3")
