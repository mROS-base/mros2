import os
import re
from header_generator import genDepMsgHeader

# mapping between ros2Type to cppType
msgCppTypes = {
    "int8": "int8_t",
    "uint8": "uint8_t",
    "int16": "int16_t",
    "uint16": "uint16_t",
    "int32": "int32_t",
    "uint32": "uint32_t",
    "int64": "int64_t",
    "uint64": "uint64_t",
    "float32": "float",
    "float64": "double",
    "string": "string",
    "header": "header",
    "bool": "uint8_t",
    "byte": "uint8_t"
}

# size of each type
msgSizes = {
    "string": -1, "bool": 1,
    "int8": 1, "uint8": 1,
    "int16": 2, "uint16": 2,
    "int32": 4, "uint32": 4,
    "int64": 8, "uint64": 8,
    "float32": 4, "float64": 8,
    "header": -1
}

def toSnakeCase(string):
    return re.sub("(.[A-Z])",lambda x:x.group(1)[0] + "_" +x.group(1)[1],string).lower()

# generate detail data of type definition

def msgDefGenerator(msgDefStr, dependingFileNames):

    # split the type def and name of the type ('string name' -> ['string', 'name'])
    msgDefArr = msgDefStr.split(' ')
    msgType = msgDefArr[0]  # each type (ex. string, int8, float32, ...)
    msgName = msgDefArr[1]  # name of each type (ex. name, height, weight, ...)
    isArray = False
    boundedArray = 0

    # when array (ex. int8[], float32[], float64[36], ...)
    if msgType[-1] == "]":
        isArray = True
        right_idx = msgType.index("]")
        left_idx = msgType.index("[")
        if right_idx - left_idx > 1:
            boundedArray = int(msgType[left_idx+1:right_idx])
            msgType = msgType[:left_idx]
        else:
            msgType = msgType[:left_idx]

    if msgType in msgCppTypes:  # when standard type of ROS2
        return {
            'rosType': msgType,
            'cppType': msgCppTypes[msgType],
            'typeName': msgName,
            'size': msgSizes[msgType],
            'isArray': isArray,
            'boundedArray': boundedArray,
            'isCustomType': False
        }
        
    else:
        if os.path.isfile("custom_msgs/" + msgType + ".msg"): # when custom type
            dependingFileName = toSnakeCase(msgType) + ".hpp"
            depFileArr = dependingFileName.split("/")
            if depFileArr[2][0] == "_":
                depFileArr[2] = depFileArr[2][1:]
            dependingFileName = "/".join(depFileArr)
            dependingFileNames.append(dependingFileName)
            genDepMsgHeader(msgType+".msg")
            return {
                'rosType': msgType.replace("/","::"),
                'cppType': msgType.replace("/","::"),
                'typeName': msgName,
                'size': 0,
                'isArray': isArray,
                'boundedArray': boundedArray,
                'isCustomType': True
            }      
        else:
            print(msgType+' is not found')