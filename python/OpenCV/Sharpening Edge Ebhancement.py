import cv2
import numpy as np

img = cv2.imread('./images/1.jpg')

kernel_sharpen_3 = np.array([[-1,-1,-1,-1,-1],
                             [-1,2,2,2,-1],
                             [-1,2,8,2,-1],
                             [-1,2,2,2,-1],
                             [-1,-1,-1,-1,-1]]) / 8.0

output_3 = cv2.filter2D(img, -1, kernel_sharpen_3)

cv2.imwrite('2.jpg',output_3)

cv2.waitKey(0)