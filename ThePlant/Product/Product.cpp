#include "Product/Headers/ProductManager.h"

using namespace Application;

int main(int argc, char* argv[])
{
    // should be very similar to Pipeline.cpp in how it is handled, but with a custom application
	auto AppManager = ProductManager::Application();
	AppManager->Run();

	return 0;
}