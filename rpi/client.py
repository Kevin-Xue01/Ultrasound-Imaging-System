import numpy as np
from PIL import Image
import serial
import cv2

MOTOR_INO = 'COM13'
PIEZO_INO = 'COM12'

x_max = 301
y_max = 301 # 22 cm

IMG = np.zeros((x_max, y_max), dtype=np.uint8)

def nothing(x):
    pass

# cv2.namedWindow("Trackbar")
# cv2.resizeWindow("Trackbar", 500, 60)  # width, height
# cv2.createTrackbar(
#     "Threshold", "Trackbar", 50, 255, nothing
# )

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
                
                cv2.imshow("Scan", cv2.resize(IMG, (602, 602), interpolation = cv2.INTER_AREA))
                cv2.waitKey(1)
                if (x, y) == (x_max-1, y_max-1):
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