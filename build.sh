#! /bin/sh
#
# build.sh
# Copyright (C) 2019 ubuntu <ubuntu@rpi3>
#
# Distributed under terms of the MIT license.
#


mkdir -p temp
cd temp
cat ../*.ino > a.ino
cp ../Makefile .
make upload
