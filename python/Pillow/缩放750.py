#coding=utf-8 

from PIL import Image
import re,os
import sys
 



def size_by_width(wsize,src,dst):
    im = Image.open(src)
    wpercent = (wsize/float(im.size[0]))
    hsize = int((float(im.size[1])*float(wpercent)))
    im = im.resize((wsize,hsize), Image.ANTIALIAS)
    im.save(dst,quality=100)


file_paths = sys.argv[1:]

w=750

# size_by_width(w,'d:/1.jpg','d:/1.jpg')
for p in file_paths:
    size_by_width(w,p,p)
    print p      