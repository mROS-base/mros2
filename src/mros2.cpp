#include "mros2.h"
#include "mros2_user_config.h"

#include <rtps/rtps.h>

#ifdef __MBED__
#include "mbed.h"
#else  /* __MBED__ */
#include "cmsis_os.h"
#endif /* __MBED__ */

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/byte.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int8.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/int64.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/u_int16.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "std_msgs/msg/u_int64.hpp"
#include "std_msgs/msg/w_string.hpp"

//#include "TEST.hpp"
#include "health_msgs/msg/health.hpp"

#ifndef __MBED__
/* Statement to avoid link error */
void* __dso_handle=0;
#endif /* __MBED__ */


namespace mros2
{

rtps::Domain *domain_ptr = NULL;
rtps::Participant *part_ptr = NULL; //TODO: detele this
rtps::Writer *pub_ptr = NULL;

#define SUB_MSG_SIZE	4	// addr size
osMessageQueueId_t subscriber_msg_gueue_id;

bool completeNodeInit = false;
uint8_t endpointId = 0;
uint32_t subCbArray[10];

uint8_t buf[100];
uint8_t buf_index = 4;

/* Callback function to set the boolean to true upon a match */
void setTrue(void* args)
{
  *static_cast<volatile bool*>(args) = true;
}

bool subMatched = false;
bool pubMatched = false;

void pubMatch(void* args)
{
  MROS2_DEBUG("[MROS2LIB] publisher matched with remote subscriber");
}

void subMatch(void* args)
{
  MROS2_DEBUG("[MROS2LIB] subscriber matched with remote publisher");
}


/*
 *  Initialization of mROS 2 environment
 */
#ifdef __MBED__
Thread *mros2_init_thread;
#endif /* __MBED__ */
void init(int argc, char * argv[])
{
  buf[0] = 0;
  buf[1] = 1;
  buf[2] = 0;
  buf[3] = 0;

#ifdef __MBED__
  mros2_init_thread =  new Thread(osPriorityAboveNormal, 2000, nullptr, "mROS2Thread");
  mros2_init_thread->start(callback(mros2_init, (void *)NULL));
#else /* __MBED__ */
  osThreadAttr_t attributes;

  attributes.name = "mROS2Thread",
  attributes.stack_size = 1000,
  attributes.priority = (osPriority_t)24,

  osThreadNew(mros2_init, NULL, (const osThreadAttr_t*)&attributes);
#endif /* __MBED__ */

}

void mros2_init(void *args)
{
  osStatus_t ret;

  MROS2_DEBUG("[MROS2LIB] mros2_init task start");

#ifndef __MBED__
  MX_LWIP_Init();
  MROS2_DEBUG("[MROS2LIB] Initilizing lwIP complete");
#endif /* __MBED__ */

  int sub_msg_count;
  static rtps::Domain domain;
  domain_ptr = &domain;

#ifndef __MBED__
  sub_msg_count = mros2_get_submsg_count();
  subscriber_msg_gueue_id = osMessageQueueNew(sub_msg_count, SUB_MSG_SIZE, NULL);
  if (subscriber_msg_gueue_id == NULL) {
    MROS2_ERROR("[MROS2LIB] ERROR: mROS2 init failed");
    return;
  }
#endif /* __MBED__ */

  /* wait until participant(node) is created */
  while(!completeNodeInit) {
    osDelay(100);
  }
  domain.completeInit();
  MROS2_DEBUG("[MROS2LIB] Initilizing Domain complete");

  while(!subMatched && !pubMatched) {
    osDelay(1000);
  }

  MROS2_DEBUG("[MROS2LIB] mros2_init task end");

  ret = osThreadTerminate(NULL);
  if (ret != osOK) {
    MROS2_ERROR("[MROS2LIB] ERROR: mros2_init() task terminate error %d", ret);
  }
}


/*
 *  Node functions
 */
Node Node::create_node(std::string node_name)
{
  MROS2_DEBUG("[MROS2LIB] create_node");
  MROS2_DEBUG("[MROS2LIB] start creating participant");

  while(domain_ptr == NULL) {
    osDelay(100);
  }

  Node node;
  node.part = domain_ptr->createParticipant();
  /* TODO: utilize node name */
  node.node_name = node_name;
  part_ptr = node.part;
  if(node.part == nullptr) {
    MROS2_ERROR("[MROS2LIB] ERROR: create_node() failed");
    while(true) {}
  }
  completeNodeInit = true;

  MROS2_DEBUG("[MROS2LIB] successfully created participant");
  return node;
}


/*
 *  Publisher functions
 */
template <class T>
Publisher Node::create_publisher(std::string topic_name, int qos)
{
  rtps::Writer* writer = domain_ptr->createWriter(*part_ptr, ("rt/"+topic_name).c_str(), message_traits::TypeName<T*>().value(), false);
  if(writer == nullptr) {
    MROS2_ERROR("[MROS2LIB] ERROR: failed to create writer in create_publisher()");
    while(true) {}
  }

  Publisher pub;
  pub_ptr = writer;
  pub.topic_name = topic_name;

  /* Register callback to ensure that a publisher is matched to the writer before sending messages */
  part_ptr->registerOnNewSubscriberMatchedCallback(pubMatch, &subMatched);

  MROS2_DEBUG("[MROS2LIB] create_publisher complete.");
  return pub;
}

template <class T>
void Publisher::publish(T& msg)
{
  msg.copyToBuf(&buf[4]);
  pub_ptr->newChange(rtps::ChangeKind_t::ALIVE, buf, msg.getTotalSize() + 4);
}


/*
 *  Subscriber functions
 */
typedef struct {
  void (*cb_fp)(intptr_t);
  intptr_t argp;
} SubscribeDataType;

template <class T>
Subscriber Node::create_subscription(std::string topic_name, int qos, void(*fp)(T*))
{
  rtps::Reader* reader = domain_ptr->createReader(*(this->part), ("rt/"+topic_name).c_str(), message_traits::TypeName<T*>().value(), false);
  if(reader == nullptr) {
    MROS2_ERROR("[MROS2LIB] ERROR: failed to create reader in create_subscription()");
    while(true) {}
  }

  Subscriber sub;
  sub.topic_name = topic_name;
  sub.cb_fp = (void (*)(intptr_t))fp;

  SubscribeDataType *data_p;
  data_p = new SubscribeDataType;
  data_p->cb_fp = (void (*)(intptr_t))fp;
  data_p->argp = (intptr_t)NULL;
  reader->registerCallback(sub.callback_handler<T>, (void *)data_p);

  /* Register callback to ensure that a subscriber is matched to the reader before receiving messages */
  part_ptr->registerOnNewPublisherMatchedCallback(subMatch, &pubMatched);

  MROS2_DEBUG("[MROS2LIB] create_subscription complete. data memory address=0x%x", data_p);
  return sub;
}

template <class T>
void Subscriber::callback_handler(void *callee, const rtps::ReaderCacheChange &cacheChange)
{
  T msg;
  msg.copyFromBuf(&cacheChange.data[4]);

  SubscribeDataType *sub = (SubscribeDataType *)callee;
  void (*fp)(intptr_t) = sub->cb_fp;
  fp((intptr_t)&msg);
}


/*
 *  Other utility functions
 */
void spin()
{
  while(true) {
#ifndef __MBED__
    osStatus_t ret;
    SubscribeDataType* msg;
    ret = osMessageQueueGet(subscriber_msg_gueue_id, &msg, NULL, osWaitForever);
    if (ret != osOK) {
      MROS2_ERROR("[MROS2LIB] ERROR: mROS2 spin() wait error %d", ret);
    }
#else /* __MBED__ */
    // The queue above seems not to be pushed anywhere. So just sleep.
    ThisThread::sleep_for(1000);
#endif /* __MBED__ */
  }
}

}  /* namespace mros2 */


