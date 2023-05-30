#include <array>
#include <chrono>
#include <queue>
#include <map>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "DrawMap.h"
#include "GetMouseCell.h"
#include "Dijkstra.h"

using namespace std;
bool LoadTexture(sf::Texture&t, std::string path){
       return t.loadFromFile(path);
}

int main() {

    bool dijkstra_finished = false;

    unsigned short dijkstra_path_length = 0;
    unsigned short dijkstra_total_checks = 0;

    chrono::microseconds dijkstra_duration(0);

    map<gbl::Position<>, gbl::Position<>> dijkstra_previous_cell;

    gbl::Map<float> dijkstra_distances = {};


    priority_queue<gbl::Position<>, vector<gbl::Position<>>, DijkstraComparison> dijkstra_path_queue(
            (DijkstraComparison(&dijkstra_distances)));

    gbl::Map<> map = {};



    bool mouse_pressed = false;
    bool pause_search = true;

    chrono::microseconds lag(0);

    chrono::steady_clock::time_point previous_time;

    sf::Event event{};

    sf::RenderWindow window(
            sf::VideoMode(gbl::SCREEN::RESIZE * gbl::SCREEN::WIDTH, gbl::SCREEN::RESIZE * gbl::SCREEN::HEIGHT),
            "Pathfinding", sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT)));

    sf::Sprite map_sprite;

    sf::Texture map_texture;
    if(LoadTexture(map_texture,"Map.png"));
    else
        LoadTexture(map_texture,"../Map.png");

    gbl::Position<> finish_position(gbl::MAP::COLUMNS - 1, gbl::MAP::ROWS - 1);
    gbl::Position<> start_position(0, 0);


    gbl::Position<short> mouse_cell_start;

    for (array<gbl::MAP::Cell, gbl::MAP::ROWS> &column: map) {
        column.fill(gbl::MAP::Cell::Empty);
    }

    map_sprite.setTexture(map_texture);
    previous_time = chrono::steady_clock::now();

    while (1 == window.isOpen()) {
        chrono::microseconds delta_time = chrono::duration_cast<chrono::microseconds>(
                chrono::steady_clock::now() - previous_time);

        lag += delta_time;

        previous_time += delta_time;

        while (gbl::SCREEN::FRAME_DURATION <= lag) {
            bool map_updated = 0;

            lag -= gbl::SCREEN::FRAME_DURATION;

            while (1 == window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed: {
                        window.close();

                        break;
                    }
                    case sf::Event::KeyPressed: {
                        switch (event.key.code) {
                            case sf::Keyboard::Enter:
                            {
                                pause_search = 1 - pause_search;

                                break;
                            }
                            case sf::Keyboard::R:
                            {
                                map_updated = 1;

                                break;
                            }
                            case sf::Keyboard::Space:
                            {
                                for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++) {
                                    for (unsigned short b = 0; b < gbl::MAP::ROWS; b++) {
                                        map[a][b] = gbl::MAP::Empty;
                                    }
                                }

                                map_updated = 1;
                            }
                        }
                    }
                }
            }

            if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ||
                1 == sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                if (0 == mouse_pressed) {
                    mouse_pressed = true;

                    mouse_cell_start = get_mouse_cell(window);
                }
            } else {
                mouse_pressed = false;
            }

            if (1 == mouse_pressed) {
                char step_x;
                char step_y;


                unsigned short line_size;

                gbl::Position<short> mouse_cell = get_mouse_cell(window);


                line_size = 1 + max(abs(mouse_cell.first - mouse_cell_start.first),
                                    abs(mouse_cell.second - mouse_cell_start.second));

                step_x = gbl::sign(mouse_cell.first - mouse_cell_start.first);
                step_y = gbl::sign(mouse_cell.second - mouse_cell_start.second);

                for (unsigned short a = 0; a < line_size; a++) {
                    gbl::Position<short> cell;


                    cell.first = mouse_cell_start.first + step_x * floor(a * (1 + abs(mouse_cell.first -
                                                                                      mouse_cell_start.first)) /
                                                                         static_cast<float>(line_size));
                    cell.second = mouse_cell_start.second + step_y * floor(a * (1 + abs(mouse_cell.second -
                                                                                        mouse_cell_start.second)) /
                                                                           static_cast<float>(line_size));

                    if (0 <= cell.first && 0 <= cell.second && cell.first < gbl::MAP::COLUMNS &&
                        cell.second < gbl::MAP::ROWS) {
                        if (finish_position != static_cast<gbl::Position<>>(cell) &&
                            start_position != static_cast<gbl::Position<>>(cell)) {
                            if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                if (gbl::MAP::Cell::Wall != map[cell.first][cell.second]) {
                                    map_updated = true;

                                    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                                        map[cell.first][cell.second] = gbl::MAP::Cell::Empty;
                                        finish_position = cell;
                                    } else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                                        map[cell.first][cell.second] = gbl::MAP::Cell::Empty;
                                        start_position = cell;
                                    } else {
                                        map[cell.first][cell.second] = gbl::MAP::Cell::Wall;
                                    }
                                }
                            } else if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                                if (gbl::MAP::Cell::Wall == map[cell.first][cell.second]) {
                                    map_updated = true;

                                    map[cell.first][cell.second] = gbl::MAP::Cell::Empty;
                                }
                            }
                        }
                    }
                }

                mouse_cell_start = mouse_cell;
            }

            if (1 == map_updated) {
                map = map;

                dijkstra_reset(dijkstra_finished, dijkstra_path_length, dijkstra_total_checks, dijkstra_duration,
                               dijkstra_previous_cell,
                               dijkstra_path_queue, dijkstra_distances, start_position, map);

            }

            if (0 == pause_search) {
                if (0 == dijkstra_finished) {
                    dijkstra_finished = dijkstra_search(dijkstra_path_length, dijkstra_total_checks, dijkstra_duration,
                                                        dijkstra_previous_cell, dijkstra_path_queue,
                                                        dijkstra_distances, finish_position, start_position,
                                                        map);
                }

            }


            if (gbl::SCREEN::FRAME_DURATION > lag) {
                window.clear();
                draw_map(0, 0, finish_position, start_position, window, map_sprite,
                         map, 1, dijkstra_distances);

                window.display();
            }
        }
    }

}