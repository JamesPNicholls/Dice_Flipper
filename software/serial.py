import serial
from time import sleep,time
from time import time
import cv2
import numpy as np
import matplotlib.pyplot as plt

ser = serial.Serial(
        # Serial Port to read the data from
        port='/dev/ttyS0',
 
        #Rate at which the information is shared to the communication channel
        baudrate = 9600,
   
        #Applying Parity Checking (none in this case)
        parity=serial.PARITY_NONE,
 
       # Pattern of Bits to be read
        stopbits=serial.STOPBITS_ONE,
     
        # Total number of bits to be read
        bytesize=serial.EIGHTBITS,
 
        # Number of serial commands to accept before timing out
        timeout=1
)


print("Opening Camera")
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FPS, 30)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
print("Camera Opened")



grn_l = (40, 50, 50) 
grn_h = (80, 250, 250)
x_b = [90, 510]
y_b = [10, 460]

def tx(x,y, ball):
    # scaling values to be percentages of the ROI
    print(x,y)
    x = (x-x_b[0])/(x_b[1]-x_b[0])*100+128
    y = (y-y_b[0])/(y_b[1]-y_b[0])*100
    
    if x > 255 :
        x = 255
    elif x < 0:
          x = 128
        
    if y > 100:
        y = 100
    elif y < 0:
        y = 0
        
    if ball == False:
        x = 50+128
        y = 50
        
        

    print(x-128,y)
    ser.write(bytearray([int(x)]))
    rx = ser.read() # wait for an ack to send the next value
    ser.write(bytearray([int(y)]))

    #sleep(0.1) # temp gate to slow it down
    

def find_ball(frame):
    ball = False
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    HSV  = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
      
    g_mask = cv2.inRange(HSV, grn_l, grn_h)
    g_mask = cv2.erode(g_mask, None, iterations = 2)
    g_mask = cv2.dilate(g_mask, None, iterations = 2)
    cnts, hier  = green = cv2.findContours(g_mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#         
#     ret, thresh = cv2.threshold(gray, 150, 210, cv2.THRESH_BINARY)
#     cnts, hier  =cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#            
    
    corner = [(0,0),0]
    for c in cnts:
        (x,y),r= cv2.minEnclosingCircle(c)
        if r != None:
            
            if r > 20 and r < 100: # store the largest circle
                ball = True
                corner = [(int(x),int(y)), int(r)]
                cv2.circle(frame, corner[0], corner[1], (0,255,0), 2)
                cv2.putText(frame, "o", corner[0], cv2.FONT_HERSHEY_SIMPLEX, 1,(255,100,100),1) 
        else:
            ball = False

    return corner[0][0],corner[0][1], ball
    
 
#     received_data = ser.read()              #read serial port
#     sleep(0.03)
#     data_left = ser.inWaiting()             #check for remaining byte
#     received_data += ser.read(data_left)
#     print (received_data)                   #print received data
#     ser.write(received_data)


while True:
    start = time()
    ret, frame = cap.read()
    x,y,ball = find_ball(frame)
    tx(x,y,ball)
    
#     x_data.append(x)
#     y_data.append(y)
#     if len(x_data) > 500:
#         plt.plot(range(1, len(x_data)+1), x_data, color = "red")
#         plt.plot(range(1, len(y_data)+1), y_data, color = "blue")
#         plt.show(block = False)
#         x_data = []
#         y_data = []
        


#     cv2.imshow("frame", frame)
#     cv2.waitKey(1);
    end = time();
    delta = end-start
    print(delta)
    

    
    
    
    

