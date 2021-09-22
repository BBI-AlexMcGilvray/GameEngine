#include "Product/Headers/ProductManager.h"

int main(int argc, char* argv[])
{
    // should be very similar to Pipeline.cpp in how it is handled, but with a custom application
	auto productManager = Product::ProductManager();
	productManager.run();

	return 0;
}