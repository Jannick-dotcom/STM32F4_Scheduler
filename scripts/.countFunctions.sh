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
CNT=$((CNT+1))

echo "Count of processes:  $CNT"
PATHTODAT=$(find -name StallardOSconfig.h)
echo $PATHTODAT
LINE=$(grep -n "#define countTasks" $PATHTODAT | cut -d ":" -f1)

sed -i $LINE'd' $PATHTODAT
sed -i $LINE"i #define countTasks "$CNT $PATHTODAT