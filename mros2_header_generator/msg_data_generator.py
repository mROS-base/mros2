import os
from msg_def_generator import msgDefGenerator

# generate message data is mainly about the name, definition of the type 

def msgDataGenerator(line):
    dependingFileNames = []
    if os.path.isfile(line):
        with open(line, 'r') as m_f:
            arr = m_f.readlines()
            msgDef = []
            for m_line in arr:
                stripped_line = m_line.strip()
                if stripped_line == "": continue
                msgDef.append(msgDefGenerator(stripped_line, dependingFileNames))

        lineArr = line.strip().split('/')
        lineArr[2] = os.path.splitext(lineArr[2])[0]
        return {
            'name': lineArr[2],
            'pkg': lineArr[0],
            'NAME': lineArr[2].upper(),
            'PKG': lineArr[0].upper(),
            'def': msgDef,
            'dependingFileNames': dependingFileNames,
        }
    else:
        raise Exception('msg header file "' + line + '" not found.')
