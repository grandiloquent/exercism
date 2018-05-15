#coding=utf-8 

from PIL import Image
import re,os
import sys
from multiprocessing import Pool




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
        imc.save(dst,dpi=(target_dpi,target_dpi),quality=100)
    return 'OK'
    # return u'裁剪：'+src+u'到宽度'+centimeter+u'厘米完成'

if __name__ == '__main__':
    #freeze_support()  Optional under circumstances described in docs
    file_paths = sys.argv[1:]
    # 宽度（厘米）
    dimension=20.3

    po = Pool(processes = 4)
    resultslist = [] 


    for p in file_paths:
        arg = [dimension,p,p]
        result = po.apply_async(crop_by_width, arg)
        resultslist.append(result)

    for res in resultslist:
        print res.get() 

    raw_input("Press enter to exit ;)")