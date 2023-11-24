import numpy as np
from PIL import Image
import serial
import cv2


MOTOR_INO = 'COM14'
PIEZO_INO = 'COM8'

def handle_image_size_line(line):
    return int(line.split(" ")[1])

def main():
    global IMG
    motor = serial.Serial(MOTOR_INO, 9600, timeout=1)
    piezo = serial.Serial(PIEZO_INO, 9600, timeout=1)

    motor.reset_input_buffer()

    counter = 0
    image_size = []

    while True:
        if motor.in_waiting > 0:
            line = motor.readline().decode('utf-8').rstrip()
            if counter < 2:
                print(line)
                image_size.append(handle_image_size_line(line))
                if len(image_size) == 2:
                    IMG = np.zeros(tuple(image_size), dtype=np.uint8)
                counter += 1

            print(f'Recieved: "{line}" from Motor')
            coords = handle_motor_input(line)

            if coords:
                x, y = coords
                dist = query_from_piezo(piezo)
                print(f"{dist} cm at ({x}, {y})")

                IMG[x, y] = dist
                
                cv2.imshow("Scan", cv2.resize(IMG, (2*max(image_size), 2*max(image_size)), interpolation = cv2.INTER_AREA))
                cv2.waitKey(1)
                if (x, y) == (image_size[0]-1, image_size[1]-1):
                    fname = "test.png"
                    np.save("mat", IMG)
                    # IMG *= (255/np.max(IMG))
                    # Image.fromarray(IMG).convert("L").save(fname)
                    cv2.imwrite(fname, IMG)
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
