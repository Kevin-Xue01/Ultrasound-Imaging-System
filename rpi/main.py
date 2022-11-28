import numpy as np
from PIL import Image
import serial
import cv2

PORT = "COM12"

def main():
    global IMG
    arduino = serial.Serial(PORT, 9600, timeout=1)

    arduino.reset_input_buffer()

    counter = 0
    image_size = []

    while True:
        if arduino.in_waiting > 0:
            line = arduino.readline().decode('utf-8').rstrip()
            if counter < 2:
                image_size.append(int(line.split(" ")[1]))
                if len(image_size) == 2:
                    IMG = np.zeros(tuple(image_size), dtype=np.uint8)
                counter += 1
                continue

            print(f"Serial: {line}")
            arduino_output = handle_output(line)
            if arduino_output:
                x, y, distance = arduino_output
                IMG[x, y] = distance
                
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

def handle_output(line):
    if '-' not in line:
        l = line.split(" ")
        return int(l[0]), int(l[1]), int(l[2])
    else:
        return False

if __name__ == "__main__":
    main()