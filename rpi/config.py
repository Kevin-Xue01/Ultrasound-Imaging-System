import cv2
  
def nothing(x):
    pass

name = "rock"
n = 2

PATH = f'../data/{name}_{n}/test.png'
NEW_PATH = f"../data/{name}_{n}/new_image.png"
def main():
    cv2.namedWindow("Trackbar")
    cv2.resizeWindow("Trackbar", 800, 200)  # width, height
    cv2.createTrackbar(
        "Width", "Trackbar", 630, 1000, nothing
    )
    cv2.createTrackbar(
        "Height", "Trackbar", 400, 1000, nothing
    )
    cv2.createTrackbar(
        "Threshold", "Trackbar", 0, 255, nothing
    )

    img = cv2.imread(PATH)
    img = cv2.bitwise_not(img)
    img = cv2.applyColorMap(img, cv2.COLORMAP_OCEAN)
    print(img.dtype)
    width = 630
    height = 400
    print(img.shape)
    while True:
        if cv2.waitKey(1) == ord("q"):  # press q to terminate program
            cv2.imwrite(NEW_PATH, cv2.resize(img, (width, height), interpolation = cv2.INTER_AREA))
            break
        width = cv2.getTrackbarPos(
            "Width", "Trackbar"
        )
        height = cv2.getTrackbarPos(
            "Height", "Trackbar"
        )
        threshold = cv2.getTrackbarPos(
            "Threshold", "Trackbar"
        )
        cv2.imshow("Scan", cv2.threshold(cv2.resize(img, (width, height), interpolation = cv2.INTER_AREA), threshold, 255, cv2.THRESH_BINARY)[1])
        
if __name__ == "__main__":
    main()