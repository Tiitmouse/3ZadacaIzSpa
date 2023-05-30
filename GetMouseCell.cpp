//
// Created by lorena on 5/30/23.
//

#include "GetMouseCell.h"

#include <array>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "GetMouseCell.h"

gbl::Position<short> get_mouse_cell(const sf::RenderWindow& i_window)
{
    float mouse_x = sf::Mouse::getPosition(i_window).x - gbl::MAP::ORIGIN_X * gbl::SCREEN::RESIZE;
    float mouse_y = sf::Mouse::getPosition(i_window).y - gbl::MAP::ORIGIN_Y * gbl::SCREEN::RESIZE;

    return gbl::Position<short>(float(mouse_x / gbl::MAP::CELL_SIZE / gbl::SCREEN::RESIZE),
                                float(mouse_y / gbl::MAP::CELL_SIZE / gbl::SCREEN::RESIZE));
}