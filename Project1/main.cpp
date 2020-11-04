#include "Window.h"
#include <iostream>

int main() {
	Window app;

	if (app.init()) {
		while (app.isRun()) {
			app.broadcast();
		}
	}

	return 0;
}