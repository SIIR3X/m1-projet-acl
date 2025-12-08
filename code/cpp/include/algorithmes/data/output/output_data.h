#ifndef OUTPUT_DATA_H
#define OUTPUT_DATA_H

#include <string>

struct OutputData
{
    virtual ~OutputData() = default;

    virtual std::string toJson() const = 0;
};

#endif  // OUTPUT_DATA