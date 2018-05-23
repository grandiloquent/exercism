from PIL import Image
import re,os,math
import sys


def combineImages(width):
    im=Image.new('RGB',(width,100),(255,255,255))
    im.show()

def getResoultion(image):
    return image.info['dpi']
def px2cm(px,dpi):
     return px /float( dpi) * 2.539999918
def cm2px(cm,dpi):
     return cm / 2.539999918 * dpi
     
def calculateSize(image):
    dpi=254
    imageDPI=getResoultion(image)
    if dpi==imageDPI[0]:
        return image.size
    else:
        widthInCentimeter=px2cm(image.size[0],imageDPI[0])
        heightInCentimeter=px2cm(image.size[1],imageDPI[1])
        return(round(cm2px(widthInCentimeter,dpi),0),round(cm2px(heightInCentimeter,dpi),0))

def main():
    dir='C:/Users/Administrator/Desktop/123'
    for filename in os.listdir(dir):
        im=Image.open(os.path.join(dir,filename))
        
        print calculateSize(im)

if __name__ == '__main__':
    main()