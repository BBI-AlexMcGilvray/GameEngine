#include "Core/UnitTests/HashTesting.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/MapDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IOUtils.h"
#include <iostream>

using namespace Core;
using namespace Core::IO;

void TestHashes()
{
  std::string filePath = GetCWD() + "/DataManagement/Headers/";

  {
    File AllWords(FilePath{ filePath, "EnglishWords.txt" }, std::ios::in);
    AllWords.Open();

    File HashedWords(FilePath{ filePath, "HashedEnglishWords.txt" }, std::ios::out);
    HashedWords.Open();
    HashedWords.Clear();

    uint wordCount = 0;

    /*
		NOTE: there is an issue with the below, occasionally prints out doubles, and also has a random single number near the bottom of the file
		*/

    std::string word;
    while (AllWords.Read(word)) {
      AllWords.MoveToNextLine();

      auto start = std::chrono::high_resolution_clock::now();

      Hash hashedWord = HashValue(word);

      auto end = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> elapsed = (end - start);
      double dt = elapsed.count();

      HashedWords.Write(word, " ", uint(hashedWord), " ", dt);
      HashedWords.CreateNewLine();

      wordCount++;
    }
    std::cout << "Done hashing words" << std::endl;
    HashedWords.SetPermissions(std::ios::in);
    HashedWords.GoToPosition(0);

    double wordAverageTime = 0;
    uint numWordCollisions = 0;

    std::string wordThatWasHashed;
    uint hashedWord;
    double time;
    StreamPos wordPosition = 0;

    Map<uint, List<std::string>> hashWordMapping;

    while (HashedWords.Read(wordThatWasHashed, hashedWord, time)) {
      // use time to keep finding average
      wordAverageTime += time;

      hashWordMapping[hashedWord].push_back(wordThatWasHashed);
    }
    wordAverageTime /= wordCount;

    auto factorial = [](int i) {
      int result = i;
      while (i > 1) {
        result *= --i;
      }

      return result;
    };

    for (auto key : hashWordMapping) {
      if (hashWordMapping[key.first].size() > 1) {
        numWordCollisions += factorial(static_cast<int>(hashWordMapping[key.first].size()) - 1);

        std::cout << "The following words collided: ";
        for (auto word : hashWordMapping[key.first]) {
          std::cout << word << " - ";
        }
        std::cout << std::endl;
      }
    }

    // return result (# collisions and average time)
    std::cout << "Collisions: " << numWordCollisions << ", Average Time: " << wordAverageTime << std::endl;
  }

  {
    // do the same with all numbers in uint
    File HashedUints(FilePath{ filePath, "HashedUints.txt" }, std::ios::out);
    HashedUints.Open();
    HashedUints.Clear();

    int upToNum = 1000000;

    for (int i = 0; i < upToNum; i++) {
      auto start = std::chrono::high_resolution_clock::now();

      Hash hashedUint = HashValue(i);

      auto end = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> elapsed = (end - start);
      double dt = elapsed.count();

      HashedUints.Write(i, " ", uint(hashedUint), " ", dt);
      HashedUints.CreateNewLine();
    }
    std::cout << "Done hashing ints" << std::endl;
    HashedUints.SetPermissions(std::ios::in);
    HashedUints.GoToPosition(0);

    double uintAverageTime = 0;
    uint numUintCollisions = 0;

    int intThatWasHashed;
    uint hashedUint;
    double time;
    StreamPos uintPosition = 0;

    Map<uint, List<int>> hashUintMapping;

    while (HashedUints.Read(intThatWasHashed, hashedUint, time)) {
      // use time to keep finding average
      uintAverageTime += time;

      hashUintMapping[hashedUint].push_back(intThatWasHashed);
    }
    uintAverageTime /= upToNum;

    auto factorial = [](int i) {
      int result = i;
      while (i > 1) {
        result *= --i;
      }

      return result;
    };

    for (auto key : hashUintMapping) {
      if (hashUintMapping[key.first].size() > 1) {
        numUintCollisions += factorial(static_cast<int>(hashUintMapping[key.first].size()) - 1);

        std::cout << "The following numbers collided: ";
        for (auto word : hashUintMapping[key.first]) {
          std::cout << word << " - ";
        }
        std::cout << std::endl;
      }
    }

    // return result (# collisions and average time)
    std::cout << "Collisions: " << numUintCollisions << ", Average Time: " << uintAverageTime << std::endl;
  }
}