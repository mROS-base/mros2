# generate message type header file for mROS2

import os
import json
import sys
from jinja2 import Environment, FileSystemLoader
from msg_data_generator import msgDataGenerator
#from mros2_compute_message_type_size import computeMsgTypeSize

# standard types for ROS2
stdMsgs = {
    "std_msgs/msg/int8.hpp": 1,
    "std_msgs/msg/uint8.hpp": 2,
    "std_msgs/msg/int16.hpp": 3,
    "std_msgs/msg/uint16.hpp": 4,
    "std_msgs/msg/int32.hpp": 5,
    "std_msgs/msg/uint32.hpp": 6,
    "std_msgs/msg/int64.hpp": 7,
    "std_msgs/msg/uint64.hpp": 8,
    "std_msgs/msg/float32.hpp": 9,
    "std_msgs/msg/float64.hpp": 10,
    "std_msgs/msg/string.hpp": 11,
    "std_msgs/msg/bool.hpp": 12,
    "std_msgs/msg/byte.hpp": 13,
}

msgs = []
depMsgs = []
includedStdMsgs = []

arg = sys.argv
if(len(arg) == 1):
    raise Exception('Error: json file is not specified')
jsonFileName = arg[1]

appDir = '../../mros2'
msgIncludePath = appDir + "/" + "mros2_msgs" + "/"
fileDir = os.getcwd()

def main():
    #if not(os.path.isdir(msgIncludePath)):
        #os.mkdir(msgIncludePath)
    if not(os.path.isfile(fileDir + "/" + jsonFileName)):
        raise Exception('specified json file (' + fileDir + "/" + jsonFileName + ') not found')

    with open(fileDir + "/" + jsonFileName, 'r') as f:
        jsonData = json.load(f)
        for line in jsonData['includingMsgs']:
            line = line.strip()
            print(line)
            if line in stdMsgs:  # when standard type of ROS2
                includedStdMsgs.append( {'pkgName': line, 'id': stdMsgs[line]} )
            else:  # when custom type
                msgs.append(msgDataGenerator(line))  # generate message data of the custom type

    #os.chdir(fileDir)

    # generate header file for mros2
    for msg in msgs:
        env = Environment(loader=FileSystemLoader('.'))
        template = env.get_template('mros2_msg_header_template.tpl')
        datatext = template.render({"msg": msg})
        msgPkgPath = msgIncludePath + msg['pkg']
        if not(os.path.isdir(msgPkgPath)):
            os.mkdir(msgPkgPath)
        with open(os.path.join(msgPkgPath, "msg", msg['name'] + ".hpp"), "wb") as f:
            f.write(datatext)

if __name__ == "__main__":
    main()
