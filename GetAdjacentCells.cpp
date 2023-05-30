//
// Created by lorena on 5/30/23.
//

#include "GetAdjacentCells.h"
#include <array>

#include <cmath>


#include "Global.h"

#include "GetCell.h"

std::vector<gbl::Position<>> get_adjacent_cells(const gbl::Position<>& i_cell, const gbl::Map<>& i_map)
{
    std::array<bool, 9> valid_adjacent_cells = {};

    std::vector<gbl::Position<>> adjacent_cells;
    std::vector<gbl::Position<>> diagonal_adjacent_cells;

    for (unsigned char a = 0; a < valid_adjacent_cells.size(); a++)
    {
        gbl::MAP::Cell cell = get_cell(gbl::Position<short>(i_cell.first + a % 3 - 1, i_cell.second + std::floor(a / 3.f) - 1), i_map);

        valid_adjacent_cells[a] = gbl::MAP::Cell::Invalid != cell && gbl::MAP::Cell::Wall != cell;
    }

    for (unsigned char a = 0; a < 3; a++)
    {
        for (unsigned char b = 0; b < 3; b++)
        {
            if ((1 != a || 1 != b) && 1 == valid_adjacent_cells[b + 3 * a])
            {
                if (abs(a - 1) == abs(b - 1))
                {
                    if (1 == valid_adjacent_cells[1 + 3 * a] && 1 == valid_adjacent_cells[3 + b])
                    {
                        diagonal_adjacent_cells.emplace_back(b + i_cell.first - 1, a + i_cell.second - 1);
                    }
                }
                else
                {
                    adjacent_cells.emplace_back(b + i_cell.first - 1, a + i_cell.second - 1);
                }
            }
        }
    }
    adjacent_cells.insert(adjacent_cells.end(), diagonal_adjacent_cells.begin(), diagonal_adjacent_cells.end());

    return adjacent_cells;
}