#ifndef TSP_INPUT_DATA_H
#define TSP_INPUT_DATA_H

#include <string>
#include <vector>

#include "algorithmes/data/input/input_data.h"

struct TSPInputData : public InputData
{
    std::vector<std::vector<double>> distances;
    std::vector<std::string> labels;
    int nombreSommets;
    int machines;
};

#endif  // TSP_INPUT_DATA_H