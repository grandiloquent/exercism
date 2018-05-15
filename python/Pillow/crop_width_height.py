#coding=utf-8 

from PIL import Image
import re,os
import sys
 
def px2cm(px,dpi):
     return px /float( dpi) * 2.539999918
def cm2px(cm,dpi):
     return cm / 2.539999918 * dpi



def size_by_width(cw,ch,src,dst):
    im = Image.open(src)
    dpi=im.info['dpi'][0]
    tx=round(cm2px(cw,dpi))
    ty=round(cm2px(ch,dpi))
    x=(im.size[0]-tx)/2
    y=(im.size[1]-ty)/2
    w=im.size[0]-((im.size[0]-tx)/2)
    h=im.size[1]-((im.size[1]-ty)/2)

    print tx,ty,x,y,w,h
    im = im.crop((x,y,w,h))
    im.save(dst,quality=95,dpi=(dpi,dpi))


file_paths = sys.argv[1:]

w=750

#size_by_width(51,25.5,'C:/Users/Administrator/Desktop/1/P001.jpg','C:/Users/Administrator/Desktop/1/P001.jpg')
for p in file_paths:
    size_by_width(51,25.5,p,p)
    print p      