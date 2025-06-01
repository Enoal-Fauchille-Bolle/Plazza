/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** CommandInterpreter
*/

#ifndef COMMANDINTERPRETER_HPP_
#define COMMANDINTERPRETER_HPP_

#include <string>
#include <vector>
#include <unordered_map>

struct PizzaOrder {
        std::string type;
        std::string size;
        int quantity;
};

struct CustomPizza {
        std::string name;
        int cookingTime;
        std::vector<std::string> ingredients;
};

class CommandInterpreter {
    public:
        CommandInterpreter() = default;

        int runCommand(std::string& line);
        void run();

    private:
        bool isValidPizzaType(const std::string& type) const;
        bool isValidPizzaSize(const std::string& size) const;
        bool isValidNumber(const std::string& number) const;
        std::vector<PizzaOrder> parsePizzaOrder(const std::string& orderStr);
        void handlePizzaOrder(const std::vector<PizzaOrder>& orders);
        void handleStatusCommand();
        void handleCreateCommand(const std::string& createArgs);
        void parseIndividualPizza(const std::string& pizzaCommand,
                                  std::string& type,
                                  std::string& size,
                                  std::string& number);
        PizzaOrder createPizzaOrder(const std::string& type,
                                    const std::string& size,
                                    const std::string& number);
        void validatePizzaComponents(const std::string& type,
                                     const std::string& size,
                                     const std::string& number);
        std::string trimWhitespace(const std::string& str);
        bool isValidCookingTime(const std::string& timeStr) const;
        bool isValidIngredient(const std::string& ingredient) const;
        CustomPizza parseCreateCommand(const std::string& createArgs);

        void displayUsageHelp() const;

        // TODO: Move these to a more appropriate place
        // std::unordered_map<std::string, CustomPizza> customPizzas;
};

#endif /* !COMMANDINTERPRETER_HPP_ */