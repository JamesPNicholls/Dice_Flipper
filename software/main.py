"""
Dice Detecting software for ELEX 7820 
Author: James Nicholls, Laurel Kinahan
Date: 5/11/2022

Overview
Take a live camera feed and find the value of the dice face.
Using two sides of a dice determine the relative position of the other faces
Apply a path finding algorithm to find coordinates of 

Code stolen from: https://golsteyn.com/writing/dice
"""
import cv2
import numpy as np
import imutils
from sklearn import cluster

SIDE_LENGTH = 25 #mm
CORN_LENGTH = 14 #mm

def get_blobs(frame):
    frame_blurred = cv2.medianBlur(frame, 7)
    frame_gray = cv2.cvtColor(frame_blurred, cv2.COLOR_BGR2GRAY)
    blobs = detector.detect(frame_gray)
    return blobs

def get_dice_from_blobs(blobs):
    # Get centroids of all blobs
    X = []
    for b in blobs:
        pos = b.pt

        if pos != None:
            X.append(pos)

    X = np.asarray(X)

    if len(X) > 0:
        # Important to set min_sample to 0, as a dice may only have one dot
        clustering = cluster.DBSCAN(eps=60, min_samples=1).fit(X)

        # Find the largest label assigned + 1, that's the number of dice found
        num_dice = max(clustering.labels_) + 1

        dice = []

        # Calculate centroid of each dice, the average between all a dice's dots
        for i in range(num_dice):
            X_dice = X[clustering.labels_ == i]

            centroid_dice = np.mean(X_dice, axis=0)

            dice.append([len(X_dice), *centroid_dice])

        return dice

    else:
        return []

