#coding=utf-8 

from PIL import Image
import re,os
import sys
 



def crop_by_height(centimeter,src,dst):
    im = Image.open(src)
    target_dpi=254
    target_height=0
    try:
        target_dpi= im.info['dpi'][0]
        target_height=centimeter/2.54*target_dpi
    except KeyError:
        pass
        
    if target_height!=0 and im.size[1]>target_height:
        x=0
        y=(im.size[1]-target_height)/2
        w=im.size[0]
        h=target_height+y
        imc=im.crop((x,y,w,h))
        imc.save(dst,dpi=(target_dpi,target_dpi),quality=100)

file_paths = sys.argv[1:]
# 高度（厘米）
dimension=25.4



for p in file_paths:
    try:
        crop_by_height(dimension,p,p)
        print u'裁剪：',p,u'到高度25.4厘米完成'
    except Exception as e:
        print e
    

raw_input("Press enter to exit ;)")