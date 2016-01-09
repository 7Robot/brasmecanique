import serial
import time
import cv2
import numpy as np
from userfunctions import *



device = '/dev/ttyACM0'
#device = '/dev/ttyUSB0'
baudrate = '57600'
ser = serial.Serial(device, baudrate)  # open serial port @ baudrate
print(ser.name + device + " @ " + baudrate + "bps  chosen")         # check which port was really used


cap = cv2.VideoCapture(0)
print(cap.get(3)) # x size of frame
print(cap.get(4)) # y size of frame

x = 0
y = 0


while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    #convert frame to BW
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    output = frame.copy()

    # detect circles in the image
    circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1.2, 100, param2=100)

    # Draw detected circles if some of them were found
    if circles is not None:
        # convert the (x, y) coordinates and radius of the circles to integers
        circles = np.round(circles[0]).astype("int")

        # loop over the (x, y) coordinates and radius of the circles
        for (x, y, r) in circles:
            # draw the circle in the output image, then draw a rectangle
            # corresponding to the center of the circle
            cv2.circle(output, (x, y), r, (0, 255, 0), 4)
            cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)


    # show the output image
    cv2.imshow("video", output)

    xcoord = int(remap(x, 0, 640, 0, 360))

    mystr = '$x='+str(xcoord)+';'
    print(mystr)
    ser.write(mystr.encode())

    #delay to not fuck UART
    time.sleep(0.1)


    #exit if q key is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
ser.close()             # close port






