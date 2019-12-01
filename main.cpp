/*
Студент: Лагода Д.А.И
Группа: М8О-207Б
Создать набор шаблонов, создающих функции, реализующие:
1.       Вычисление геометрического центра фигуры;
2.       Вывод в стандартный поток вывода std::cout координат вершин фигуры;
3.       Вычисление площади фигуры;
Создать программу, которая позволяет:
•  Вводить из стандартного ввода std::cin фигуры, согласно варианту задания (как в виде класса, так и в виде std::tuple).
•  Вызывать для нее шаблонные функции (1-3).
*/

#include <iostream>
#include <vector>
#include <map>
#include "figures.hpp"

enum { 
    ERR, ADD,
    PRINT, DEL,
    PENT, EXIT,
    CENTR, AREA,
    HEX, RHOMB,
    SIZE, HELP
};

void help() {
    std::cout << "Commands: add, del, print, area, size, quit, help, centr\n";
    std::cout << "Supported Figures: hexagon, pentagon, rhombus\n";
    std::cout << "Figure id can be number or target \"all\"\n";
}

int main() {
    Point tmpP1, tmpP2;
    int temp;
    std::string comId, figType;
    Pentagon* tmpV;
    int id;
    double length, angle, overallArea;
    int status = 1;
    std::vector<Figure*> vec;
    std::map <std::string, int> command;
    command["add"] = ADD;
    command["print"] = PRINT;
    command["del"] = DEL;
    command["pent"] = PENT;
    command["pentagon"] = PENT;
    command["quit"] = EXIT;
    command["q"] = EXIT;
    command["centr_of"] = CENTR;
    command["centr"] = CENTR;
    command["area_of"] = AREA;
    command["area"] = AREA;
    command["size_of"] = AREA;
    command["size"] = SIZE;
    command["hex"] = HEX;
    command["hexagon"] = HEX;
    command["rhomb"] = RHOMB;
    command["help"] = HELP;
    command["h"] = HELP;

    help();
    while (status) {
        
        std::cout << "Enter command: ";
        std::cin >> comId;
        switch (command[comId]) {
            case ADD:
                std::cin >> figType;
                switch (command[figType]) {
                    
                    case RHOMB:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure*>(new Rhombus(tmpP1, tmpP2, length)));
                        std::cout << "Rhombus added\n";
                        break;
                        
                    case PENT:
                        if (!( std::cin >> tmpP1 >> temp)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure*>(new Pentagon(tmpP1, temp)));
                        std::cout << "Pentagon added\n";
                        break;

                        break;
                    case HEX:
                        if (!( std::cin >> tmpP1 >> temp)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure*>(new Hexagon(tmpP1, temp)));
                        std::cout << "Hexagon added\n";
                        break;
                    case ERR:
                        std::cout << "Unknown figure\n";
                        break;
                }
                break;
            case PRINT:
                std::cin >> comId;
                if (comId == "all") {
                    for (int i = 0; i < vec.size(); i++) {
                        vec[i]->printCoor();
                        putchar('\n');
                    }
                } else {
                    try {
                        id = std::stoi(comId);
                    } catch (std::invalid_argument) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    if (id > ((int)vec.size() - 1) || id < 0) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    vec[id]->printCoor();
                }
                break;
                
            case CENTR:
                if (!(std::cin >> id)) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                if (id > ((int)vec.size() - 1) || id < 0) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                std::cout << vec[id]->centr() << '\n';
                break;
            case AREA:
                std::cin >> comId;
                if (comId == "all") {
                    overallArea = 0;
                    for (int i = 0; i < vec.size(); i++) {
                        overallArea += vec[i]->area();
                    }
                    std::cout << overallArea << '\n';
                } else {
                    try {
                        id = std::stoi(comId);
                    } catch (std::invalid_argument) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    if (id > ((int)vec.size() - 1) || id < 0) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    std::cout << vec[id]->area() << '\n';
                }
                break;
            case DEL:
                if (!(std::cin >> id)) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                if (id > ((int)vec.size() - 1) || id < 0) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                delete vec[id];
                vec.erase(vec.begin() + id);
                std::cout << "Deleted\n";
                break;
            case SIZE:
                std::cout << vec.size() << "\n";
                break;
            case HELP:
                help();
                break;
            case ERR:
                std::cout << "Invalid command\n";
                break;
            case EXIT:
                for (int i = 0; i < vec.size(); i++) {
                    delete vec[i];
                }
                status = 0;
                break;
        }
        while(getchar() != '\n');
        std::cin.clear();
    }
    return 0;
}
