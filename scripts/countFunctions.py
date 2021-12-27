import os
import re

def tasks_created(dir):
    cnt = 0

    pattern = r'\.addFunction(Static)?\(.*\);'
    match = re.compile(pattern)
    
    for r, d, f in os.walk(dir):
        for file in f:
            with open(f'{r}/{file}') as fp:
                lines = fp.read()
                matches = match.findall(lines)
                cnt += len(matches)

    return cnt


def write_task_cnt(task_count):
    
    with open('ECU_Defines/StallardOSconfig.h', 'r+') as f:
        text = f.read()
        text = re.sub(r'#define countTasks \d+', f'#define countTasks {task_count}', text)
        f.seek(0)
        f.write(text)
        f.truncate()


def count_functions(dir):
    task_cnt = tasks_created('./src')
    write_task_cnt(task_cnt)
    return task_cnt


def main():
    cnt = count_functions('./src')
    print(f'updated max task count to {cnt}')


if __name__ == '__main__' or __name__ == 'SCons.Script':
    main()