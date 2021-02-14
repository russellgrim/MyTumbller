import pytest
from API import *
import logging
from log_config import *
import time

global logger 
logger = logging.getLogger(__name__)


def setup_module(module):
    """ setup any state specific to the execution of the given module."""
    global api
    logger.info("Running Test")
    api = API("COM3")
    

def teardown_module(module):
    """ teardown any state that was previously setup with a setup_module
    method.
    """
    api.disconnect()


def test_find_port():
    assert(api.is_connected)

def test_send_command():
    api.send_command("led start blinking")
    time.sleep(4)
    api.send_command("led stop blinking")