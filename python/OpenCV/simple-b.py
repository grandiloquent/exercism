import cv2
import math
import numpy as np
import sys
import os.path
import os
import re
from scipy.interpolate import UnivariateSpline

def create_LUT_8UC1(x, y):
    """Creates a look-up table using scipy's spline interpolation"""
    spl = UnivariateSpline(x, y)
    return spl(xrange(256))

def auto_white_balance(filename,dir):
    img=cv2.imread(filename)
    c_r, c_g, c_b = cv2.split(img)
    lut=create_LUT_8UC1([0,  128, 192, 256],
                                                 [0,128, 182, 256])
    print lut
    c_b = cv2.LUT(c_b,lut).astype(np.uint8)
    out = cv2.merge((c_r, c_g, c_b))
    cv2.imwrite(os.path.join(dir,filename),out,[int(cv2.IMWRITE_JPEG_QUALITY), 95])
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