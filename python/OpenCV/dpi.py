from PIL import Image
import re,os

for filename in os.listdir('.'):
    if re.match(r'.*\.(?:jpg)$',filename, re.IGNORECASE):
        im = Image.open(filename)
        im.save(filename, dpi=(254,254))