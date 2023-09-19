import os
import glob
import re
import argparse
import filecmp
import shutil
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
    parser.add_argument('--outdir', default='.',
                    help='directry name to output template.hpp (default: \'.\' (current dir))')
    parser.add_argument('--indir', nargs='*', type=str, required=True,
                    help='input dir(s) that contains mros2 app code (required)')

    args = parser.parse_args()
    indir = args.indir
    outdir = args.outdir
    file = []
    for id in indir:
        file = file + glob.glob(os.path.join(id, "*.cpp"))

    for f in file:
        print('  Analyzing \'{}\' to generate...'.format(f))
        with open(f, 'r') as m_f:
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

    outfile_path = os.path.join(outdir, "templates.hpp")
    outtemp_path = os.path.join(outdir, "templates.hpp.tmp")
    if (not os.path.isfile(outfile_path)):
        with open(outfile_path, "wb") as f:
            f.write(datatext.encode('utf-8'))
    with open(outtemp_path, "wb") as f:
        f.write(datatext.encode('utf-8'))
    if filecmp.cmp(outtemp_path, outfile_path, shallow=True):
        os.remove(outtemp_path)
    else:
        shutil.move(outtemp_path, outfile_path)

    print('Generate {}/template.hpp done.'.format(outdir))

if __name__ == "__main__":
    main()
