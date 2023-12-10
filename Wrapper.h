#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>

template <typename ClassType, typename ... Args>
class Wrapper {
private:
	using MethodType = int (ClassType::*)(Args...);

	ClassType* instance;
	MethodType method;
	std::vector<std::string> argument_names;
	std::vector<int> arguments_values;

	template<std::size_t... Idx>
	int run_method(std::index_sequence<	Idx...>) {
		return (instance->*method)(arguments_values[Idx]...);
	}

public:
	Wrapper(ClassType* instance, MethodType method, std::unordered_map<std::string, int> arguments):instance(instance), method(method) {
		for (auto tmp : arguments) 
			argument_names.push_back(tmp.first);
	}
	int operator()(std::unordered_map<std::string, int> arguments_map) {
		for (const auto& argument_name : arguments_map) {
			if (arguments_map.find(argument_name.first) == arguments_map.end()) {
				throw std::runtime_error("Incorrect argument " + argument_name.first);
			}
			arguments_values.push_back(arguments_map[argument_name.first]);
		}
		return run_method(std::make_index_sequence<sizeof...(Args)>{});
	}
};