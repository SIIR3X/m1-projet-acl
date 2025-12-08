#ifndef DATA_BUILDER_H
#define DATA_BUILDER_H

#include <any>
#include <memory>
#include <vector>

#include "algorithmes/data/input/input_data.h"

class DataBuilder
{
public:
    virtual ~DataBuilder() = default;

    template <typename... Args>
    std::unique_ptr<InputData> construire(Args&&... args) const
    {
        std::vector<std::any> packedArgs;
        packedArgs.reserve(sizeof...(Args));

        (packedArgs.emplace_back(std::forward<Args>(args)), ...);

        return construireDonnees(packedArgs);
    }

protected:
    virtual std::unique_ptr<InputData> construireDonnees(const std::vector<std::any>& args) const = 0;
};

#endif  // DATA_BUILDER_H