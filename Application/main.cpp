#include "ApplicationManagement\Headers\ApplicationManager.h"

using namespace Application;

int main(int argc, char* argv[])
{
	auto AppManager = ApplicationManager();
	AppManager.Run();

	return 0;
}