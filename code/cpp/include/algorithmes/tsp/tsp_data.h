#ifndef TSP_DATA_H
#define TSP_DATA_H

#include <vector>

struct TSPData
{
    std::vector<std::vector<double>> _distances;
    int _nombreSommets;
};

#endif  // TSP_DATA_H