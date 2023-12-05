#include "TerrainMap.h"
#include "Path.h"
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Letadlo.h"
#include "Lodka.h"

Point read_coordinates(int argc, char *argv[], int i_option) {

    Point p;

    if (argc > i_option+1) {
        p.x = std::atoi(argv[i_option]);
        p.y = std::atoi(argv[i_option + 1]);
    }
    else throw std::runtime_error("Coordinates incorrectly specified!");

    return p;
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 4) {
            std::cerr << "Insufficient arguments!" << std::endl;
            return 1;
        }

        const int nx = 256;
        const int ny = 256;

        std::string terrain_filename = argv[1];
        TerrainMap m(nx, ny, terrain_filename);

        Point start = read_coordinates(argc, argv, 2);
        Point finish = read_coordinates(argc, argv, 4);

        std::vector<std::shared_ptr<Path>> paths = {
                std::make_shared<Letadlo>(m, start, finish),
                std::make_shared<Lodka>(m, start, finish),


        };

        for (auto& p : paths) {
            std::cout << "Path search: " << p->getName() << std::endl;
            std::cout << "=============" << std::endl;
            p->find();
            p->printStats();
            std::cout << "=============" << std::endl;
            p->saveToFile();
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
