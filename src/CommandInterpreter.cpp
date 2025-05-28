/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** CommandInterpreter
*/

#include "CommandInterpreter.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <cctype>

bool CommandInterpreter::isValidPizzaType(const std::string& type) const
{
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(),
                   ::tolower);

    return (lowerType == "regina" || lowerType == "margarita" ||
            lowerType == "americana" || lowerType == "fantasia");
}

bool CommandInterpreter::isValidPizzaSize(const std::string& size) const
{
    return (size == "S" || size == "M" || size == "L" || size == "XL" ||
            size == "XXL");
}

bool CommandInterpreter::isValidNumber(const std::string& number) const
{
    std::string numStr;
    int num;

    if (number.empty() || number[0] != 'x' || number[1] == '0') {
        return false;
    }
    numStr = number.substr(1);
    if (numStr.empty()) {
        return false;
    }
    for (char c : numStr) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    num = std::stoi(numStr);
    return (num >= 1);
}

std::string CommandInterpreter::trimWhitespace(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");

    return (first == std::string::npos) ? ""
                                        : str.substr(first, last - first + 1);
}

void CommandInterpreter::parseIndividualPizza(const std::string& pizzaCommand,
                                              std::string& type,
                                              std::string& size,
                                              std::string& number)
{
    std::istringstream iss(pizzaCommand);
    std::string extra;

    if (!(iss >> type >> size >> number)) {
        throw std::invalid_argument("Invalid pizza command format: " +
                                    pizzaCommand);
    }
    if (iss >> extra) {
        throw std::invalid_argument("Too many arguments in pizza command: " +
                                    pizzaCommand);
    }
}

PizzaOrder CommandInterpreter::createPizzaOrder(const std::string& type,
                                                const std::string& size,
                                                const std::string& number)
{
    PizzaOrder order;

    order.type = type;
    order.size = size;
    order.quantity =
        std::stoi(number.substr(1));  // Remove 'x' and convert to int
    return order;
}

void CommandInterpreter::validatePizzaComponents(const std::string& type,
                                                 const std::string& size,
                                                 const std::string& number)
{
    if (!isValidPizzaType(type)) {
        throw std::invalid_argument("Invalid pizza type: " + type);
    }
    if (!isValidPizzaSize(size)) {
        throw std::invalid_argument("Invalid pizza size: " + size);
    }
    if (!isValidNumber(number)) {
        throw std::invalid_argument("Invalid pizza number format: " + number);
    }
}

std::vector<PizzaOrder> CommandInterpreter::parsePizzaOrder(
    const std::string& orderStr)
{
    std::vector<PizzaOrder> orders;
    std::stringstream ss(orderStr);
    std::string pizzaCommand;
    std::string type, size, number;

    while (std::getline(ss, pizzaCommand, ';')) {
        pizzaCommand = trimWhitespace(pizzaCommand);
        if (pizzaCommand.empty()) {
            continue;
        }
        parseIndividualPizza(pizzaCommand, type, size, number);
        validatePizzaComponents(type, size, number);
        orders.push_back(createPizzaOrder(type, size, number));
    }

    return orders;
}

void CommandInterpreter::handlePizzaOrder(const std::vector<PizzaOrder>& orders)
{
    std::cout << "Processing pizza order:" << std::endl;
    for (const auto& order : orders) {
        std::cout << "  - " << order.quantity << "x " << order.type << " ("
                  << order.size << ")" << std::endl;
    }

    // TODO
}

void CommandInterpreter::handleStatusCommand()
{
    // TODO
    std::cout << "Kitchen Status:" << std::endl;
    std::cout << "  - Number of active kitchens: [TODO]" << std::endl;
    std::cout << "  - Cook occupancy: [TODO]" << std::endl;
    std::cout << "  - Ingredient stocks: [TODO]" << std::endl;
}

int CommandInterpreter::runCommand(std::string& line)
{
    std::vector<PizzaOrder> orders;

    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);
    if (line.empty()) {
        return 0;
    }
    if (line == "quit" || line == "exit") {
        return 1;
    }
    if (line == "status") {
        handleStatusCommand();
        return 0;
    }
    try {
        orders = parsePizzaOrder(line);
        if (!orders.empty()) {
            handlePizzaOrder(orders);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Usage: TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*"
                  << std::endl;
        std::cerr << "  TYPE: regina, margarita, americana, fantasia"
                  << std::endl;
        std::cerr << "  SIZE: S, M, L, XL, XXL" << std::endl;
        std::cerr << "  NUMBER: xN (where N is a positive integer)"
                  << std::endl;
        std::cerr << "Example: regina XXL x2; fantasia M x3; margarita S x1"
                  << std::endl;
    }
    return 0;
}

void CommandInterpreter::run()
{
    std::string line;

    std::cout << "Plazza Pizza Reception - Ready to take orders!" << std::endl;
    std::cout << "Commands: [pizza orders], status, quit/exit" << std::endl;
    while (std::cout << "> ", std::getline(std::cin, line)) {
        if (line != "" && runCommand(line) == 1)
            break;
    }
}