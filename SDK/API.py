import serial

class API():
    """!
    sends commads to the firmware and listens for 
    """
    def __init__(self , comPort=None ):
        """!

        @param comPort
        """
        self.ser = serial.Serial("COM3") # Create the serial port object
    
    def _init_Port(self, comPort):
        print("Using port: {}".format(comPort))

        # Configure the COM port
        self.ser.port = comPort
        self.ser.baudrate = 115200
        self.ser.parity = serial.PARITY_NONE
        self.ser.stopbits = serial.STOPBITS_ONE
        self.ser.bytesize = serial.EIGHTBITS
        self.ser.open() # Open the COM port


if __name__ == '__main__':
    api = API("COM3")