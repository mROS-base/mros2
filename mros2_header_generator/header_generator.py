# generate message type header file for mROS2

import os
import sys
import re
from jinja2 import Environment, FileSystemLoader

arg = sys.argv
msgFile = arg[1]

def toCamelCase(string):
    return ''.join(x.capitalize() for x in string.split('_'))

def toSnakeCase(string):
    return re.sub("(.[A-Z])",lambda x:x.group(1)[0] + "_" +x.group(1)[1],string).lower()

def main():
    from msg_data_generator import msgDataGenerator
    # load msg settings & prepare information for .tpl file
    msgs.append(msgDataGenerator(msgFile))

    # generate header file for mros2
    for msg in msgs:
        env = Environment(loader=FileSystemLoader('../mros2/mros2_header_generator'))
        template = env.get_template('header_template.tpl')
        datatext = template.render({ "msg": msg })
        
        msgPkgPath = "custom_msgs" + "/" + msg['pkg'] 
        
        if not(os.path.isdir("custom_msgs")):
            os.mkdir("custom_msgs")  
        if not(os.path.isdir(msgPkgPath)):
            os.mkdir(msgPkgPath)
        if not(os.path.isdir(msgPkgPath + "/msg")):
            os.mkdir(msgPkgPath + "/msg")

        with open(os.path.join(msgPkgPath, "msg", toSnakeCase(msg['name']) + ".hpp"), "wb") as f:
            f.write(datatext.encode('utf-8'))
            
def genDepMsgHeader(genMsg):
    from msg_data_generator import msgDataGenerator
    msgs=[]
    msgs.append(msgDataGenerator(genMsg.strip()))
    for msg in msgs:
        env = Environment(loader=FileSystemLoader('../mros2/mros2_header_generator'))
        template = env.get_template('header_template.tpl')
        datatext = template.render({ "msg": msg })
        
        msgPkgPath = "custom_msgs" + "/" + msg['pkg'] 
        
        if not(os.path.isdir("custom_msgs")):
            os.mkdir("custom_msgs")  
        if not(os.path.isdir(msgPkgPath)):
            os.mkdir(msgPkgPath)
        if not(os.path.isdir(msgPkgPath + "/msg")):
            os.mkdir(msgPkgPath + "/msg")

        with open(os.path.join(msgPkgPath, "msg", toSnakeCase(msg['name']) + ".hpp"), "wb") as f:
            f.write(datatext.encode('utf-8'))

if __name__ == "__main__":
    msgs = []
    main()