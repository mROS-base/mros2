{%- for includeFile in includeFiles %}
{{includeFile}}
{%- endfor %}

{% for pubMsgType in pubMsgTypes %}
template mros2::Publisher mros2::Node::create_publisher<{{pubMsgType}}>(std::string topic_name, int qos);
template void mros2::Publisher::publish({{pubMsgType}} &msg);
{% endfor %}

{% for subMsgType in subMsgTypes %}
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)({{subMsgType}}*));
template void mros2::Subscriber::callback_handler<{{subMsgType}}>(void *callee, const rtps::ReaderCacheChange &cacheChange);
{% endfor %}