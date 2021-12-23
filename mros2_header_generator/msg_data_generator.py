import os
from msg_def_generator import msgDefGenerator

# generate message data is mainly about the name, definition of the type 

def msgDataGenerator(line, dependingMsgs):
    if os.path.isfile(line):
        with open(line, 'r') as m_f:
            arr = m_f.readlines()
            msgDef = []
            for m_line in arr:
                msgDef.append(msgDefGenerator(m_line, dependingMsgs))

        lineArr = line.strip().split('/')
        lineArr[2] = lineArr[2].rstrip('.msg')
        return {
            'name': lineArr[2],
            'pkg': lineArr[0],
            'NAME': lineArr[2].upper(),
            'PKG': lineArr[0].upper(),
            'def': msgDef,
        }
    else:
        raise Exception('msg header file "' + line + '" not found.')