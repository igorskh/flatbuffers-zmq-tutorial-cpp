#include "helpers/zmq_helper.hpp"
#include "helpers/flatbuffers_helper.hpp"

int main(void)
{
    flatbuffers::FlatBufferBuilder builder(1024);
    create_object(&builder);

    zmq::context_t context(1);
    zmq::socket_t broker(context, ZMQ_DEALER);
    broker.connect("tcp://127.0.0.2:5555");

    printf("Sending %u bytes\n", builder.GetSize());
    send_bytes(&broker, builder.GetBufferPointer(), builder.GetSize());

    broker.close();
    return 0;
}