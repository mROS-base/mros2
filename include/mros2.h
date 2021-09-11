#ifndef MROS2_MROS2_H
#define MROS2_MROS2_H

#include <string>
#include "rtps/rtps.h"

// To avoid link error
#ifdef __cplusplus
extern void* __dso_handle;
#endif

namespace mros2
{

class Subscriber
{
public:
  std::string topic_name;
  static void callback_handler(
    void* callee,
    const rtps::ReaderCacheChange& cacheChange
  );
  void (*cb_fp)(intptr_t);
private:
};

class Publisher
{
public:
  std::string topic_name;
  template <class T>
  void publish(T& msg);
};

class Node//TODO: move to node.h/cpp?
{
public:
  static Node create_node();
  template <class T>
  Subscriber create_subscription(
    std::string node_name,
    int qos,
    void (*fp)(T)
  );
  template <class T>
  Publisher create_publisher(
    std::string node_name,
    int qos
  );
  std::string node_name;
  rtps::Participant* part;

private:

};


void init(int argc, char *argv);
void spin();

void setTrue(void *args);
void setTrue(void *args);
void message_callback(void* callee, const rtps::ReaderCacheChange& cacheChange);
void message_callback(void* callee, const rtps::ReaderCacheChange& cacheChange);

#ifdef __cplusplus
extern "C" {
#endif
void mros2_init(void *arg);
#ifdef __cplusplus
}
#endif
}//namespace mros2

namespace message_traits
{
template <class T>
struct TypeName {
static const char* value();
};
}// namespace message_traits
#endif //MROS2_MROS2_H

