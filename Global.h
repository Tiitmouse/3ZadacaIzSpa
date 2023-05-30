//
// Created by lorena on 5/30/23.
//

#ifndef INC_3ZADACASPA_GLOBAL_H
#define INC_3ZADACASPA_GLOBAL_H


#include <chrono>
#include <array>
#include <SFML/Graphics.hpp>

namespace gbl {
    namespace COLOR {
        const sf::Color WALLCOLOR = sf::Color(0, 0, 0);
        const sf::Color PATHCOLOR = sf::Color(255, 255, 255);

    }
    namespace PATHFINDING {
        //If you don't want to see the process of the search, set this constant to USHRT_MAX.
        constexpr unsigned short CHECKS_PER_FRAME = 40;
    }

    namespace MAP {
        constexpr unsigned char CELL_SIZE = 8;
        constexpr unsigned char ORIGIN_X = 1;
        constexpr unsigned char ORIGIN_Y = 1;

        constexpr unsigned short COLUMNS = 159;
        constexpr unsigned short ROWS = 89;

        enum Cell {
            Empty,
            Invalid,
            Path,
            Visited,
            Wall
        };
    }

    namespace SCREEN {
        constexpr unsigned char RESIZE = 1;

        constexpr unsigned short HEIGHT = 720;
        constexpr unsigned short WIDTH = 1280;

        //This will make the program run at 60 FPS.
        //Because 1 second == 1,000,000 microseconds
        //1,000,000 microseconds / 60 frames = 16667 microseconds per frame
        constexpr std::chrono::microseconds FRAME_DURATION(16667);
    }

    template<typename value_type>
    char sign(const value_type i_value) {
        return (0 < i_value) - (0 > i_value);
    }

    template<typename value_type = MAP::Cell>
    using Map = std::array<std::array<value_type, MAP::ROWS>, MAP::COLUMNS>;


    template<typename value_type = unsigned short>
    using Position = std::pair<value_type, value_type>;
}

#endif //INC_3ZADACASPA_GLOBAL_H
