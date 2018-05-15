
from PIL import Image
import re,os,math
import sys

PAPER_24=60.9
PAPER_30=76.2

def px2cm(px,dpi):
     return px /float( dpi) * 2.539999918
def cm2px(cm,dpi):
     return cm / 2.539999918 * dpi

def round_up(num):
    return round(num + 0.49)

def process_image(f):
    im=Image.open(f)
    dpi=im.info['dpi'][0]
    cw=round(px2cm(im.size[0],dpi),1)
    ch=round(px2cm(im.size[1],dpi),1)
  
    count=0
    tl=0
    guess=0
    while tl<PAPER_24:
        count=count+1
        tl=tl+cw
    else:
        # print '24 inch width=>',tl
        if (tl-PAPER_24)/count<1:
            guess=(tl-PAPER_24)/count
            print cw,ch,'24 inch width guess=>',guess,'substract px',round(cm2px(guess,dpi))
            return
    count=0
    tl=0
    while tl<PAPER_24:
        count=count+1
        tl=tl+ch
    else:
       # print '24 inch height=>',tl
        if (tl-PAPER_24)/count<1:
            guess=(tl-PAPER_24)/count
            print cw,ch,'24 inch height guess=>',guess,'substract px',round(cm2px(guess,dpi))
            return
    
    count=0
    tl=0
    while tl<PAPER_30:
        count=count+1
        tl=tl+cw
    else:
       # print '24 inch height=>',tl
        if (tl-PAPER_30)/count<1:
            guess=(tl-PAPER_30)/count
            print cw,ch,'30 inch width guess=>',guess,'substract px',round(cm2px(guess,dpi))
            return

    count=0
    tl=0
    while tl<PAPER_30:
        count=count+1
        tl=tl+ch
    else:
       # print '24 inch height=>',tl
        if (tl-PAPER_30)/count<1:
            guess=(tl-PAPER_30)/count
            print cw,ch,'30 inch height guess=>',guess,'substract px',round(cm2px(guess,dpi))
            return
    


# def process_image(f):
#     im=Image.open(f)
#     dpi=im.info['dpi'][0]
    
#     wc= round(px2cm(im.size[0],dpi),1)
#     hc= round(px2cm(im.size[1],dpi),1)
#     wr=PAPER_24/wc
#     hr=PAPER_24/hc
#     dw = round((PAPER_24 / round(wr) - wc), 2)
#     dh=round((PAPER_24/round(hr)-hc),2)
#     if abs(dw)<1 or abs(dh)<1:
#         print 'file name=>',os.path.basename(f),'width,height=>',str(im.size[0])+'x'+str(im.size[1]),'dpi =>',dpi,'width centimeter=>',px2cm(im.size[0],dpi)
#         # print  wc,hc,wr,hr,dw,dh
#         if wr%1>hr%1:
#             tw= round(cm2px(abs(dw),dpi))
#             print 'Best guess=>width','subtract length(px)=>',tw
#             crop_image(im,(tw/2,0,im.size[0]-(tw/2),im.size[1]),f)
#         else:
#             th=round(cm2px(abs(dh),dpi))
#             print 'Best guess=>height',th
#             crop_image(im,(0,th/2,im.size[0],im.size[1]-(th/2)),f)
#     else:
#         print 'Best guess=>30 Inch'
#         wr=PAPER_30/wc
#         hr=PAPER_30/hc
#         dw = round((PAPER_30 / round(wr) - wc), 2)
#         dh=round((PAPER_30/round(hr)-hc),2)
#         if abs(dw)<1 or abs(dh)<1:
#             if wr%1>hr%1:
#                 tw= round(cm2px(abs(dw),dpi))
#                 print 'Best guess=>width','subtract length(px)=>',tw
#                 crop_image(im,(tw/2,0,im.size[0]-(tw/2),im.size[1]),f)
#             else:
#                 th=round(cm2px(abs(dh),dpi))
#                 print 'Best guess=>height',th
#                 crop_image(im,(0,th/2,im.size[0],im.size[1]-(th/2)),f)
#         else:
#             pass


def crop_image(im,region,f):
    im=im.crop(region)
    im.save(f,quality=95)
    print "Processed Image=>",f


if __name__ == '__main__':
    # file_paths = sys.argv[1:]
    # for p in file_paths:
    #     process_image(p)
    for f in os.listdir('C:/Users/Administrator/Desktop/1'):
        if f.endswith('jpg'):

            process_image('C:/Users/Administrator/Desktop/1/'+f)
