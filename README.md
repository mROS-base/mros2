# mros2

mROS 2 (formly `mros2`) realizes a agent-less and lightweight runtime environment compatible with ROS 2 for embedded devices.
This repository contains the communication layer of mROS 2.

mROS 2 mainly offers pub/sub APIs compatible with [rclcpp](https://docs.ros2.org/dashing/api/rclcpp/index.html) for embedded devices. 
[ROS 2](https://docs.ros.org/en/dashing/) is a de-fact platform for the robot system development, and provides pub/sub communication infrastructure with the DDS/RTPS protocol.

## Features

- **Agent-less**: a node on mROS 2 autonomously discovers communication nodes on the host with the feature of [embeddedRTPS](https://github.com/mROS-base/embeddedRTPS). It means no agent/bridge is required for pub/sub communication from the embedded devices.
- **Lightweight**: mROS 2 APIs are implemented by C++ to be operated on the embedded devices. All software stacks are also implemented only in C/C++.
- **Real-time**: mROS 2 employs the real-time kernel (e.g., [TOPPERS kernel](https://www.toppers.jp/en/project.html)) as the runtime platform in order to enhance the real-time capability.

## Supported platform

Since this repository itself only maintains the communication layer of mROS 2, we also publish the implementation on the embedded board using this layer and the embedded kernel.
Please see each repository to learn how to use it.


| name | board | kernel |
|:---|:---|:---|
| [mros2-asp3-f767zi](https://github.com/mROS-base/mros2-asp3-f767zi) |[STM32 NUCLEO-F767ZI](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html) | [TOPPERS/ASP3](https://www.toppers.jp/en/project.html) |

Please let us know if you have a request for a support of board/kernel, or if you could implement this layer on another platform.

## License

The source code of this repository itself is published under [Apache License 2.0](https://github.com/mROS-base/mros2/blob/main/LICENSE).  
Please note that this repository contains [embeddedRTPS and its third party libraries](https://github.com/mROS-base/embeddedRTPS#third-party-libraries) as the submodule, and also check their Licenses.
