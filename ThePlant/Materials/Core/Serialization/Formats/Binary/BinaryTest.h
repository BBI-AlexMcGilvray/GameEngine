#pragma once

#include "Binary.h"
#include "Core/Reflection/Reflectable.h"
#include "Core/Serialization/Serialization.h"
#include <iostream>

struct Person
{
  Person()
    : name("no name"), age(0)
  {}

  Person(std::string name, int age)
    : name(name), age(age)
  {}

  Person(const Person &other)
  {
    name = other.name;
    age = other.age;
  }

  Person &operator=(const Person &other)
  {
    name = other.name;
    age = other.age;
    return *this;
  }

private:
  REFLECTABLE(
    (std::string)name,
    (int)age)
};

struct People
{
  People()
  {}

  People(std::vector<Person> people)
    : people(people)
  {}

  People(const People &other)
    : people(other.people)
  {}

  People &operator=(const People &other)
  {
    people = other.people;
    return *this;
  }

  void AddPerson(Person person)
  {
    people.push_back(person);
  }

  std::vector<Person> &GetPeople()
  {
    return people;
  }

private:
  REFLECTABLE(
    (std::vector<Person>)people)
};

void TestBinary()
{
  Serialization::Format::Binary resultantBinary;
  std::cout << "created Binary object" << '\n';

  std::cout << "created test binary object" << '\n';
  Serialization::Format::Binary testBinary = Serialize<Serialization::Format::Binary>(1);
  std::cout << "created test binary object" << '\n';

  SerializeTo(resultantBinary, 1);
  std::cout << "serialized int" << '\n';
  SerializeTo(resultantBinary, 1.0f);
  std::cout << "serialized float" << '\n';
  SerializeTo(resultantBinary, 1.0);
  std::cout << "serialized double" << '\n';
  SerializeTo(resultantBinary, std::string("a"));
  std::cout << "serialized string" << '\n';
  SerializeTo(resultantBinary, true);
  std::cout << "serialized bool" << '\n';

  Person p("Tom", 82);
  SerializeTo(resultantBinary, p);
  std::cout << "serialized Person" << '\n';

  std::vector<int> v = std::vector<int>(10);
  for (int i = 0; i < 10; i++) {
    v[i] = i;
  }
  SerializeTo(resultantBinary, v);
  std::cout << "serialized vector" << '\n';

  std::vector<Person> people = std::vector<Person>();
  for (int i = 0; i < 10; i++) {
    people.push_back(Person(std::string("person ") + std::to_string(i), i));
  }
  People ppl(people);
  SerializeTo(resultantBinary, ppl);
  std::cout << "serialized People" << '\n';

  int testInt = Deserialize<int>(testBinary);
  std::cout << "test int deserialized: " << (testInt == 1) << '\n';

  int deserializedInt;
  DeserializeTo(deserializedInt, resultantBinary);
  std::cout << "int deserialized: " << (deserializedInt == 1) << '\n';
  float deserializedFloat;
  DeserializeTo(deserializedFloat, resultantBinary);
  std::cout << "float deserialized: " << (deserializedFloat == 1.0f) << '\n';
  double deserializedDouble;
  DeserializeTo(deserializedDouble, resultantBinary);
  std::cout << "double deserialized: " << (deserializedDouble == 1.0) << '\n';
  std::string deserializedString;
  DeserializeTo(deserializedString, resultantBinary);
  std::cout << "string deserialized: " << (deserializedString == "a") << '\n';
  bool deserializedBool;
  DeserializeTo(deserializedBool, resultantBinary);
  std::cout << "bool deserialized: " << (deserializedBool == true) << '\n';

  Person deserializedPerson;
  DeserializeTo(deserializedPerson, resultantBinary);
  std::cout << "person deserialized" << '\n';
  print_fields(deserializedPerson);

  std::vector<int> deserializedVector;
  DeserializeTo(deserializedVector, resultantBinary);
  std::cout << "vector deserialized" << '\n';
  for (int i = 0; i < deserializedVector.size(); i++) {
    std::cout << "deserialized vector[" << i << "] " << deserializedVector[i] << '\n';
  }

  People deserializedPeople;
  DeserializeTo(deserializedPeople, resultantBinary);
  std::cout << "people deserialized" << '\n';
  for (Person &person : deserializedPeople.GetPeople()) {
    print_fields(person);
  }
}