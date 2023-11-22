import serial
import socket
import time

# Set the serial port name for your Arduino
serial_port = '/dev/ttyACM0'  # Replace with the correct port for your Arduino

# Set the IP address and port for the server
server_ip = '0.0.0.0'  # Listen on all available network interfaces
server_port = 8000  # Choose a port number that is not in use

# Open the serial connection to Arduino
ser = serial.Serial(serial_port, 115200, timeout=1)
ser.reset_input_buffer()

# Set up a socket server to accept incoming connections
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((server_ip, server_port))
    server_socket.listen(1)

    print("Waiting for connection...")
    connection, client_address = server_socket.accept()

    try:
        print("Connection established:", client_address)
        
        while True:
            data = connection.recv(1024).decode('utf-8')
            ser.write(data.encode('utf-8'))  # Send the received data to Arduino as bytes
            
            if not data:
                print("Check2")
                break

    finally:
        connection.close()
        print("Connection closed.")
