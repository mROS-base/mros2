# generate message type header file for mROS2

import os
import json
import sys
import re
from jinja2 import Environment, FileSystemLoader
from msg_data_generator import msgDataGenerator

msgs = []
deps = []
dependingFileNames = []
dependingMsgs = {}

arg = sys.argv
if(len(arg) == 1):
    raise Exception('Error: json file is not specified')
jsonFileName = arg[1]

appDir = '../../mros2' # for asp_app
msgIncludePath = appDir + "/" + "mros2_msgs" + "/"
fileDir = os.getcwd()

def toSnakeCase(string):
    return re.sub("(.[A-Z])",lambda x:x.group(1)[0] + "_" +x.group(1)[1],string).lower()

def main():
    #if not(os.path.isdir(msgIncludePath)):
        #os.mkdir(msgIncludePath)
    if not(os.path.isfile(fileDir + "/" + jsonFileName)):
        raise Exception('specified json file (' + fileDir + "/" + jsonFileName + ') not found')

    with open(fileDir + "/" + jsonFileName, 'r') as f:
        jsonData = json.load(f)
        
        for dep in jsonData['dependingMsgs']:
            dep = toSnakeCase(dep.strip()[:-4]) + '.hpp'
            depArr = dep.split('/')
            depArr[-1] = depArr[-1][1:]
            dependingFileNames.append('/'.join(depArr))
            
        for dep in jsonData['dependingMsgs']:
            depArr = dep.strip().split('/')
            depArr[2] = depArr[2].rstrip('.msg')
            dependingMsgs[depArr[2]] = '::'.join(depArr)
            
        for line in jsonData['includingMsgs']:
            line = line.strip()
            msgs.append(msgDataGenerator(line, dependingMsgs))  # generate message data of the custom type

    # generate header file for mros2
    for msg in msgs:
        env = Environment(loader=FileSystemLoader(appDir + '/mros2_header_generator'))
        template = env.get_template('header_template.tpl')
        datatext = template.render({"msg": msg, "dependingFileNames": dependingFileNames})
        print(datatext)
        msgPkgPath = msgIncludePath + msg['pkg']
        if not(os.path.isdir(msgPkgPath)):
            os.mkdir(msgPkgPath)
            os.mkdir(msgPkgPath + "/msg")
        with open(os.path.join(msgPkgPath, "msg", toSnakeCase(msg['name']) + ".hpp"), "wb") as f:
            f.write(datatext.encode('utf-8'))

if __name__ == "__main__":
    main()