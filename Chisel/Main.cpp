#include <PCH/pch.h>
#include <Game/System/Application.h>


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Log::initialize();

	Application* app = new Application();
	if (app->init()) {
		app->update();
	}
	else {
		logError("Failed to init application");
	}
	delete app;
	return 0;
}