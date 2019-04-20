#! /bin/python3
# 检测指定目录下失效的软连接
#
# @platform: linux
# @author: sanfusu@foxmail.com

# usage:
# python3 check_invalid_symlink.py path_to_check
#

import os
import sys
import argparse
from pathlib import Path

parser = argparse.ArgumentParser(description='扫描指定目录下所有的无效符号连接（软链接）')
parser.add_argument('PATH_LIST', nargs='*', default=['./'], type=Path)

args = parser.parse_args()

def justify_symlink(full_path):
    if os.path.exists(full_path) == False:
        print("\033[1;31;40m {0} \033[0m".format(full_path))

for arg in args.PATH_LIST:
    if os.path.isdir(arg):
        for dirpath, dirnames, filenames in os.walk(arg):
            for dirname in dirnames:
                justify_symlink(os.path.join(dirpath, dirname))
            for filename in filenames:
                justify_symlink(os.path.join(dirpath, filename))