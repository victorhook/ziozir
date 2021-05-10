import os
import re

opcode_path = os.path.join(os.path.dirname(__file__), '../src', 'cpu.h')
re_start = 'typedef enum {'
re_end = '} Operation;'
re_opcodes = re.compile(f'{re_start}.*?{re_end}', flags=re.DOTALL)


def get_opcodes(input: str) -> list:
    opcodes = re_opcodes.findall(data)[0]
    opcodes = re.sub(',\s*\/\/.*', '', opcodes)
    opcodes = re.sub(' ', '', opcodes)
    opcodes = opcodes.splitlines()
    opcodes = filter(lambda l: l.startswith('OP'), opcodes)
    opcodes = list(map(lambda code: code[3:], opcodes))
    return opcodes


if __name__ == '__main__':
    with open(opcode_path) as f:
        data = f.read()

    opcodes = get_opcodes(data)
    for index, code in enumerate(opcodes):
        print(f'{code} = {index}')

    for index, code in enumerate(opcodes):
        print(f'"{code}": {index},')

