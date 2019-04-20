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
import stat
from pathlib import Path

parser = argparse.ArgumentParser(description='扫描指定目录下所有的无效符号连接（软链接）')
parser.add_argument('PATH_LIST', nargs='*', default=[os.getcwd()], type=Path)
parser.add_argument('--ignore_hidden_dir', action='store_true',
                    default=False, help='忽略隐藏文件夹')
parser.add_argument('--ignore_hidden_file', action='store_true',
                    default=False, help='忽略隐藏文件')
args = parser.parse_args()

def is_hidden(full_path):
    ret = False

    if sys.platform == 'linux':
        base_name = os.path.basename(full_path)
        ret = base_name.startswith('.')
    elif sys.platform == 'win32':
        ret = os.lstat(
            full_path).st_file_attributes == stat.FILE_ATTRIBUTE_HIDDEN
    return ret


def justify_symlink(full_path):
    if os.path.exists(full_path) == False:
        print("\033[1;31;40m {0} \033[0m".format(full_path))

for arg in args.PATH_LIST:
    if os.path.isdir(arg):
        for dirpath, dirnames, filenames in os.walk(arg, topdown=True):
            for dirname in dirnames[:]:
                full_path = os.path.join(dirpath, dirname)
                if is_hidden(full_path) == True and args.ignore_hidde_dir == True:
                    dirnames.remove(dirname)
                else:
                    justify_symlink(full_path)
            for filename in filenames[:]:
                full_path = os.path.join(dirpath, filename)
                if is_hidden(full_path) == True and args.ignore_hidde_file == True:
                    filenames.remove(filename)
                else:
                    justify_symlink(os.path.join(dirpath, filename))