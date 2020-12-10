#pragma once
#include <chrono>
#include <string>

class fps_calculator {

private:
	std::chrono::time_point<std::chrono::system_clock> tp1;
	std::chrono::time_point<std::chrono::system_clock> tp2;

public:
	fps_calculator();
	std::string get_fps();
};