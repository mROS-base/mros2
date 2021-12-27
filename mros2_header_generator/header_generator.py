# generate message type header file for mROS2

import os
import json
import sys
import re
from jinja2 import Environment, FileSystemLoader
from msg_data_generator import msgDataGenerator

arg = sys.argv
mros2Dir = arg[1]
appDir = arg[2]

def toSnakeCase(string):
    return re.sub("(.[A-Z])",lambda x:x.group(1)[0] + "_" +x.group(1)[1],string).lower()

def main():
    # load msg settings & prepare information for .tpl file
    with open(appDir + "/" + "msg_settings.json", 'r') as f:
        jsonData = json.load(f)
        for msgLst in jsonData['includingMsgs']:
            dependingFileNames = []
            dependingDict = {}
            dependingLst = []
            generatingMsg = msgLst[0]
            if len(msgLst) > 1:
                dependingLst = msgLst[1:]
                
            for dep in dependingLst:
                dep = toSnakeCase(dep.strip()[:-4]) + '.hpp'
                depArr = dep.split('/')
                if depArr[-1][0] == '_':
                    depArr[-1] = depArr[-1][1:]
                    dependingFileNames.append('/'.join(depArr))
            
            for dep in dependingLst:
                depArr = dep.strip().split('/')
                depArr[2] = depArr[2].rstrip('.msg')
                dependingDict[depArr[2]] = '::'.join(depArr)
                
            generatingMsg = generatingMsg.strip()
            msgs.append(msgDataGenerator(generatingMsg, appDir, dependingDict, dependingFileNames))

    # generate header file for mros2
    for msg in msgs:
        env = Environment(loader=FileSystemLoader(mros2Dir + '/mros2_header_generator'))
        template = env.get_template('header_template.tpl')
        datatext = template.render({ "msg": msg })
        
        msgPkgPath = "mros2_msgs" + "/" + msg['pkg'] 
        
        if not(os.path.isdir("mros2_msgs")):
            os.mkdir("mros2_msgs")  
        if not(os.path.isdir(msgPkgPath)):
            os.mkdir(msgPkgPath)
        if not(os.path.isdir(msgPkgPath + "/msg")):
            os.mkdir(msgPkgPath + "/msg")

        with open(os.path.join(msgPkgPath, "msg", toSnakeCase(msg['name']) + ".hpp"), "wb") as f:
            f.write(datatext.encode('utf-8'))

if __name__ == "__main__":
    msgs = []
    main()