from SDK import *
import logging

global logger 
logger = logging.getLogger(__name__)

def setup_module(module):
    """ setup any state specific to the execution of the given module."""
    global sdk
    logger.info("Running SDK Test")
    sdk = SDK("COM3")
    

def teardown_module(module):
    """ teardown any state that was previously setup with a setup_module
    method.
    """
    sdk.disconnect()

def test_run_PID_speed_test():
    sdk.run_pid_speed_test()