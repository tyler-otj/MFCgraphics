#include "../amg_sdk/window/window.h"
#include <iostream>

int main() {
	window app;

	if (app.init()) {
		while (app.isRun()) {
			app.broadcast();
		}
	}

	return 0;
}