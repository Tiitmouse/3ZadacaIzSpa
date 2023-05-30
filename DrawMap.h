//
// Created by lorena on 5/30/23.
//

#ifndef INC_3ZADACASPA_DRAWMAP_H
#define INC_3ZADACASPA_DRAWMAP_H

#include "Global.h"
#include <SFML/Graphics.hpp>
void draw_map(unsigned short i_x, unsigned short i_y, const gbl::Position<>& i_finish_position,
              const gbl::Position<>& i_start_position, sf::RenderWindow& i_window, sf::Sprite& i_map_sprite,
              const gbl::Map<>& i_map, bool i_change_colors = false, const gbl::Map<float>& i_distances = {});


#endif //INC_3ZADACASPA_DRAWMAP_H
