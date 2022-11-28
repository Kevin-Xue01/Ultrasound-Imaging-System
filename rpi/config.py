import cv2
  
def nothing(x):
    pass

def main():
    cv2.namedWindow("Trackbar")
    cv2.resizeWindow("Trackbar", 800, 200)  # width, height
    cv2.createTrackbar(
        "Width", "Trackbar", 20, 1000, nothing
    )
    cv2.createTrackbar(
        "Height", "Trackbar", 20, 1000, nothing
    )

    img = cv2.imread("../data/paper_1/test.png")
    while True:
        if cv2.waitKey(1) == ord("q"):  # press q to terminate program
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