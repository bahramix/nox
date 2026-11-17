#!/bin/bash

#config
source config.txt

echo compiling using $COMPILER
$COMPILER src/launch.cpp src/core/command.cpp src/core/config.cpp src/platform/linux/linux_process.cpp -o ./nox -Isrc -std=c++23