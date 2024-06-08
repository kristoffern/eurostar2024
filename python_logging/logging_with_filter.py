import logging

class OurFilter(logging.Filter):
    def filter(self, record):
        return "a warning" in record.msg

# Basic configuration
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger()
our_filter = OurFilter()
logger.addFilter(our_filter)

# Example usage
logging.debug('This is a debug message')
logging.info('This is an info message')
logging.warning('This is a warning message')
logging.error('This is an error message')
logging.critical('This is a critical message')