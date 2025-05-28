/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Main file
*/

#include <iostream>

#include "OptionParser.hpp"
#include "CommandInterpreter.hpp"

int main(int ac, char **av)
{
    OptionParser parser(ac, av);
    if (parser.isHelpPage()) {
        parser.displayHelpPage();
        return 0;
    }
    if (parser.isError()) {
        std::cerr << "Error: " << parser.getErrorMessage() << std::endl;
        parser.displayHelpPage();
        return 84;
    }
    std::cout << "Multiplier: " << parser.getMultiplier() << std::endl;
    std::cout << "Cooks: " << parser.getCooks() << std::endl;
    std::cout << "Restock Delay: " << parser.getRestockDelay() << std::endl;
    CommandInterpreter interpreter;
    interpreter.run();
    std::cout << "Exiting Plazza reception." << std::endl;
    return 0;
}
