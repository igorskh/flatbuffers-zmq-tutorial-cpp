#include "zmq_helper.hpp"
#include <iostream>
#include "flatbuffers/flatbuffers.h"
#include "schema_generated.h"
#include <fstream>

void extract_data(const char *data) {
    auto raw_data = MyCalc::GetRawData(data);
    
    printf("Received request for " );
    switch (raw_data->calcType()) {
        case MyCalc::CalcType_Average : printf("Average" ); break;
        case MyCalc::CalcType_Median : printf("Median" ); break;
        case MyCalc::CalcType_Sum : printf("Sum" ); break;
    }
    printf(" on axis %d\n", raw_data->axis());
    printf("Description: %s\n", raw_data->description()->c_str());
    printf("Number of values: %d \n", raw_data->values()->size());
}

int main()
{
    zmq::context_t context(1);
    zmq::socket_t broker(context, ZMQ_ROUTER);

    broker.bind("tcp://*:5555");

    while (1)
    {
        std::string identity = recv_message(&broker);
        std::string msg = recv_message(&broker);

        extract_data(msg.c_str());
        // send_message(&broker, identity, ZMQ_SNDMORE);
        // send_message(&broker, msg);
    }

    return 0;
}