/*
 *  Declaration for embeddedRTPS participants
 */
void *networkSubDriverPtr;
void *networkPubDriverPtr;
void (*hbPubFuncPtr)(void *);
void (*hbSubFuncPtr)(void *);

extern "C" void callHbPubFunc(void *arg)
{
  if(hbPubFuncPtr != NULL && networkPubDriverPtr != NULL) {
    (*hbPubFuncPtr)(networkPubDriverPtr);
  }
}
extern "C" void callHbSubFunc(void *arg)
{
  if(hbSubFuncPtr != NULL && networkSubDriverPtr != NULL) {
    (*hbSubFuncPtr)(networkSubDriverPtr);
  }
}

void setTrue(void* args)
{
  *static_cast<volatile bool*>(args) = true;
}


/*
 *  specialize template functions
 */

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Bool>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Bool*));
template void mros2::Publisher::publish(std_msgs::msg::Bool &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Bool>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Byte>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Byte*));
template void mros2::Publisher::publish(std_msgs::msg::Byte &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Byte>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Float32>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Float32*));
template void mros2::Publisher::publish(std_msgs::msg::Float32 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Float32>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Float64>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Float64*));
template void mros2::Publisher::publish(std_msgs::msg::Float64 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Float64>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Int8>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Int8*));
template void mros2::Publisher::publish(std_msgs::msg::Int8 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Int8>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Int16>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription<std_msgs::msg::Int16>(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Int16*));
template void mros2::Publisher::publish(std_msgs::msg::Int16 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Int16>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Int32>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Int32*));
template void mros2::Publisher::publish(std_msgs::msg::Int32 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Int32>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Int64>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Int64*));
template void mros2::Publisher::publish(std_msgs::msg::Int64 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Int64>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::String>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::String*));
template void mros2::Publisher::publish(std_msgs::msg::String &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::String>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::UInt8>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::UInt8*));
template void mros2::Publisher::publish(std_msgs::msg::UInt8 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::UInt8>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::UInt16>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::UInt16*));
template void mros2::Publisher::publish(std_msgs::msg::UInt16 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::UInt16>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::UInt32>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::UInt32*));
template void mros2::Publisher::publish(std_msgs::msg::UInt32 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::UInt32>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::UInt64>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::UInt64*));
template void mros2::Publisher::publish(std_msgs::msg::UInt64 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::UInt64>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::WString>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::WString*));
template void mros2::Publisher::publish(std_msgs::msg::WString &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::WString>(void *callee, const rtps::ReaderCacheChange &cacheChange);

/* Work in Progress: for custom message
template mros2::Publisher mros2::Node::create_publisher<TEST>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(TEST*));
template void mros2::Publisher::publish(TEST& msg);
*/

template mros2::Publisher mros2::Node::create_publisher<health_msgs::msg::Health>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(health_msgs::msg::Health*));
template void mros2::Publisher::publish(health_msgs::msg::Health &msg);
template void mros2::Subscriber::callback_handler<health_msgs::msg::Health>(void *callee, const rtps::ReaderCacheChange &cacheChange);
