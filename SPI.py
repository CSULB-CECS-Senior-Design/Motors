import spidev  # Import the spidev library for SPI communication
import time  # Import the time library for sleep functionality

class Movements:
    def __init__(self, spi_channel=0, speed=5000000):
        # Initializer method with optional spi_channel and speed parameters
        self.spi_channel = spi_channel  # SPI channel (bus) to use
        self.speed = speed  # SPI communication speed in Hz
        self.spi = spidev.SpiDev()  # Create an SPI device object
        self.spi.open(0, spi_channel)  # Open SPI port 0, chip select (CS) is set by spi_channel
        self.spi.max_speed_hz = speed  # Set the SPI communication speed

    def test_commands(self):
        # Method to test sending a series of command bytes
        # Commands are represented by their ASCII codes
        data = [ord('W'), ord('A'), ord('S'), ord('D'), ord('O'), ord('P'), ord('Q')]
        for command in data:
            print(f"Attempting to send 0x{command:02x}")  # Print the command in hex format before sending
            received = self.spi.xfer([command])  # Send the command and receive the response
            print(f"Sent: 0x{command:02x}, Received Data: 0x{received[0]:02x}")  # Print sent command and received data in hex
            time.sleep(2)  # Wait for 2 seconds

    # Below methods implement specific movements by sending single-byte commands
    def move_forward(self):
        self.spi.xfer([ord('W')])  # Send the command to move forward

    def move_left(self):
        self.spi.xfer([ord('A')])  # Send the command to move left

    def move_backwards(self):
        self.spi.xfer([ord('S')])  # Send the command to move backwards

    def move_right(self):
        self.spi.xfer([ord('D')])  # Send the command to move right

    def pivot_left(self):
        self.spi.xfer([ord('O')])  # Send the command to pivot left

    def pivot_right(self):
        self.spi.xfer([ord('P')])  # Send the command to pivot right

    def stop(self):
        self.spi.xfer([ord('Q')])  # Send the command to stop movement

def main():
    move = Movements()  # Create an instance of the Movements class
    move.test_commands()  # Testing and debugging purposes
    # Sequentially execute movement commands with pauses in between
    move.move_forward()
    time.sleep(2)
    move.move_left()
    time.sleep(2)
    move.move_backwards()
    time.sleep(2)
    move.move_right()
    time.sleep(2)
    move.pivot_left()
    time.sleep(2)
    move.pivot_right()
    time.sleep(2)
    move.stop()
    time.sleep(2)

if __name__ == "__main__":
    main()  # Execute the main function if the script is run directly
