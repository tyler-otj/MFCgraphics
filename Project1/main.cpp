#include "gameWindow.h"

//void HideConsole() {
//	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
//}
//
//int main() {
//	HideConsole();
//	gameWindow app;
//
//	while (app.isRun()) {
//		app.broadcast();
//	}
//
//	return 0;
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR scCmdLine, int iCmdShow) {
	gameWindow app;

	while (app.isRun()) {
		app.broadcast();
	}
}