# mros2

`mros2` (formally mROS 2) realizes an agent-less and lightweight runtime environment compatible with ROS 2 for embedded devices.
It consists of basic APIs for pub/sub communication, RTPS protocol, UDP/IP stack, and real-time kernel.
Embedded nodes can now communicate directly with native ROS 2 nodes via topic!

This repository maintains the communication layer of mROS 2, that mainly offers pub/sub APIs compatible with [rclcpp](https://docs.ros2.org/dashing/api/rclcpp/index.html) for embedded devices. 
[ROS 2](https://docs.ros.org/en/dashing/) is a de-fact platform for the robot system development and provides pub/sub communication infrastructure with the DDS/RTPS protocol.

## Features

- **Agent-less**: A node on mROS 2 autonomously discovers communication nodes on the host. No agent/bridge is required for pub/sub communication from the embedded devices.
  - mros2 adopts [embeddedRTPS](https://github.com/mROS-base/embeddedRTPS) with some modifications. 
- **Lightweight**: mROS 2 APIs are implemented by C++ to be operated on the embedded devices. All software stacks are also implemented only in C/C++.
- **Real-time**: mROS 2 uses the real-time kernel (e.g., [TOPPERS kernel](https://www.toppers.jp/en/project.html), [Mbed OS](https://os.mbed.com/mbed-os/)) as the runtime platform in order to enhance the real-time capability.

## Functionalities and limitations

Here are the functionalities that mROS 2 offers for you, and current limitations (a.k.a call for your contributions!).

- Pub/Sub communication via Topic is supported
  - [Built-in-types](https://docs.ros.org/en/foxy/Concepts/About-ROS-Interfaces.html#field-types)
    - `wstring` (UTF-16) is not provided due to its difficulty in verification, but it is unlikely to be used.
    - `array` types are not supported
  - Some custom message types (e.g., Twist, Pose)
    - Please check [#generating-header-files-for-custom-msgtypes](https://github.com/mROS-base/mros2#generating-header-files-for-custom-msgtypes) for more details.
    - Fragmented message types (that exceed one packet) are experimentally supported. See [PR#36](https://github.com/mROS-base/mros2/pull/36) for more details.
    - We think variable-length types cannot be handled, probably due to the limitation of lwIP.
- Service, Actions, and Parameters are not supported
  - Please let us know if you want to use them as soon as possible. We can consider raising the priority of these supports.
- mros2 node name cannot be observed from ROS 2 host (see [Issue#44](https://github.com/mROS-base/mros2/issues/44))

## Supported platform

Since this repository itself only maintains the communication layer of mROS 2, we also publish the implementation on the embedded board using this layer and the embedded kernel.
Please see each repository to learn how to use it.


| name | kernel | board | support status |
|:---|:---|:---|:---|
| [mros2-asp3-f767zi](https://github.com/mROS-base/mros2-asp3-f767zi) | [TOPPERS/ASP3](https://www.toppers.jp/en/project.html) | [STM32 NUCLEO-F767ZI](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html) | currently supported up to v0.3.2 (see [status](https://github.com/mROS-base/mros2-asp3-f767zi/issues/74)) |
| [mros2-mbed](https://github.com/mROS-base/mros2-mbed) | [Mbed OS 6](https://github.com/ARMmbed/mbed-os) | Mbed enabled boards having an Ethernet port (See [detail](https://github.com/mROS-base/mros2-mbed#supported-environment)) | well maintained and easy to try |
| [mros2-esp32](https://github.com/mROS-base/mros2-esp32) | [ESP-IDF FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html) | ESP32 boards with 2.4 GHz Wi-Fi (See [detail](https://github.com/mROS-base/mros2-esp32#supported-environment)) | well maintained |
| [mros2-posix](https://github.com/mROS-base/mros2-posix) | POSIX (pthread) | any machine that runs Linux | partly maintained |

Please let us know if you have a request for support for other boards/kernels, or if you could implement this layer on other platforms.

## Generating header files for custom MsgTypes

You can use almost any [built-in-types in ROS 2](https://docs.ros.org/en/rolling/Concepts/About-ROS-Interfaces.html#field-types) on the embedded device.
Not that `array` types are not supported yet.

You can also use following message types that are commonly used. We have prepared and located them in `mros2_msgs/`.

- [geometry_msgs/msg/Twist](https://docs.ros2.org/latest/api/geometry_msgs/msg/Twist.html)
- [geometry_msgs/msg/Vector3](https://docs.ros2.org/latest/api/geometry_msgs/msg/Vector3.html)
- [geometry_msgs/msg/Pose](https://docs.ros2.org/latest/api/geometry_msgs/msg/Pose.html)
- [geometry_msgs/msg/Point](https://docs.ros2.org/latest/api/geometry_msgs/msg/Point.html)
- [geometry_msgs/msg/Quaternion](https://docs.ros2.org/latest/api/geometry_msgs/msg/Quaternion.html)
- [sensor_msgs/msg/Image](https://docs.ros2.org/latest/api/sensor_msgs/msg/Image.html) (experimental)

In additon, you can define a customized message type in the same way as in ROS 2, and use its header file for your application.  
The rest of this section describes how to generate header files for your own MsgTypes. 
The example assumes the location as `<this_repo_dir>/mros2_msgs/` and target as `geometry_msgs::msg::Twist`.
The location is arbitrary, but be careful with the paths of the Python script and the .msg file.

### Prepare .msg files

`.msg` files are simple text files that describe the fields of a ROS message (see [About ROS 2 interface](https://docs.ros.org/en/rolling/Concepts/About-ROS-Interfaces.html)). In mros2, they are used to generate header files for messages in embedded applications.

Prepare `Twist.msg` file and make sure it is in `<this_repo_dir>/mros2_msgs/geometry_msgs/msg/`.

```
$ pwd
<this_repo_dir>/mros2_msgs

$ cat geometry_msgs/msg/Twist.msg
geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
```

In this example, `Twist` has a nested structure with `Vector3` as a child element. So you also need to prepare its file.

```
$ cat geometry_msgs/msg/Vector3.msg
float64 x
float64 y
float64 z
```

### Generate header files

To generate header files for `Twist` and `Vector3`, run the following command in `<this_repo_dir>/mros2_msgs/` (again, be careful about the paths!).

```
$ cd <this_repo_dir>/mros2_msgs
$ python3 ../mros2_header_generator/header_generator.py geometry_msgs/msg/Twist.msg
```

Make sure header files for custom MsgType are generated in `geometry_msgs/`.

```
$ ls -R geometry_msgs/
geometry_msgs:
msg

geometry_msgs/msg:
twist.hpp  vector3.hpp  Twist.msg  Vector3.msg
```

You can now use them in your applicaton like this.

```
#include "mros2.hpp"
#include "mros2-platform.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"

int main(int argc, char * argv[])
{
<snip.>
  pub = node.create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
<snip.>
```

When you generated your own header files at an arbitrary location, you need to add its path as an include path for build (e.g., CMakeLists.txt).

If you generated new header files at `<this_repo_dir>/mros2_msgs/`, we are very welcome to your PR!!

## License

The source code of this repository itself is published under [Apache License 2.0](https://github.com/mROS-base/mros2/blob/main/LICENSE).  
Please note that this repository contains [embeddedRTPS and its third-party libraries](https://github.com/mROS-base/embeddedRTPS#third-party-libraries) as the submodule, and also check their Licenses.

## Publications/References

### English

- [ROSCon 2022](https://roscon.ros.org/2022/): ``mROS 2: yet another runtime environment onto embedded devices'' [movie](https://vimeo.com/showcase/9954564/video/767150435) [slide](https://speakerdeck.com/takasehideki/mros-2-yet-another-runtime-environment-onto-embedded-devices)

### Japanese ;(

- Paper
  - 細合，高瀬：[mros2-esp32: ロボットソフトウェア軽量実行環境の無線通信対応の検討](https://ipsj.ixsq.nii.ac.jp/ej/?action=pages_view_main&active_action=repository_view_main_item_detail&item_id=226824&item_no=1&page_id=13&block_id=8)，情報処理学会研究報告 組込みシステム，2023年7月．
  - 柿本，松原，高瀬：[クラウド連携を対象としたアーキテクチャ中立なROSランタイムの検討](https://ipsj.ixsq.nii.ac.jp/ej/?action=pages_view_main&active_action=repository_view_main_item_detail&item_id=225558&item_no=1&page_id=13&block_id=8)，情報処理学会研究報告 組込みシステム，2023年3月．
  - 細合，田中，高瀬：[ロボットソフトウェア軽量実行環境mROS 2のPOSIX対応の検討](https://ipsj.ixsq.nii.ac.jp/ej/?action=pages_view_main&active_action=repository_view_main_item_detail&item_id=218783&item_no=1&page_id=13&block_id=8)，情報処理学会研究報告 組込みシステム，2022年7月．
  - 檜原，中村，高瀬：[ROS 2ノード軽量実行環境mROS 2における任意型メッセージの通信処理方式](https://ipsj.ixsq.nii.ac.jp/ej/?action=pages_view_main&active_action=repository_view_main_item_detail&item_id=217258&item_no=1&page_id=13&block_id=8)，情報処理学会研究報告 組込みシステム，2022年3月．
  - 高瀬，祐源：[mROS 2：組込みデバイス向けのROS 2ノード軽量実行環境](https://ipsj.ixsq.nii.ac.jp/ej/?action=pages_view_main&active_action=repository_view_main_item_detail&item_id=217257&item_no=1&page_id=13&block_id=8)，情報処理学会研究報告 組込みシステム，2022年3月．
- Presentation
  - [ROSCon JP 2022](https://roscon.jp/2022/): ``Now and Next about mROS 2'' [video](https://vimeo.com/781671042) [slide](https://speakerdeck.com/takasehideki/now-and-next-about-mros-2)
  - [TOPPERSカンファレンス2022](https://www.toppers.jp/conference2022.html): ``mROS 2：ロボットソフトウェアの組込みデバイス向け軽量実行環境'' [video](https://www.youtube.com/watch?v=RbMYe4FWtc0) [slide](https://speakerdeck.com/takasehideki/mros-2-robotutosohutoueafalsezu-ip-midebaisuxiang-keqing-liang-shi-xing-huan-jing)
