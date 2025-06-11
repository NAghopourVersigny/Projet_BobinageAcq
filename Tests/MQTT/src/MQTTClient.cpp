#include <iostream>

#include "../include/MQTTClient.h"

MQTTClient::MQTTClient(const std::string &id, const std::string &host, int port, const std::string &topic,
                       const std::string &username,
                       const std::string &password)
    : id_(id), host_(host), port_(port), topic_(topic),
      username_(username), password_(password), mosq_(nullptr), callbackHandler_(nullptr)
{
    mosquitto_lib_init();
    mosq_ = mosquitto_new(id.c_str(), true, this);
    mosquitto_message_callback_set(mosq_, MQTTClient::onMessage);
}

MQTTClient::~MQTTClient()
{

    if (mosq_)
    {
        mosquitto_destroy(mosq_);
    }
    mosquitto_lib_cleanup();
}

void MQTTClient::setCallbackHandler(SurveillanceMachineServ *handler)
{
    callbackHandler_ = handler;
}

bool MQTTClient::connect()
{
    if (!username_.empty())
    {
        mosquitto_username_pw_set(mosq_, username_.c_str(), password_.c_str());
    }
    return mosquitto_connect(mosq_, host_.c_str(), port_, 60) == MOSQ_ERR_SUCCESS;
}

void MQTTClient::disconnect()
{
    mosquitto_disconnect(mosq_);
}

bool MQTTClient::publish(const std::string &topic, const std::string &payload)
{
    return mosquitto_publish(mosq_, nullptr, topic.c_str(), payload.size(), payload.c_str(), 1, false) == MOSQ_ERR_SUCCESS;
}

bool MQTTClient::subscribe(vector<string> topics)
{
    // mosquitto_subscribe(mosq_, nullptr, topic_.c_str(), 1);
    for (int i = 0; i < topics.size(); i++)
        mosquitto_subscribe(mosq_, nullptr, topics[i].c_str(), 1);
    return mosquitto_loop_start(mosq_) == MOSQ_ERR_SUCCESS;
}

void MQTTClient::onMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    MQTTClient *client = static_cast<MQTTClient *>(obj);
    if (client->callbackHandler_)
    {
        std::string payload(static_cast<char *>(message->payload), message->payloadlen);
        std::string topic(message->topic);
        client->callbackHandler_->gererReception(topic, payload);
    }
}
void MQTTClient::loopForever()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
