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
    "bool": "uint8_t",
    "byte": "uint8_t",
}

# size of each type
msgSizes = {
    "string": 1, "bool": 1,
    "int8": 1, "uint8": 1,
    "int16": 2, "uint16": 2,
    "int32": 4, "uint32": 4,
    "int64": 8, "uint64": 8,
    "float32": 4, "float64": 8
}

# generate detail data of type definition


def msgDefGenerator(msgDefStr, dependingMsgs):

    # split the type def and name of the type ('string name' -> ['string', 'name'])
    msgDefArr = msgDefStr.split(' ')
    print(msgDefArr)
    msgType = msgDefArr[0]  # each type (ex. string, int8, float32, ...)
    msgName = msgDefArr[1]  # name of each type (ex. name, height, weight, ...)
    isArray = False

    # when array (ex. int8[], float32[], ...)msgType = msgType[:-2]
    if msgType[-2:] == "[]":
        isArray = True
        msgType = msgType[:-2]

    if msgType in msgCppTypes:  # when primitive type of ROS2
        return {
            'rosType': msgType,
            'cppType': msgCppTypes[msgType],
            'typeName': msgName,
            'size': msgSizes[msgType],
            'isArray': isArray,
            'isCustomType': False
        }
        
    elif msgType in dependingMsgs:
        return {
            'rosType': dependingMsgs[msgType],
            'cppType': dependingMsgs[msgType],
            'typeName': msgName,
            'size': 0,
            'isArray': isArray,
            'isCustomType': True
        }    
        
    else:
        print('type is not found')