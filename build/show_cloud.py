#!/usr/bin/python
# coding:utf-8

import os
import sys


def show_cloud(file_in):
    cmd = "src/main -ope=render -in=" + file_in
    os.system(cmd)


if __name__ == '__main__':
    if len(sys.argv) < 2:
        exit(1)

    show_cloud(sys.argv[1])
