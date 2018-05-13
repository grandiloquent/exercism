#coding=utf-8 

from PIL import Image
import re,os
import sys
 



def crop_to(cw,ch,src,dst):
    im = Image.open(src)
    td=254
    tw=0
    th=0
    try:
        td= im.info['dpi'][0]
        tw=cw/2.54*td
        th=ch/2.54*td
    except KeyError:
        pass
        
    if tw!=0 and im.size[0]>tw:
        x=(im.size[0]-tw)/2
        y=(im.size[1]-th)/2
        w=tw+x
        h=th+y
        imc=im.crop((x,y,w,h))
        imc.save(dst,dpi=(td,td),quality=100)

file_paths = sys.argv[1:]
# 宽度（厘米）
w=40
h=30

for p in file_paths:
    crop_to(w,h,p,p)
    print u'裁剪：',p.decode('utf-8'),u'12寸完成'        