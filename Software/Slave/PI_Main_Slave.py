import pygame
import socket
import time

# Set the IP address and port of the Raspberry Pi (server)
raspberry_pi_ip = '172.20.10.2' #orange rassor  # Replace with the actual IP address of your Raspberry Pi
#raspberry_pi_ip = '172.20.10.4' #blue rassor
server_port = 8000  # Make sure it matches the port used in the server script

# Initialize Pygame and the joystick
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

# Set up a socket client to connect to the Raspberry Pi's server
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((raspberry_pi_ip, server_port))

try:
    while True:
        pygame.event.get()
        # Read PlayStation controller inputs
        joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
        axes = joystick.get_numaxes()
        axisarray = []
        for i in range(axes):
            axisarray.append(joystick.get_axis(i)) 
        
        buttons = [joystick.get_button(i) for i in range(joystick.get_numbuttons())]
        
        arr = []
        for i in range(6):
            arr.append(axisarray[i] * -255)
        #print(arr)
        axisarrayint = [int(x) for x in arr]
        #array = buttons, axisarray
        buttons.extend(axisarrayint)        
        #print(array)
        print(buttons)




        #print(array)
        # Define control commands based on controller buttons
        # if buttons[0]:  # Press X button to turn on the light
        #     print("Motor ON")
        #     client_socket.sendall(b'ON')
        # else:  # Release X button to turn off the light
        #     print("Motor OFF")
        #     client_socket.sendall(b'OFF')
        
        #client_socket.sendall(str(array).encode())
        client_socket.sendall(str(buttons).encode())

       
        
        # if axisarray[1]:
        #     SpeedLeft = axisarray[1]*-255
        #     MotorSpeedLeft = (SpeedLeft)
            
        #     client_socket.sendall(str(MotorSpeedLeft).encode()) # Send value as a string
     
          


        time.sleep(0.1)  # Add a small delay to avoid sending commands too quickly

except KeyboardInterrupt:
    # Close the socket connection and exit the script
    client_socket.close()
