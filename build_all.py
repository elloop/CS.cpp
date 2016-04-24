#coding=utf-8

import os
import sys
import getopt
import shutil

PROJECTS = (
    "Algorithm",
    "c_language",
    "TotalSTL",
    "TrainingGround",
    "UnderstandingCpp11"
)

#PLATFORMS = ("mac", "windows", "linux")
# PLATFORMS = {
    # "windows":"Visual Studio 14 2013 win64",
    # "mac":"Xcode",
    # "linux":"",
# }

PLATFORMS = {
    "windows":"Visual Studio 12 2013 Win64",
    "mac": "Xcode",
    "unix": ""
}

def build_all(argv):
    try:
        opts, args = getopt.getopt(argv, "hp:", ["platform="])
    except getopt.GetoptError:
        print("build_all.py -p <platform> | all")
        sys.exit(2)
    for opt, arg in opts:
        if opt == "-h":
            print("build_all.py -p <platform>[, <platform2>[, <platform3>]]")
        elif opt in ("-p", "--platform"):
            if arg not in PLATFORMS and (arg != "all"):
                #print("Invalid platform: %s\nValid platforms: mac, windows, linux, all" % arg)
                print("Invalid platform: %s\nValid platforms: windows" % arg)
                sys.exit(2)
            platform = arg

    print("Build platform: %s" % platform)

    
    root_dir = os.getcwd()
    print("root dir: %s" % root_dir)

    
    # build_platforms = PLATFORMS.keys() if platform == "all" else [platform]

    generator = PLATFORMS[platform]
    for project in PROJECTS:
        os.chdir(root_dir)
        work_dir = os.path.join(root_dir, project, "build")
        print("work_dir: %s" % work_dir)
        if os.path.exists(work_dir):
            if work_dir != "/" and work_dir != "~":
                print("removing %s" % work_dir)
                shutil.rmtree(work_dir)
        os.mkdir(work_dir)
        os.chdir(work_dir)
        if generator == "":
            cmd_p = "cmake .."
        else:
            cmd_p = 'cmake .. -G "{gener}"'.format(gener=generator)
        print(cmd_p)
        os.system(cmd_p)
        os.system("pause")

if __name__ == "__main__":
    build_all(sys.argv[1:])
