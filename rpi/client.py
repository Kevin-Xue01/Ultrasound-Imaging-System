import numpy as np
from PIL import Image
import serial

MOTOR_INO = '/dev/ttyUSB0'
PIEZO_INO = '/dev/ttyUSB1'

x_max = 38
y_max = 38

IMG = np.zeros((x_max, y_max))

def main():
    global IMG
    motor = serial.Serial(MOTOR_INO, 9600, timeout=1)
    piezo = serial.Serial(PIEZO_INO, 9600, timeout=1)

    motor.reset_input_buffer()

    while True:
        if motor.in_waiting > 0:
            line = motor.readline().decode('utf-8').rstrip()

            print(f'Recieved: "{line}" from Motor')
            coords = handle_motor_input(line)

            if coords:
                x, y = coords
                dist = query_from_piezo(piezo)
                print(f"{dist} cm at ({x}, {y})")

                IMG[x, y] = dist

                if (x, y) == (x_max-1, y_max-1):
                    fname = "test.png"
                    np.save("mat", IMG)
                    IMG *= (255/np.max(IMG))
                    Image.fromarray(IMG).convert("L").save(fname)
                    print(f"Saved image as {fname}")
                    break

def handle_motor_input(line):
    l = line.split(" ")
    if l[0] != "coords":
        return None
    return int(l[1]), int(l[2])

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