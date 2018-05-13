# from __future__ import (
#     division, absolute_import, print_function, unicode_literals)

# import cv2 as cv
# import numpy as np


# def show(final):
#     print('display')
#     cv.imshow('Temple', final)
#     cv.waitKey(0)
#     cv.destroyAllWindows()

# # Insert any filename with path
# img = cv.imread('C:/Users/Administrator/Desktop/exercism/python/OpenCV/1.jpg')
# final = cv.cvtColor(img, cv.COLOR_BGR2LAB)

# avg_a = np.average(final[:, :, 1])
# avg_b = np.average(final[:, :, 2])

# for x in range(final.shape[0]):
#     for y in range(final.shape[1]):
#         l, a, b = final[x, y, :]
#         # fix for CV correction
#         l *= 100 / 255.0
#         final[x, y, 1] = a - ((avg_a - 128) * (l / 100.0) * 1.1)
#         final[x, y, 2] = b - ((avg_b - 128) * (l / 100.0) * 1.1)

# final = cv.cvtColor(final, cv.COLOR_LAB2BGR)
# #final = np.hstack((img, final))
# print final.shape[0]
# #show(final)
# cv.imwrite('result.jpg', final)


import cv2 as cv
import numpy as np
import os,re




def cw(f,dir):
    img = cv.imread(f)
    final = cv.cvtColor(img, cv.COLOR_BGR2LAB)

    avg_a = np.average(final[:, :, 1])
    avg_b = np.average(final[:, :, 2])

    for x in range(final.shape[0]):
        for y in range(final.shape[1]):
            l, a, b = final[x, y, :]
            # fix for CV correction
            l *= 100 / 255.0
            final[x, y, 1] = a - ((avg_a - 128) * (l / 100.0) * 1.1)
            final[x, y, 2] = b - ((avg_b - 128) * (l / 100.0) * 1.1)

    final = cv.cvtColor(final, cv.COLOR_LAB2BGR)
    cv2.imwrite(os.path.join(dir,f),final,[int(cv2.IMWRITE_JPEG_QUALITY), 100])
    cv2.waitKey(0)

if __name__ == '__main__':
    dir='auto'
    if not os.path.isdir(dir):
        os.makedirs(dir)
    for filename in os.listdir('.'):
        if re.match(r'.*\.(?:jpg)$',filename, re.IGNORECASE):
            print 'Found File:',filename
            cw(filename,dir)