#ifndef __ZMQHELPER_HPP_INCLUDED__
#define __ZMQHELPER_HPP_INCLUDED__

#include <zmq.hpp>

std::string recv_message(zmq::socket_t *sock, int flag = ZMQ_NULL)
{
    zmq::message_t message;
    sock->recv(&message, flag);
    return std::string(static_cast<char *>(message.data()), message.size());
}

bool send_message(zmq::socket_t *sock, std::string str, int flag = ZMQ_NULL)
{
    zmq::message_t message(str.size());
    memcpy(message.data(), str.data(), str.size());

    bool rc = sock->send(message, flag);
    return (rc);
}

bool send_bytes(zmq::socket_t *sock, uint8_t* data, int data_size, int flag = ZMQ_NULL)
{
    zmq::message_t message(data_size);
    memcpy(message.data(), data, data_size);

    bool rc = sock->send(message, flag);
    return (rc);
}

#endif