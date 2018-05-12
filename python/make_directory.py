import os

def clean_desktop():
    desktop_path = os.path.expanduser("~/Desktop/")
    for filename in os.listdir(desktop_path):
        ext=os.path.splitext(filename)[1].upper()[1:]
        if len(ext)>0:
            target_dir= os.path.join(desktop_path,ext)
            if not os.path.isdir(target_dir):
                os.mkdir(target_dir)
            target_file=os.path.join(target_dir,filename)
            if not os.path.isfile(target_file):
                os.rename(os.path.join(desktop_path,filename),target_file)

clean_desktop()