#pragma once
#include "Wrapper.h"

class Engine {
private:
	std::unordered_map<std::string, std::function<int (std::unordered_map<std::string, int>)>> commands_list;

public:
	template <typename ClassType, typename... Args>
	void register_command(Wrapper<ClassType, Args...>* wrapper, std::string command_name) {
		if (commands_list.find(command_name) != commands_list.end())
			throw std::runtime_error("Command already exsits: " + command_name);
		commands_list[command_name] = *wrapper;
	}

	int execute(std::string command_name, std::unordered_map<std::string, int> arguments) {
		if (commands_list.find(command_name) == commands_list.end())
			throw std::runtime_error("Command wasn`t found: " + command_name);
		return commands_list[command_name](std::move(arguments));
	}
};