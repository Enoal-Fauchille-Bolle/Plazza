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

    // Check default pizza types
    bool isDefault = (lowerType == "regina" || lowerType == "margarita" ||
                      lowerType == "americana" || lowerType == "fantasia");

    // Check custom pizza types
    if (!isDefault) {
        // TODO: Replace with actual custom pizza storage
        // return customPizzas.find(lowerType) != customPizzas.end();
    }

    return isDefault;
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

bool CommandInterpreter::isValidCookingTime(const std::string& timeStr) const
{
    if (timeStr.empty()) {
        return false;
    }
    for (char c : timeStr) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    int time = std::stoi(timeStr);
    return (time > 0 && time <= 3600);  // Maximum 1 hour cooking time
}

bool CommandInterpreter::isValidIngredient(const std::string& ingredient) const
{
    // TODO: Check if ingredient is valid using the kitchen's ingredient list
    if (ingredient.empty()) {
        return false;
    }
    for (char c : ingredient) {
        if (!std::isalpha(c) && c != ' ' && c != '-') {
            return false;
        }
    }
    return true;
}

CustomPizza CommandInterpreter::parseCreateCommand(
    const std::string& createArgs)
{
    std::istringstream iss(createArgs);
    std::string name, cookingTimeStr;
    CustomPizza pizza;

    if (!(iss >> name >> cookingTimeStr)) {
        throw std::invalid_argument(
            "Create command requires at least name and cooking time");
    }
    if (!isValidIngredient(name)) {
        throw std::invalid_argument("Invalid pizza name: " + name);
    }
    if (!isValidCookingTime(cookingTimeStr)) {
        throw std::invalid_argument("Invalid cooking time: " + cookingTimeStr);
    }
    pizza.name = name;
    pizza.cookingTime = std::stoi(cookingTimeStr);
    std::string ingredient;
    while (iss >> ingredient) {
        if (!isValidIngredient(ingredient)) {
            throw std::invalid_argument("Invalid ingredient: " + ingredient);
        }
        pizza.ingredients.push_back(ingredient);
    }
    if (pizza.ingredients.empty())
        throw std::invalid_argument("Pizza must have at least one ingredient");
    return pizza;
}

void CommandInterpreter::handleCreateCommand(const std::string& createArgs)
{
    CustomPizza pizza = parseCreateCommand(createArgs);
    std::string lowerName = pizza.name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                   ::tolower);

    // TODO: Check if pizza already exists
    // if (customPizzas.find(lowerName) != customPizzas.end()) {
    //     std::cout << "Warning: Pizza '" << pizza.name
    //               << "' already exists. Overwriting..." << std::endl;
    // }

    // TODO: Add pizza to the kitchen's custom pizzas
    // customPizzas[lowerName] = pizza;

    std::cout << "Created pizza '" << pizza.name << "' with cooking time "
              << pizza.cookingTime << " seconds and ingredients: ";
    for (size_t i = 0; i < pizza.ingredients.size(); ++i) {
        std::cout << pizza.ingredients[i];
        if (i < pizza.ingredients.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void CommandInterpreter::displayUsageHelp() const
{
    std::cerr << "Usage: TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*" << std::endl;
    std::cerr << "  TYPE: regina, margarita, americana, fantasia (or custom "
                 "pizza names)"
              << std::endl;
    std::cerr << "  SIZE: S, M, L, XL, XXL" << std::endl;
    std::cerr << "  NUMBER: xN (where N is a positive integer)" << std::endl;
    std::cerr << "Example: regina XXL x2; fantasia M x3; margarita S x1"
              << std::endl;
    std::cerr << "Other commands:" << std::endl;
    std::cerr << "  status - Show kitchen status" << std::endl;
    std::cerr << "  create <name> <cooking_time> <ingredients>... - Create "
                 "custom pizza"
              << std::endl;
    std::cerr << "  quit/exit - Exit the program" << std::endl;
}

int CommandInterpreter::runCommand(std::string& line)
{
    std::vector<PizzaOrder> orders;

    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);
    if (line.empty()) {
        std::cerr << "Error: Empty command." << std::endl;
        displayUsageHelp();
        return 0;
    }
    if (line == "quit" || line == "exit") {
        return 1;
    }
    if (line == "status") {
        handleStatusCommand();
        return 0;
    }
    if (line.substr(0, 6) == "create") {
        std::string createArgs = line.substr(6);
        createArgs = trimWhitespace(createArgs);
        if (createArgs.empty()) {
            std::cerr << "Error: Create command requires arguments."
                      << std::endl;
            displayUsageHelp();
            return 0;
        }
        try {
            handleCreateCommand(createArgs);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            displayUsageHelp();
        }
        return 0;
    }
    try {
        orders = parsePizzaOrder(line);
        if (orders.empty()) {
            std::cerr << "Error: No valid pizza orders found." << std::endl;
            displayUsageHelp();
            return 0;
        }
        handlePizzaOrder(orders);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        displayUsageHelp();
    }
    return 0;
}

void CommandInterpreter::run()
{
    std::string line;

    std::cout << "Plazza Pizza Reception - Ready to take orders!" << std::endl;
    std::cout << "Commands: [pizza orders], status, quit/exit" << std::endl;
    while (std::cout << "> ", std::getline(std::cin, line)) {
        try {
            if (line != "" && runCommand(line) == 1)
                break;
        } catch (const std::exception& e) {
            std::cerr << "Fatal error: " << e.what() << std::endl;
            break;
        }
    }
}