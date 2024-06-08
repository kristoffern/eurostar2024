import logging

# Create logger
logger = logging.getLogger()
logger.setLevel(logging.DEBUG)  # Set to lowest level to capture all logs

# Create console handler and set level to INFO
console_handler = logging.StreamHandler()

# Create formatter and add it to the handler
formatter = logging.Formatter('%(levelname)s---%(name)s---%(message)s')
console_handler.setFormatter(formatter)

# Add the handler to the logger
logger.addHandler(console_handler)

# Example usage
logger.debug('This is a debug message')
logger.info('This is an info message')
logger.warning('This is a warning message')
logger.error('This is an error message')
logger.critical('This is a critical message')