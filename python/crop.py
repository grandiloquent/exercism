#!/usr/bin/python
# -*- coding: UTF-8 -*-

from PIL import Image
import re,os,math
import sys

PAPER_24=60.9
PAPER_30=76.2

def px2cm(px,dpi):
     return round(px /float( dpi) * 2.539999918,2)
def cm2px(cm,dpi):
     return cm / 2.539999918 * dpi

def isclose(a, b, rel_tol=1e-09, abs_tol=0.0):
    return abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)

def process(f):
    im=Image.open(f)
    wc=px2cm(im.size[0],im.info['dpi'][0])
    hc=px2cm(im.size[1],im.info['dpi'][1])
    count=0
    t=0

    while t<60.96:
        t+=wc
        count+=1
    else:
        if  not isclose(t,60.96) and (t-60.96)<count:
            sw=cm2px((t-60.96)/count,im.info['dpi'][0])
            print u"24寸 左右裁剪",round((t-60.96)/count,2),u"厘米"
            crop(im,(sw/2,0,im.size[0]-sw/2,im.size[1]),f,im.info['dpi'][0])
            return 0

    count=0
    t=0

    while t<60.96:
        t+=hc
        count+=1
    else:
        if  not isclose(t,60.96) and  (t-60.96)<count:
            sh= cm2px((t-60.96)/count,im.info['dpi'][1])
            print u"24寸 上下裁剪",round((t-60.96)/count,2),u"厘米",sh
            crop(im,(0,sh/2,im.size[0],im.size[1]-sh/2),f,im.info['dpi'][0])
            return 0

    count=0
    t=0

    while t<76.2:
        t+=wc
        count+=1
    else:
        if  not isclose(t,76.2) and (t-76.2)<count:
            sw=cm2px((t-76.2)/count,im.info['dpi'][0])
            print u"30寸 左右裁剪",(t-76.2)/count,u"厘米"
            crop(im,(sw/2,0,im.size[0]-sw/2,im.size[1]),f,im.info['dpi'][0])
            return 0

    count=0
    t=0

    while t<76.2:
        t+=hc
        count+=1
    else:
        if  not isclose(t,76.2) and  (t-76.2)<count:
            sh=cm2px((t-76.2)/count,im.info['dpi'][1])
            print u"30寸 上下裁剪",(t-76.2)/count,u"厘米"
            crop(im,(0,sh/2,im.size[0],im.size[1]-sh/2),f,im.info['dpi'][0])
            return 0
    return -1
        

def crop(im,area,dst,dpi=254,quality=95):
    im=im.crop(area)
    im.save(dst,quality=quality,dpi=(dpi,dpi))

files=sys.argv[1:]
if __name__ == '__main__':
    for f in files:
        if process(f)==-1:
            print u"未找到合适尺寸，未裁剪"
raw_input("Press Enter to continue...")