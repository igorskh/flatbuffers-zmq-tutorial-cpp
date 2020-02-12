#include "zmq_helper.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string>

#include "flatbuffers/flatbuffers.h"
#include "schema_generated.h"

const int BUFLEN = 1024;

void create_object(flatbuffers::FlatBufferBuilder *builder)
{
    auto description = builder->CreateString("do any calc");

    int n = 5;
    MyCalc::Vec3 *values_vec;
    values_vec = new MyCalc::Vec3[5];
    for (int i = 0; i < n; i++)
    {
        auto value = MyCalc::Vec3(i, i + 1, i + 2);
        values_vec[i] = value;
    }
    auto values = builder->CreateVectorOfStructs(values_vec, n);
    int axis = 0;
    auto calc_type = MyCalc::CalcType_Median;

    MyCalc::RawDataBuilder raw_data_builder(*builder);
    raw_data_builder.add_axis(axis);
    raw_data_builder.add_calcType(calc_type);
    raw_data_builder.add_description(description);
    raw_data_builder.add_values(values);
    auto raw_data = raw_data_builder.Finish();
    builder->Finish(raw_data);
}

int main(void)
{
    flatbuffers::FlatBufferBuilder builder(1024);

    create_object(&builder);
    printf("%d\n", builder.GetSize());

    zmq::context_t context(1);
    zmq::socket_t broker(context, ZMQ_DEALER);
    broker.connect("tcp://127.0.0.2:5555");

    printf("Sending %u bytes\n", builder.GetSize());
    send_bytes(&broker, builder.GetBufferPointer(), builder.GetSize());

    std::string str = recv_message(&broker);
    printf("Received %s [%lu]\n", str.c_str(), str.size());

    broker.close();
    return 0;
}