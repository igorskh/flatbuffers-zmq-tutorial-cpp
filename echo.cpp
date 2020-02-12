#include "zmq_helper.hpp"
#include <iostream>
#include "flatbuffers/flatbuffers.h"
#include "schema_generated.h"
#include <fstream>

int main()
{
    zmq::context_t context(1);
    zmq::socket_t broker(context, ZMQ_ROUTER);

    broker.bind("tcp://*:5555");

    while (1)
    {
        std::string identity = recv_message(&broker);
        std::string msg = recv_message(&broker);

        send_message(&broker, identity, ZMQ_SNDMORE);
        send_message(&broker, msg);
    }

    return 0;
}