/*
 *  specialize template functions
 */

#include "mros2.h"

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/byte.hpp"
#include "std_msgs/msg/char.hpp"
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

#include "TEST.hpp"

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Bool>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Bool*));
template void mros2::Publisher::publish(std_msgs::msg::Bool &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Bool>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Byte>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Byte*));
template void mros2::Publisher::publish(std_msgs::msg::Byte &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Byte>(void *callee, const rtps::ReaderCacheChange &cacheChange);

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Char>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Char*));
template void mros2::Publisher::publish(std_msgs::msg::Char &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Char>(void *callee, const rtps::ReaderCacheChange &cacheChange);

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