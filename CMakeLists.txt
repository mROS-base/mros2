# Copyright (c) 2021 smorita_emb
# SPDX-License-Identifier: Apache-2.0

target_include_directories(mros2
  BEFORE INTERFACE
  embeddedRTPS/thirdparty/Micro-CDR/include
  embeddedRTPS/include
  include
  mros2_msgs
)

target_sources(mros2
  INTERFACE
  src/mros2.cpp
  embeddedRTPS/src/communication/UdpDriver.cpp
  embeddedRTPS/src/messages/MessageTypes.cpp
  embeddedRTPS/src/messages/MessageReceiver.cpp
  embeddedRTPS/src/rtps.cpp
  embeddedRTPS/src/discovery/TopicData.cpp
  embeddedRTPS/src/discovery/ParticipantProxyData.cpp
  embeddedRTPS/src/discovery/SEDPAgent.cpp
  embeddedRTPS/src/discovery/SPDPAgent.cpp
  embeddedRTPS/src/storages/HistoryCache.cpp
  embeddedRTPS/src/storages/SimpleHistoryCache.cpp
  embeddedRTPS/src/storages/PBufWrapper.cpp
  embeddedRTPS/src/ThreadPool.cpp
  embeddedRTPS/src/entities/Participant.cpp
  embeddedRTPS/src/entities/Domain.cpp
  embeddedRTPS/src/entities/StatelessReader.cpp
  embeddedRTPS/thirdparty/Micro-CDR/src/c/common.c
  embeddedRTPS/thirdparty/Micro-CDR/src/c/types/basic.c
  embeddedRTPS/thirdparty/Micro-CDR/src/c/types/string.c
  embeddedRTPS/thirdparty/Micro-CDR/src/c/types/sequence.c
  embeddedRTPS/thirdparty/Micro-CDR/src/c/types/array.c
)
