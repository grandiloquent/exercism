# pip install opencv-contrib-python
import cv2
import math
import numpy as np
import sys
import os.path
import os
import re

def apply_mask(matrix, mask, fill_value):
    masked = np.ma.array(matrix, mask=mask, fill_value=fill_value)
    return masked.filled()

def apply_threshold(matrix, low_value, high_value):
    low_mask = matrix < low_value
    matrix = apply_mask(matrix, low_mask, low_value)

    high_mask = matrix > high_value
    matrix = apply_mask(matrix, high_mask, high_value)

    return matrix

def simplest_cb(img, percent):
    assert img.shape[2] == 3
    assert percent > 0 and percent < 100

    half_percent = percent / 200.0

    channels = cv2.split(img)

    out_channels = []
    for channel in channels:
        assert len(channel.shape) == 2
        # find the low and high precentile values (based on the input percentile)
        height, width = channel.shape
        vec_size = width * height
        flat = channel.reshape(vec_size)

        assert len(flat.shape) == 1

        flat = np.sort(flat)

        n_cols = flat.shape[0]

        low_val  = flat[int(math.floor(n_cols * half_percent))]


        high_val = flat[int(math.ceil( n_cols * (1.0 - half_percent)))]

        print "Lowval: ", low_val
        print "Highval: ", high_val

        # saturate below the low percentile and above the high percentile
        thresholded = apply_threshold(channel, low_val, high_val)
        # scale the channel
        normalized = cv2.normalize(thresholded, thresholded.copy(), 0, 255, cv2.NORM_MINMAX)
        out_channels.append(normalized)

    return cv2.merge(out_channels)

def auto_white_balance(filename,dir):
    img=cv2.imread(filename)
    wb = cv2.xphoto.createGrayworldWB()
    wb.setSaturationThreshold(0.3)
    out = wb.balanceWhite(img)
    cv2.imwrite(os.path.join(dir,filename),out,[int(cv2.IMWRITE_JPEG_QUALITY), 100])
    cv2.waitKey(0)
    print 'Finished',filename

if __name__ == '__main__':
    dir='auto'
    if not os.path.isdir(dir):
        os.makedirs(dir)
    for filename in os.listdir('.'):
        if re.match(r'.*\.(?:jpg)$',filename, re.IGNORECASE):
            print 'Found File:',filename
            auto_white_balance(filename,dir)
    # img = cv2.imread(sys.argv[1])





    # 

    # print img.shape

    # 
    # cv2.imshow("before", img)
    # cv2.imshow("after", out)
    # cv2.waitKey(0)