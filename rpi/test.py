import numpy as np
from PIL import Image
import serial
import cv2
import time

MOTOR_INO = 'COM12'
PIEZO_INO = 'COM13'

x_motor_travel_percentage = 85.0 # percentage of x axis travel 
x_motor_pixel_percentage = 25 # percentage of x_motor_total steps for 1 pixel

y_motor_travel_percentage = 85.0 # percentage of x axis travel 
y_motor_pixel_percentage = 25 # percentage of y_motor_total steps for 1 pixel

# x motor
x_motor_pulse_pin = 9
x_motor_dir_pin = 8

x_motor_steps_per_revolution = 5760 # check the switches on the controller

x_motor_max_revolutions = 17 # found by manually rotating x axis lead screw

x_motor_total_steps = (x_motor_travel_percentage / 100.0) * float(x_motor_steps_per_revolution) * float(x_motor_max_revolutions)
x_motor_steps_per_pixel = (x_motor_pixel_percentage / 100.0) * x_motor_total_steps
x_motor_total_pixels = 100.0 / x_motor_pixel_percentage

# y motor
y_motor_steps_per_revolution = 2038; # datasheet

y_motor_max_speed = 15; # rpm

y_motor_max_revolutions = 24; # found by manually rotating y axis lead screw

y_motor_total_steps = (y_motor_travel_percentage / 100.0) * float(y_motor_steps_per_revolution) * float(y_motor_max_revolutions);
y_motor_steps_per_pixel = (y_motor_pixel_percentage / 100.0) * y_motor_total_steps
y_motor_total_pixels = 100.0 / y_motor_pixel_percentage

def step(ser, ax, dir):
    global img
    output = 0
    if dir:
        if ax:
            return output
        else:
            output = -1
    else:
        if ax:
            output = 0
        else:
            output = 1
    print(output)
    ser.write(output)
    while not ser.readline():
        cv2.imshow("Img", img)
        cv2.waitKey(1)


def sense(ser):
    ser.reset_input_buffer()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            l = line.split(" ")

            if l[0] == "distance":
                return int(l[1])


def main():
    global img
    img = np.zeros((int(x_motor_total_pixels), int(y_motor_total_pixels)), dtype=np.uint8)
    motor = serial.Serial(MOTOR_INO, 9600, timeout=1)
    piezo = serial.Serial(PIEZO_INO, 9600, timeout=1)

    motor.reset_input_buffer()
    piezo.reset_input_buffer()
    print("Starting in 3 seconds")
    time.sleep(3)

    motor.reset_input_buffer()
    piezo.reset_input_buffer()

    for j in range(int(y_motor_total_pixels)):
        for i in range(int(x_motor_total_pixels)):
            if i == x_motor_total_pixels - 1:
                step(motor, 1, 0)

            elif (j % 2 == 1):
                distance = sense(piezo)
                print(distance)
                img[x_motor_total_pixels - i - 1, j] = distance
                step(motor, 0, j % 2 == 1)
            else:
                distance = sense(piezo)
                print(distance)
                img[i, j] = distance
                step(motor, 0, j % 2 == 1)



def query_from_piezo(ser):
    ser.reset_input_buffer()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            l = line.split(" ")

            if l[0] == "distance":
                return int(l[1])

if __name__ == "__main__":
    main()