#coding=utf-8 

from PIL import Image
import re,os
import sys
 



def crop_by_width(centimeter,src,dst):
    im = Image.open(src)
    target_dpi=254
    target_width=0
    try:
        target_dpi= im.info['dpi'][0]
        target_width=centimeter/2.54*target_dpi
    except KeyError:
        pass
        
    if target_width!=0 and im.size[0]>target_width:
        x=(im.size[0]-target_width)/2
        y=0
        w=target_width+x
        h=im.size[1]
        imc=im.crop((x,y,w,h))
        imc.save(dst,dpi=(target_dpi,target_dpi))

file_paths = sys.argv[1:]
# 宽度（厘米）
dimension=60.9

for p in file_paths:
    crop_by_width(dimension,p,p)
    print "裁剪：",p,"到宽度60.9厘米完成"

        