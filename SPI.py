import spidev  # Import the spidev library for SPI communication
import time  # Import the time library for sleep functionality

class Movements:
    def __init__(self, spi_channel: int = 0, speed=5000000):
        self.spi_channel = spi_channel  # SPI channel (bus) to use
        self.speed = speed  # SPI communication speed in Hz
        self.spi = spidev.SpiDev()  # Create an SPI device object
        self.spi.open(0, spi_channel)  # Open SPI port 0, chip select (CS) is set by spi_channel
        self.spi.max_speed_hz = speed  # Set the SPI communication speed

    # Helper method to send and receive 16-bit integer via SPI
    def spi_send_receive_16bit(self, command):
        high_byte = (command << 8) & 0xFF  # Extract high byte
        low_byte = command & 0xFF  # Extract low byte
        response = self.spi.xfer([high_byte, low_byte])  # Send both bytes and receive response
        print(f"Low byte: 0x{low_byte:2x}")
        received_data = (response[0] << 8) | response[1]  # Combine response bytes into one 16-bit value
        print(f"Response 0 0x{response[0]:02x}")
        print(f"Response 1 0x{response[1]:02x}")
        return received_data  # Return the 16-bit received data

    def move_forward(self):
        response = self.spi_send_receive_16bit(0x0057)
        print(f"Response from move_forward: {response:#06x}")

    def move_left(self):
        response = self.spi_send_receive_16bit(0x0041)
        print(f"Response from move_left: {response:#06x}")

    def move_backwards(self):
        response = self.spi_send_receive_16bit(0x0053)
        print(f"Response from move_backwards: {response:#06x}")

    def move_right(self):
        response = self.spi_send_receive_16bit(0x0044)
        print(f"Response from move_right: {response:#06x}")

    def pivot_left(self):
        response = self.spi_send_receive_16bit(0x004F)
        print(f"Response from pivot_left: {response:#06x}")

    def pivot_right(self):
        response = self.spi_send_receive_16bit(0x0050)
        print(f"Response from pivot_right: {response:#06x}")

    def stop(self):
        response = self.spi_send_receive_16bit(0x0051)
        print(f"Response from stop: {response:#06x}")

def main():
    move = Movements()  # Create an instance of the Movements class
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
