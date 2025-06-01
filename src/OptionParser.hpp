/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Option Parser
*/

#ifndef OPTIONPARSER_HPP_
#define OPTIONPARSER_HPP_

#include <iostream>
#include <string>

class OptionParser {
    public:
        OptionParser(int ac, char **av);
        ~OptionParser() = default;

        double getMultiplier() const;
        int getCooks() const;
        int getRestockDelay() const;
        bool isHelpPage() const;
        bool isError() const;
        std::string getErrorMessage() const;

        void displayHelpPage() const;

    private:
        double _multiplier = 0.0;
        int _cooks = 0;
        int _restockDelay = 0;
        bool _helpPage = false;
        std::string _errorMessage = "";

        void validateArguments(int ac, char **av);
};

#endif /* !OPTIONPARSER_HPP_ */
