def start_recording_video():
    with_arduino = True

    cap = cv2.VideoCapture(0)
    database_controller = Database()
    ser = None
    if with_arduino:
        ser = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)
        ser.flush()
    while True:
        (
            _,
            frame,
        ) = cap.read()

        frame = cv2.flip(frame, 1)
        s = frame.shape # (height, width, depth)
        frame = frame[:, s[1] // 2 - 160 : s[1] // 2 + 160, :]

        top, bottom = process_green_rectangle(frame.copy(), database_controller)
        ball = process_ball(frame.copy(), database_controller)
        output_numeric_value, output_string_value = process_state(top, bottom, ball)
        if with_arduino:
            time.sleep(1)
            ser.write(bytes(f"{output_numeric_value}\n", "utf-8"))
            print(f"{output_string_value}")
    
        cv2.imshow("camera", frame)
        if cv2.waitKey(1) == ord("q"):  # press q to terminate program
            break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    start_recording_video()