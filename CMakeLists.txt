# Copyright (c) 2021 smorita_emb
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.16.3)

project(mros2)

target_include_directories(mros2
  BEFORE INTERFACE
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/thirdparty/Micro-CDR/include
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/mros2_msgs
)

target_sources(mros2
  INTERFACE
  ${PROJECT_SOURCE_DIR}/src/mros2.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/communication/UdpDriver.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/messages/MessageTypes.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/messages/MessageReceiver.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/discovery/TopicData.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/discovery/ParticipantProxyData.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/discovery/SEDPAgent.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/discovery/SPDPAgent.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/storages/PBufWrapper.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/ThreadPool.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/entities/Participant.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/entities/Domain.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/src/entities/StatelessReader.cpp
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/thirdparty/Micro-CDR/src/c/common.c
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/basic.c
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/string.c
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/sequence.c
  ${PROJECT_SOURCE_DIR}/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/array.c
)