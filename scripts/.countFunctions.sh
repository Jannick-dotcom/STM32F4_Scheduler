#!/bin/bash
CNT=$(grep 'addFunction' src/*.cpp | wc -l)
LINE=$(grep -n "#define countTasks" lib/OS/StallardOS.hpp | cut -d ":" -f1)


sed -i $LINE'd' ./lib/OS/StallardOS.hpp
sed -i $LINE"i #define countTasks "$CNT lib/OS/StallardOS.hpp;