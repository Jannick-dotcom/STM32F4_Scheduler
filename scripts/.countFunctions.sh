#!/bin/bash

CNTLNS=$(grep 'addFunction' src/*.cpp | wc -l)
CNT=0
allThreadIDs=()

for ((i=1; i<=$CNTLNS; i++)) do
    INCR=0
    THISOCC="$(grep 'addFunction' src/*.cpp | cut -d $'\n' -f$i | cut -d "," -f2)"   #ID der Funktion
    THISOCC=$(($THISOCC + 0))                                                           #In Zahl umwandeln
    for t in ${allThreadIDs[@]}; do                                                    #Jedes Element durchgehen
        if [ $THISOCC -eq $t ]; then                                                   #Wenn ID gleich ist wie das vom Arrayelement
            INCR=1
            break
        fi
    done

    if [ $INCR -eq 0 ]; then
        allThreadIDs+=($THISOCC)                                                            #Zum Array Hinzufügen
        CNT=$((CNT+1))
    fi
done
echo ${allThreadIDs[@]}
echo "Anzahl:  $CNT"

LINE=$(grep -n "#define countTasks" lib/OS/StallardOS.hpp | cut -d ":" -f1)
#hier noch irgendwie einfügen dass nur gezählt wird, wenn IDs unterschiedlich

sed -i $LINE'd' ./lib/OS/StallardOS.hpp
sed -i $LINE"i #define countTasks "$CNT lib/OS/StallardOS.hpp;