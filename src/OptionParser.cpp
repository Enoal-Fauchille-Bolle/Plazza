/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Option Parser
*/

#include "OptionParser.hpp"

/**
 * @brief Construct a new Option Parser:: Option Parser object
 *
 * This constructor parses the command line arguments and initializes
 * the member variables. It also checks for help flag and invalid arguments.
 *
 * @param ac The number of command line arguments
 * @param av The command line arguments
 */
OptionParser::OptionParser(int ac, char **av)
{
    if (ac < 2) {
        _errorMessage = "No arguments provided. Use -h or --help for usage information.";
        return;
    }
    if (std::string(av[1]) == "-h" || std::string(av[1]) == "--help") {
        _helpPage = true;
        return;
    }
    if (ac != 4) {
        _errorMessage = "Invalid number of arguments. Expected 3 arguments.";
        return;
    }
    validateArguments(ac, av);
}

void OptionParser::validateArguments(int ac, char **av)
{
    (void)ac;
    try {
        _multiplier = std::stod(av[1]);
        if (_multiplier <= 0) {
            _errorMessage = "Multiplier must be a positive number.";
            return;
        }
    } catch (const std::invalid_argument &) {
        _errorMessage = "Invalid argument: " + std::string(av[1]) + " (must be a positive double)";
        return;
    } catch (const std::out_of_range &) {
        _errorMessage = "Multiplier value is out of range.";
        return;
    }
    try {
        _cooks = std::stoi(av[2]);
        if (_cooks <= 0) {
            _errorMessage = "Number of cooks must be a positive integer.";
            return;
        }
    } catch (const std::invalid_argument &) {
        _errorMessage = "Invalid argument: " + std::string(av[2]) + " (must be a positive integer)";
        return;
    } catch (const std::out_of_range &) {
        _errorMessage = "Number of cooks is out of range.";
        return;
    }
    try {
        _restockDelay = std::stoi(av[3]);
        if (_restockDelay <= 0) {
            _errorMessage = "Restock delay must be a positive integer.";
            return;
        }
    } catch (const std::invalid_argument &) {
        _errorMessage = "Invalid argument: " + std::string(av[3]) + " (must be a positive integer)";
        return;
    } catch (const std::out_of_range &) {
        _errorMessage = "Restock delay is out of range.";
        return;
    }
}

/**
 * @brief Get the multiplier value
 *
 * @return double The multiplier value
 */
double OptionParser::getMultiplier() const
{
    return _multiplier;
}

/**
 * @brief Get the number of cooks
 *
 * @return int The number of cooks
 */
int OptionParser::getCooks() const
{
    return _cooks;
}

/**
 * @brief Get the restock delay
 *
 * @return int The restock delay
 */
int OptionParser::getRestockDelay() const
{
    return _restockDelay;
}

/**
 * @brief Check if the help page is requested
 *
 * @return true If help page is requested
 * @return false If help page is not requested
 */
bool OptionParser::isHelpPage() const
{
    return _helpPage;
}

/**
 * @brief Check if there is an error in the arguments
 *
 * @return true If there is an error
 * @return false If there is no error
 */
bool OptionParser::isError() const
{
    return !_errorMessage.empty();
}

/**
 * @brief Get the error message
 *
 * @return std::string The error message if any
 */
std::string OptionParser::getErrorMessage() const
{
    return _errorMessage;
}

/**
 * @brief Display the help page
 *
 * This function prints the usage information and the description of each
 * argument.
 */
void OptionParser::displayHelpPage() const
{
    std::cout << "Usage: ./plazza <multiplier> <cooks> <restock_delay>"
              << std::endl;
    std::cout << "\tMultiplier: The multiplier for the pizza size."
              << std::endl;
    std::cout << "\tCooks: The number of cooks to use." << std::endl;
    std::cout << "\tRestock Delay: The delay for restocking ingredients."
              << std::endl;
}
