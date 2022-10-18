# mros2

`mros2` (formally mROS 2) realizes an agent-less and lightweight runtime environment compatible with ROS 2 for embedded devices.
It consists of basic APIs for pub/sub communication, RTPS protocol, UDP/IP stack, and real-time kernel.
Embedded nodes can now communicate directly with native ROS 2 nodes via topic!

This repository maintains the communication layer of mROS 2, that mainly offers pub/sub APIs compatible with [rclcpp](https://docs.ros2.org/dashing/api/rclcpp/index.html) for embedded devices. 
[ROS 2](https://docs.ros.org/en/dashing/) is a de-fact platform for the robot system development, and provides pub/sub communication infrastructure with the DDS/RTPS protocol.

## Features

- **Agent-less**: a node on mROS 2 autonomously discovers communication nodes on the host with the feature of [embeddedRTPS](https://github.com/mROS-base/embeddedRTPS). It means no agent/bridge is required for pub/sub communication from the embedded devices.
  - mros2 currently uses [embeddedRTPS @ 1410a87](https://github.com/mROS-base/embeddedRTPS/tree/1410a8776660244249a84031ffa78c9bdaa45e19) as it is.
- **Lightweight**: mROS 2 APIs are implemented by C++ to be operated on the embedded devices. All software stacks are also implemented only in C/C++.
- **Real-time**: mROS 2 employs the real-time kernel (e.g., [TOPPERS kernel](https://www.toppers.jp/en/project.html), [Mbed OS](https://os.mbed.com/mbed-os/)) as the runtime platform in order to enhance the real-time capability.

## Functionalities and limitations

Here are functionalities that mROS 2 offers for you, and current limitations (a.k.a call for your contibutions!).

- Pub/Sub communication via Topic is supported
  - [Built-in-types](https://docs.ros.org/en/foxy/Concepts/About-ROS-Interfaces.html#field-types) except for `wstring` (UTF-16)
    - Please check [mros2-asp3-f767zi#exapmle-applications](https://github.com/mROS-base/mros2-asp3-f767zi#example-applications) for more details.
    - `array` types are not supported
  - Some custom message types (e.g., Twist, Pose)
    - We think variable-length types and types exceeding one packet cannot be handled, probably due to the limitation of lwIP.
- Service, Actions, and Parameters are not supported
  - Please let us know if you want to use them as soon as possible. We can consider of raising the priority of these supports.

## Supported platform

Since this repository itself only maintains the communication layer of mROS 2, we also publish the implementation on the embedded board using this layer and the embedded kernel.
Please see each repository to learn how to use it.


| name | kernel | board | support status |
|:---|:---|:---|:---|
| [mros2-asp3-f767zi](https://github.com/mROS-base/mros2-asp3-f767zi) | [TOPPERS/ASP3](https://www.toppers.jp/en/project.html) | [STM32 NUCLEO-F767ZI](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html) | currently supported up to v0.3.2 (see [status](https://github.com/mROS-base/mros2-asp3-f767zi/issues/74)) |
| [mros2-mbed](https://github.com/mROS-base/mros2-mbed) | [Mbed OS 6](https://github.com/ARMmbed/mbed-os) | Mbed enabled boards having an Ethernet port (See [detail](https://github.com/mROS-base/mros2-mbed#supported-environment)) | well maintained and easy to try |
| [mros2-posix](https://github.com/mROS-base/mros2-posix) | POSIX (pthread) | any machine that runs Linux | partly maintained |

Please let us know if you have a request for a support of board/kernel, or if you could implement this layer on another platform.

## License

The source code of this repository itself is published under [Apache License 2.0](https://github.com/mROS-base/mros2/blob/main/LICENSE).  
Please note that this repository contains [embeddedRTPS and its third party libraries](https://github.com/mROS-base/embeddedRTPS#third-party-libraries) as the submodule, and also check their Licenses.
