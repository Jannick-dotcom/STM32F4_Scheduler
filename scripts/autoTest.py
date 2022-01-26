import os
import subprocess
import time

while True:
    result = subprocess.run(['git', 'pull'], stdout=subprocess.PIPE).stdout
    if(not str(result).__contains__("up to date")):
        with open("test/result.txt","wb") as out:
            result = subprocess.run(['platformio', 'test', '-e', 'black_f407ve'], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL).stdout
            out.write(result)
            subprocess.run(['git', 'add', 'test/result.txt'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            subprocess.run(['git', 'commit', '-m', 'UnitTest result'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            subprocess.run(['git', 'push'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(60)