import os
import sys
import re
import argparse
from os import path
from jinja2 import Environment, FileSystemLoader

includeFiles = []
pubMsgTypes = []
subMsgTypes = []

def toSnakeCase(string):
    return re.sub("(.[A-Z])",lambda x:x.group(1)[0] + "_" +x.group(1)[1],string).lower()

def main():
    print('Generate template.hpp from mros2 app code file.')

    parser = argparse.ArgumentParser(description='Generate template.hpp from mros2 app code file.')
    parser.add_argument('--app', default='echoreply_string',
                    help='application name (default: \'echoreply_string\')')
    parser.add_argument('--file', nargs='*', type=str, default=['app.cpp'],
                    help='filename(s) of mros2 app code (default: \'app.cpp\')')

    args = parser.parse_args()
    app = args.app
    file = args.file

    for f in file:
        print('  Analyzing {}/{} file to generate...'.format(app, f))
        with open(app + "/" + f, 'r') as m_f:
            arr = m_f.readlines()
            for m_line in arr:
                if "create_publisher" in m_line:
                    line = m_line.strip()
                    left_idx = line.index('<')
                    right_idx =line.index('>')
                    pubMsgTypes.append(line[left_idx+1:right_idx])
                    
                if "create_subscription" in m_line:
                    line = m_line.strip()
                    left_idx = line.index('<')
                    right_idx =line.index('>')
                    subMsgTypes.append(line[left_idx+1:right_idx])
                    
            pubSubUnion = list(set(pubMsgTypes + subMsgTypes))
            for msgType in pubSubUnion:
                typeArr = msgType.split('::')
                typeArr[2] = toSnakeCase(typeArr[2])
                includeFile = '/'.join(typeArr)
                includeFile = '#include "' + includeFile + '.hpp"'
                includeFiles.append(includeFile)
                
    env = Environment(loader=FileSystemLoader(path.dirname(__file__)))
    template = env.get_template('templates.tpl')
    datatext = template.render({ "includeFiles":includeFiles, "pubMsgTypes":pubMsgTypes, "subMsgTypes":subMsgTypes  })
    with open(os.path.join(app+"/templates.hpp"), "wb") as f:
        f.write(datatext.encode('utf-8'))

    print('Generate {}/template.hpp done.'.format(app))

if __name__ == "__main__":
    main()
