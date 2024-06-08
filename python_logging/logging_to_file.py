import logging

# Configure logging to a file
logging.basicConfig(filename='app.log', filemode='w', level=logging.DEBUG,
                    format='%(name)s - %(levelname)s - %(message)s')

# Example usage
logging.debug('This will get logged to a file')
logging.info('So will this')