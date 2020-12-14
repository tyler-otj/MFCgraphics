#include "gameWindow.h"

int main() {
	gameWindow app;

	while (app.isRun()) {
		app.broadcast();
	}

	return 0;
}