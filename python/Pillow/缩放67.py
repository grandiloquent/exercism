#coding=utf-8 

from PIL import Image
import re,os,math

import sys
 



def size_by_width(wsize,src,dst):
    im = Image.open(src)
    target_dpi= im.info['dpi'][0]
    wsize=wsize/2.54*target_dpi
    print target_dpi,wsize,math.ceil(wsize)

    wpercent = (wsize/float(im.size[0]))
    hsize = int((float(im.size[1])*float(wpercent)))
    im = im.resize((int(math.ceil(wsize)),hsize), Image.ANTIALIAS)
    im.save(dst,dpi=(target_dpi,target_dpi),quality=100)


file_paths = sys.argv[1:]

w=67
size_by_width(w,u'C:/Users/Administrator/Desktop/15X15婚纱恋人/01.jpg',u'C:/Users/Administrator/Desktop/15X15婚纱恋人/01.jpg')
# size_by_width(w,'d:/1.jpg','d:/1.jpg')
for p in file_paths:
    size_by_width(w,p,p)
    print p      