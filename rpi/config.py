import cv2
  
def nothing(x):
    pass

name = "scissors"
n = 4

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

    img = cv2.imread(PATH)
    img = cv2.bitwise_not(img)
    img = cv2.applyColorMap(img, cv2.COLORMAP_OCEAN)

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
        print(width)
        print(height)
        cv2.imshow("Scan", cv2.resize(img, (width, height), interpolation = cv2.INTER_AREA))

if __name__ == "__main__":
    main()