# Finds contour of the dice in order to gain the angle of the dice
def find_squares(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    thresh = cv2.threshold(gray, 180, 255, cv2.THRESH_BINARY)[1]
    can =  cv2.Canny(thresh, 100, 200)
   
    cnts, hier  = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    square = []

    # find the largest square which will be the dice 
    for c in cnts:
        rect = cv2.minAreaRect(c)
        if rect != None:
            if rect[1][0] > 10:
                sqaure = cv2.boxPoints(rect)
                sqaure = np.int0(sqaure)
    try:
        return sqaure
    except:
        return []

# finds the red corner of the dice to determine the adjacent die faces 
def find_corner(frames):
    hsv = cv2.cvtColor(frames, cv2.COLOR_BGR2HSV)

    result = frames.copy()    
    frames = cv2.cvtColor(frames, cv2.COLOR_BGR2HSV)
    
    # lower boundary RED color range values; Hue (0 - 10)
    lower1 = np.array([0, 100, 20])
    upper1 = np.array([10, 255, 255])
    
    # upper boundary RED color range values; Hue (160 - 180)
    lower2 = np.array([160,100,20])
    upper2 = np.array([179,255,255])
    
    lower_mask = cv2.inRange(frames, lower1, upper1)
    upper_mask = cv2.inRange(frames, lower2, upper2)
    
    # mask the image to find the red mark
    full_mask = lower_mask + upper_mask
    cnts, hier  = cv2.findContours(full_mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    corner = [(0,0),0]
    for c in cnts:
        (x,y),r= cv2.minEnclosingCircle(c)
        if r != None:
            if r > corner[1]: # store the largest circle
                corner = [(int(x),int(y)), int(r)]
    
    try:
        # returns only the largest red surface found
        return corner
    except:
        return [] 

def overlay_info(frames, dice, blobs, sqaure, corner):
    # Overlay blobs
    for b in blobs:
        pos = b.pt
        r = b.size / 2

        cv2.circle(frame, (int(pos[0]), int(pos[1])),
                   int(r), (255, 0, 0), 2)
        
    # Holds the positions of the faces in pixels    
    p_array = [[],[],[],[],[],[],[]]
    delta = 0
    top_face = 0
    M = 0

    # Overlay dice number
    for d in dice:
        # Get textsize for text centering
        textsize = cv2.getTextSize(
            str(d[0]), cv2.FONT_HERSHEY_PLAIN, 3, 2)[0]

        cv2.putText(frame, str(d[0]), 
                    (int(d[1] - textsize[0] / 2),
                     int(d[2] + textsize[1] / 2)),
                    cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        
        # first entry is the reference corner
        p_array[d[0]] = np.array([int(d[1] - textsize[0] / 2), 
                                  int(d[2] + textsize[1] / 2),
                                  1])
        # stores the value of the top face
        top_face = d[0]
        # finds the difference between the reference corner and the center of the die face
        delta = p_array[d[0]] - p_array[0]


    try:
        # Robotics transform discussed in elex_7660
        l = np.sqrt(delta.dot(delta))
        angle = np.arctan2(delta[1], delta[0])
        _w2o = np.array([[np.cos(angle), -np.sin(angle), p_array[0][0]], 
                         [np.sin(angle), np.cos(angle),  p_array[0][1]],
                         [0, 0, 1]])

        if top_face == 6:
            p_array[1] = np.matmul(_w2o,(  0,  0, 1))
            p_array[2] = np.matmul(_w2o,(  0, -l, 1))
            p_array[3] = np.matmul(_w2o,(2*l, -l, 1))
            p_array[4] = np.matmul(_w2o,(  0,  l, 1))
            p_array[5] = np.matmul(_w2o,(2*l,  l, 1))
            p_array[6] = (  0,  0, 1)

        elif top_face == 5:
            p_array[1] = np.matmul(_w2o,(  0,  -l, 1))
            p_array[2] = np.matmul(_w2o,(  0,  0,  1))
            p_array[3] = np.matmul(_w2o,(  0,  l, 1))
            p_array[4] = np.matmul(_w2o,(2*l,  -l, 1))
            p_array[5] =(  0,  0, 1)
            p_array[6] = np.matmul(_w2o,(2*l,  l, 1))
            
        elif top_face == 4:
            p_array[1] = np.matmul(_w2o,(2*l,  l, 1))
            p_array[2] = np.matmul(_w2o,( 0,   l, 1))
            p_array[3] = np.matmul(_w2o,( 0,  0, 1))
            p_array[4] = (  0,  0, 1)
            p_array[5] = np.matmul(_w2o,(2*l, -l, 1))
            p_array[6] = np.matmul(_w2o,(  0, -l, 1)) 

        elif top_face == 3:
            p_array[1] = np.matmul(_w2o,(  0,  l, 1))
            p_array[2] = np.matmul(_w2o,(2*l,  l, 1))
            p_array[3] = (  0,  0, 1)
            p_array[4] = np.matmul(_w2o,(  0,  0, 1))
            p_array[5] = np.matmul(_w2o,(  0, -l, 1))
            p_array[6] = np.matmul(_w2o,(2*l, -l, 1))   

        elif top_face == 2:
            p_array[1] = np.matmul(_w2o,(2*l,  l, 1))
            p_array[2] = (  0,  0, 1)
            p_array[3] = np.matmul(_w2o,(2*l, -l, 1))
            p_array[4] = np.matmul(_w2o,(  0, -l, 1))
            p_array[5] = np.matmul(_w2o,(  0,  0, 1))
            p_array[6] = np.matmul(_w2o,(  0,  l, 1)) 

        elif top_face == 1:
            p_array[1] = (  0,  0, 1)
            p_array[2] = np.matmul(_w2o,(  2*l,  l, 1))
            p_array[3] = np.matmul(_w2o,(  0, -l, 1))
            p_array[4] = np.matmul(_w2o,(2*l,  l, 1))
            p_array[5] = np.matmul(_w2o,(  0,  l, 1))
            p_array[6] = np.matmul(_w2o,(  0,  0, 1))

        cv2.putText(frame, "1", ([int(p_array[1][0]), int(p_array[1][1])]), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        cv2.putText(frame, "2", ([int(p_array[2][0]), int(p_array[2][1])]), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        cv2.putText(frame, "3", ([int(p_array[3][0]), int(p_array[3][1])]), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        cv2.putText(frame, "4", ([int(p_array[4][0]), int(p_array[4][1])]), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        cv2.putText(frame, "5", ([int(p_array[5][0]), int(p_array[5][1])]), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        cv2.putText(frame, "6", ([int(p_array[6][0]), int(p_array[6][1])]), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)
        
    except:
        print("no angle")
        print(p_array[2])
        
    try:
        # draws the boudning rect, and bounding circ on the reference corner
        cv2.drawContours(frame,[sqaure],0,(0,0,255),2)
        cv2.circle(frame, corner[0], corner[1], (0,255,0), 2)
    except:
        print(square)
        print("hmmm")


params = cv2.SimpleBlobDetector_Params()

params.filterByInertia
params.minInertiaRatio = 0.6

detector = cv2.SimpleBlobDetector_create(params)
print("Opening Camera")
cap = cv2.VideoCapture(1 + cv2.CAP_DSHOW)
print("Camera Opened")

while(True):
    # Grab the latest image from the video feed
    ret, frame = cap.read()
    # We'll define these later
    blobs = get_blobs(frame)
    dice = get_dice_from_blobs(blobs)
    square = find_squares(frame)
    corner = find_corner(frame)
    out_frame = overlay_info(frame,dice, blobs, square, corner)

    cv2.imshow("frame", frame)

    res = cv2.waitKey(1)

    # Stop if the user presses "q"
    if res & 0xFF == ord('q'):
        break