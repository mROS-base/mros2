#ifndef MROS2_MROS2_H
#define MROS2_MROS2_H

#include <string>
#include "rtps/rtps.h"
#ifndef __MBED__
#include "lwip.h"
#endif /* __MBED__ */
#include "mros2/logging.h"

/* Statement to avoid link error */
#ifdef __cplusplus
extern void* __dso_handle;
#endif

namespace mros2
{

void init(int argc, char * argv[]);

#ifdef __cplusplus
extern "C" {
#endif
void mros2_init(void *arg);
#ifdef __cplusplus
}
#endif

class Node;
class Publisher;
class Subscriber;

/* TODO: move to node.h/cpp? */
class Node
{
public:
  static Node create_node(
    std::string node_name
  );

  template <class T>
  Publisher create_publisher(
    std::string topic_name,
    int qos
  );

  template <class T>
  Subscriber create_subscription(
    std::string topic_name,
    int qos,
    void (*fp)(T*)
  );

  std::string node_name;
  rtps::Participant* part;

private:

};

class Publisher
{
public:
  std::string topic_name;
  template <class T>
  void publish(T& msg);
};

class Subscriber
{
public:
  std::string topic_name;
  template <class T> 
  static void callback_handler(
    void* callee,
    const rtps::ReaderCacheChange& cacheChange
  );
  void (*cb_fp)(intptr_t);
private:
};

void spin();

}  /* namespace mros2 */

namespace message_traits
{
template <class T>
struct TypeName {
static const char* value();
};
}  /* namespace message_traits */

#endif /* MROS2_MROS2_H */