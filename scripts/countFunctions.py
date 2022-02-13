import os
import re
from enum import Enum

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()


class Mode(Enum):
    build=0
    test=1

def read_files(dir) -> list[str]:
    file_content = []
    for r, d, f in os.walk(dir):
        for file in f:
            if file.endswith('.c') or file.endswith('.cpp'):
                with open(f'{r}/{file}') as fp:
                    lines = fp.read()
                    file_content.append(lines)

    return file_content


def parse_build_file(file_content) -> int:
    pattern = r'\.addFunction(Static)?\(.*\);'
    match = re.compile(pattern)
    matches = match.findall(file_content)
    return len(matches)


def parse_test_file(file_content) -> int:
    # TODO: only return test case with most function calls
    return parse_build_file(file_content)


def tasks_in_file(file_content: str, mode:Mode) -> int:
    cnt = 0

    if mode == mode.build:
        cnt = parse_build_file(file_content)
    elif mode == mode.test:
        cnt = parse_test_file(file_content)
    else:
        print(f'ERR: unknown mode {mode}')
        exit(-1)

    return cnt


def tasks_created(files: list[str], mode:Mode) -> int:
    cnt_lst = []
    
    for content in files:
        cnt_lst.append(tasks_in_file(content, mode))
        
    if mode==mode.build:
        # build mode requires to hold all functions
        return sum(cnt_lst)
    elif mode==mode.test:
        # unit tests only require the highest used function count (not total)
        return max(cnt_lst)
    else:
        print(f'ERROR: unknown build mode {mode}')
        exit(-1)


def write_task_cnt(task_count):
    
    with open('ECU_Defines/StallardOSconfig.h', 'r+') as f:
        text = f.read()
        text = re.sub(r'#define countTasks \d+', f'#define countTasks {task_count}', text)
        f.seek(0)
        f.write(text)
        f.truncate()


def count_functions(dir, mode:Mode):
    files = read_files(dir)
    task_cnt = tasks_created(files, mode)
    write_task_cnt(task_cnt)
    return task_cnt


def main():

    if 'PIOTEST_RUNNING_NAME' in env:
        task_dir = env['PROJECT_TEST_DIR']
        mode=Mode.test
    else:
        task_dir = env['PROJECT_SRC_DIR']
        mode=Mode.build
    
    cnt = count_functions(env.subst(task_dir), mode=mode)
    print(f'updated max task count to {cnt}')


if __name__ == '__main__' or __name__ == 'SCons.Script':
    main()