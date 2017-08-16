#! /usr/bin/env python
#-*- coding: UTF-8 -*-
import os
import platform
import re

def os_pause():
    if platform.system() == "windows":
        os.system("pause")
    else:
        os.system('read -n 1 -p "Press any key to continue..."')

def find_cpp(args, wdir, wnames):
    result = args["result"]
    ignoredir = args["ignore"]
    skip = False
    for s in ignoredir:
        if wdir.find(s) != -1:
            skip = True
            break

    if not skip:
        for name in wnames:
            if name.endswith(".cpp"):
                result.append(os.path.join(wdir, name))

def turn_off_except(on):
    result_cpps = []
    ignoredir = ["build"]
    os.path.walk(os.getcwd(), find_cpp, {"result":result_cpps, "ignore":ignoredir})

    for f in result_cpps:
        turn_off_if_not(f, on)

def turn_off_if_not(f, on):
    replace = False
    with open(f, "r") as ff:
        c = ff.readlines()
        p = re.compile('run_gtest\(\s*(\w+).*\)', re.I)
        psub = re.compile("run_gtest", re.I)
        linenum = len(c)
        for i in range(linenum):
            m = p.match(c[i])
            if m and m.group(1) != on:
                c[i] = re.sub(psub, "BEGIN_TEST", c[i])
                replace = True

    if replace:
        with open(f, "w") as fw:
            fw.writelines(c)
            print("save: ", f)

if "__main__" == __name__:
    turn_on = ""
    turn_off_except(turn_on)
    os_pause()

