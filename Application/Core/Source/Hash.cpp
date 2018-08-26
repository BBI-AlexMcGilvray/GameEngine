#include "Core/Headers/Hash.h"

namespace Core
{
	Hash HashValue(uint u)
	{
		Hash newHash;

		newHash.H = u;

		return newHash;
	}

	void HashValue(uint u, Hash& existingHash)
	{
		existingHash.H += u;
	}

	Hash HashValue(String s)
	{
		Hash newHash;

		HashValue(s, newHash);

		return newHash;
	}

	void HashValue(String s, Hash& existingHash)
	{
		for (uint i = 0; i < s.length(); i++)
		{
			HashValue(s.c_str()[i], existingHash);
		}
	}

	Hash HashValue(char b)
	{
		Hash newHash;

		HashValue(b, newHash);

		return newHash;
	}

	void HashValue(char b, Hash& existingHash)
	{
		/*
			Shift value notes:
			            (58 000)          (500 000)
			shift | string collisions | int collisions
			  8   |        2          |      1157
			  4   |       38          |  24031746
			 12   |        4          |       384
			 11   |       16          |       192
			 17   |       26          |      2670
			 13   |        3          |      0

			salt value notes:
			            (116 000)          (500 000)
			salt | string collisions | int collisions
			 37   |        3          |       0
			 17   |        5          |       0
			 11   |        6          |       0
			 13   |        3          |       0

			 pepper value notes:
			 (116 000)          (500 000)
			 pepper | string collisions | int collisions
			 27   |        3          |       0
			127   |        6          |       0
			 67   |        8          |       0

			 General notes:
			 - Shift seems to have the greatest effect on collisions
			 - Average string speed: 117.388 nano seconds ( 1.17388 * 10^(-5) )
			 - Average integer speed: 52.8337 nano seconds ( 5.28337 * 10^(-7) )

			 For benchmarks for other algorithms: https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
		*/
		int shift = 13; // shift value should be within range [1, 31] (i.e. - do not lose information, and apply some form of shift)
		int nonShift = (32 - shift); // the rest of the bits are those that are not lost due to shifting

		int salt = 13; // can be any number, should be odd, ideally prime and not so large to lose much information
		int pepper = 27; // can be any number, should be odd, ideally prime

		uint saltedB = (b * salt);
		existingHash.H ^= (saltedB); // salt the byte, then modify hash with it

		existingHash.H += pepper; // salt the resulting hash (+ instead of * since * would cause overflow and lose data more often (this may not even be needed)

		uint lostBits = (existingHash.H << nonShift); // get the bits that would be lost by the shift

		existingHash.H >>= shift; // shift bits

		existingHash.H += lostBits; // add the missing bits back
	}

	// SEE HEADER
	/*
	char UnHashValue(Hash& currentHash, Hash& previousHash)
	{
		int shift = 7;
		int nonShift = (32 - shift);

		int salt = 37;
		int pepper = 27;

		uint aB = cH >> nonShift; // get the bits that were added to the front

		cH <<= shift; // shift

		cH += aB; // add bits to the end

		cH -= pepper;
		uint bI = (cH ^ pH);

		char b = (bI / salt);

		return b;
	}
	*/
}