//
// Created by lorena on 5/30/23.
//

#ifndef INC_3ZADACASPA_DIJKSTRA_H
#define INC_3ZADACASPA_DIJKSTRA_H


#include "Global.h"
#include <map>
#include <queue>

class DijkstraComparison
{
    gbl::Map<float>* distances;
public:
    explicit DijkstraComparison(gbl::Map<float>* i_distances = nullptr);
    bool operator()(const gbl::Position<>& i_left_cell, const gbl::Position<>& i_right_cell) const;
};

bool dijkstra_search(unsigned short& i_path_length, unsigned short& i_total_checks, std::chrono::microseconds& i_duration,
                     std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::priority_queue<gbl::Position<>, std::vector<gbl::Position<>>,
                     DijkstraComparison>& i_path_queue, gbl::Map<float>& i_distances, const gbl::Position<>& i_finish_position, const gbl::Position<>& i_start_position, gbl::Map<>& i_map);

void dijkstra_reset(bool& i_finished, unsigned short& i_path_length, unsigned short& i_total_checks, std::chrono::microseconds& i_duration,
                    std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::priority_queue<gbl::Position<>, std::vector<gbl::Position<>>,
                    DijkstraComparison>& i_path_queue, gbl::Map<float>& i_distances, const gbl::Position<>& i_start_position, gbl::Map<>& i_map);


#endif //INC_3ZADACASPA_DIJKSTRA_H
