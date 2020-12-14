#include "fps_calculator.h"
#include <sstream>
#include <iomanip>

fps_calculator::fps_calculator() {
	get_fps();
}

std::string fps_calculator::get_fps() {
	tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = tp2 - tp1;
	tp1 = tp2;
	float const fElapsedTime = elapsedTime.count();
	float const fps = 1.0f / fElapsedTime;

	//TODO: idk if we really need ss for this..
	std::ostringstream ss;
	ss << std::setprecision(4) << fps;

	return ss.str();
}