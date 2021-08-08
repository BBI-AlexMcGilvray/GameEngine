#include "Pipeline/Headers/ApplicationManager.h"

using namespace Application;

int main(int argc, char* argv[])
{
	auto AppManager = ApplicationManager::Application();
	AppManager->Run();

	return 0;
}