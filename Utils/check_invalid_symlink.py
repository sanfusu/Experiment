#! /bin/python3
# 检测指定目录下失效的软连接
#
# @platform: linux
# @author: sanfusu@foxmail.com

# usage:
# python3 check_invalid_symlink.py path_to_check

import os
import sys

# 默认在当前目录查找
ROOT = './'


def justify_symlink(full_path):
    if os.path.islink(full_path):
        parent_path = os.path.dirname(full_path)
        link_path = os.readlink(full_path)
        if os.access(os.path.join(parent_path, link_path), os.F_OK) == False:
            print("\033[1;31;40m {0} \033[0m".format(full_path))


for arg in sys.argv[0:]:
    if os.path.isdir(arg):
        ROOT = arg
    for dirpath, dirnames, filenames in os.walk(ROOT,):
        for dirname in dirnames:
            justify_symlink(os.path.join(dirpath, dirname))
        for filename in filenames:
            justify_symlink(os.path.join(dirpath, filename))

# else:
#     print("\033[1;31m ERROR:\033[0m {0} is not a path".format(arg))
