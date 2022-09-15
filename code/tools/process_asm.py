import sys

next_label = 0
def label():
    global next_label
    next_label += 1
    return f'$__{next_label}'

def log_calls(lines):
    result = []
    for line in lines:
        if line[0] == 'proc':
            proc_name = line[1]

            # make sure there's room for at least one arg
            #if line[3] == '0':
            line[3] = str(int(line[3]) + 4)

            result.extend([
                ['lit'],
                ['LABELV', f'__{proc_name}_name'],
            ])
            result.extend([['byte', '1', str(ord(char))] for char in proc_name + '\n\0'])
            result.extend([
                ['code'],
                line,
                ['ADDRGP4', f'__{proc_name}_name'],
                ['ARGP4'],
                ['CNSTI4', '-1'],
                ['CALLP4'],
                ['pop'],
            ])
        else:
            result.append(line)
    return result

def process_setjmp(lines):
    result = []
    setjmp_labels = []
    handler_label = None
    return_label = None

    i = 0
    while i < len(lines):
        if lines[i][0] == 'proc':
            handler_label = label()
            return_label = label()
            setjmp_labels.append(return_label)
            result.append(lines[i])
            i += 1

        elif lines[i][0] == 'endproc':
            result.extend([
                ['LABELV',  handler_label],
                ['ADDRGP4', setjmp_labels[-1]],
                ['JUMPV'],

                ['LABELV', return_label],
                lines[i],
            ])
            i += 1

        elif lines[i][0].startswith('CALL'):
            result.extend([
                lines[i], lines[i+1],
                ['ADDRGP4', '__longjmp_target'],
                ['INDIRI4'],
                ['CNSTI4', '0'],
                ['NEI4', handler_label],
            ])
            i += 2

        elif (
            lines[i][0].startswith('ADDR') and
            lines[i+1][0].startswith('ARGP4') and
            lines[i+2][0] == 'ADDRLP4' and
            lines[i+3][0] == 'ADDRGP4' and
            lines[i+4][0].startswith('CALL') and
            lines[i+5][0].startswith('ASGN') and
            lines[i+3][1] == '__setjmp'
        ):
            l = label()
            result.append(['LABELV', l])
            result.extend(lines[i:i+6])
            result.extend([
                ['ADDRGP4', '__longjmp_skip'],
                ['INDIRI4'],
                ['CNSTI4', '0'],
                ['NEI4', setjmp_labels[-1]],
            ])
            setjmp_labels.append(l)
            i += 6
        
        else:
            result.append(lines[i])
            i += 1

    return result

if __name__ == '__main__':
    with open(sys.argv[1]) as f:
        lines = [line.split() for line in f.readlines()]
    lines = process_setjmp(lines)
    # lines = log_calls(lines)
    with open(sys.argv[1], 'w') as f:
        f.write('\n'.join(' '.join(word for word in line) for line in lines))
