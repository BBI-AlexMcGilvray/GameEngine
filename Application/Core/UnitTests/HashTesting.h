#pragma once

void TestHashes();

template <typename T>
void PrintBits(T&& t)
{
	int numBytes = sizeof(t);

	// this should be redone once serialization stuff is working
	Ptr<const char> typeBytes = reinterpret_cast<Ptr<const char>>(&t);

	std::cout << "Real Data: " << t << ", Memory Data: ";
	for (int i = 0; i < numBytes; i++)
	{
		int bitsInChar = sizeof(char) * 8;

		for (int j = bitsInChar - 1; j >= 0; j--)
		{
			std::cout << ((typeBytes[j] >> j) & 1);
		}
	}
	std::cout << std::endl;
}