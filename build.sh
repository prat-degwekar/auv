#! /bin/sh
#
# build.sh
# Copyright (C) 2019 ubuntu <ubuntu@rpi3>
#
# Distributed under terms of the MIT license.
#


mkdir -p temp_build
cd temp_build
cat ../*.ino > a.ino
cp ../Makefile .
make upload
