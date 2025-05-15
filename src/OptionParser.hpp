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
        double _multiplier;
        int _cooks;
        int _restockDelay;
        bool _helpPage = false;
        std::string _errorMessage = "";

};

#endif /* !OPTIONPARSER_HPP_ */
