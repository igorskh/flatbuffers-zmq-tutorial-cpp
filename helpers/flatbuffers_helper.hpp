#ifndef __FLATBUFFERSHELPER_HPP_INCLUDED__
#define __FLATBUFFERSHELPER_HPP_INCLUDED__

#include "schema_generated.h"

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

void create_object(flatbuffers::FlatBufferBuilder *builder)
{
    auto description = builder->CreateString("do any calc");

    int n = 5;
    MyCalc::Vec3 *values_vec;
    values_vec = new MyCalc::Vec3[n];
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

#endif