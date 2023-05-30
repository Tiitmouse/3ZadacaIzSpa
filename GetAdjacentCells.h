//
// Created by lorena on 5/30/23.
//

#ifndef INC_3ZADACASPA_GETADJACENTCELLS_H
#define INC_3ZADACASPA_GETADJACENTCELLS_H


#pragma once

#include <vector>
#include "Global.h"

std::vector<gbl::Position<>> get_adjacent_cells(const gbl::Position<>& i_cell, const gbl::Map<>& i_map);


#endif //INC_3ZADACASPA_GETADJACENTCELLS_H
