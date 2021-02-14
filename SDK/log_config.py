import logging
from datetime import date

logging.basicConfig(
    filename = f'./logs/{date.today().isoformat()}_sample.log', 
    level = logging.INFO,
    filemode = 'w',
    format = '%(levelname)s:%(asctime)s:%(name)s: %(message)s'
    )
