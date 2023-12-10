#pragma once
#include "Wrapper.h"

class Engine {
private:
	std::unordered_map<std::string, std::function<int (std::unordered_map<std::string, int>)>> list;

public:
	template <typename ClassType, typename... Args>
	void register_command(Wrapper<ClassType, Args...>* wrapper, std::string command_name) {
		list[command_name] = *wrapper;
	}

	int execute(std::string command_name, std::unordered_map<std::string, int> arguments) {
		return list[command_name](std::move(arguments));
	}
};