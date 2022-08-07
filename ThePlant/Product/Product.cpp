#include "Product/Headers/ProductManager.h"

int main(int argc, char* argv[])
{
	auto productManager = Product::ProductManager();
	productManager.run();

	return 0;
}