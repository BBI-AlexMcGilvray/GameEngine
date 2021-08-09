#pragma once

#include "Core/Reflection/Reflectable.h"
#include "Core/Serialization/Serialization.h"
#include "JSON.h"
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

void TestJSON()
{
  Serialization::Format::JSON resultantJSON;
  std::cout << "created JSON object" << '\n';

  Serialization::Format::JSON testJSON = Serialize<Serialization::Format::JSON>(1, "test");

  SerializeTo(resultantJSON, 1, "int");
  std::cout << "serialized int" << '\n';
  SerializeTo(resultantJSON, 1.0f, "float");
  std::cout << "serialized float" << '\n';
  SerializeTo(resultantJSON, 1.0, "double");
  std::cout << "serialized double" << '\n';
  SerializeTo(resultantJSON, std::string("a"), "string");
  std::cout << "serialized string" << '\n';
  SerializeTo(resultantJSON, true, "bool");
  std::cout << "serialized bool" << '\n';

  Person p("Tom", 82);
  SerializeTo(resultantJSON, p, "person");
  std::cout << "serialized Person" << '\n';

  std::vector<int> v = std::vector<int>(10);
  for (int i = 0; i < 10; i++) {
    v[i] = i;
  }
  SerializeTo(resultantJSON, v, "vector");
  std::cout << "serialized vector" << '\n';

  std::vector<Person> people = std::vector<Person>();
  for (int i = 0; i < 10; i++) {
    people.push_back(Person(std::string("person ") + std::to_string(i), i));
  }
  People ppl(people);
  SerializeTo(resultantJSON, ppl, "people");
  std::cout << "serialized People" << '\n';

  std::cout << "built JSON:" << '\n'
            << resultantJSON.ToString(Serialization::Format::Style::Readable) << '\n';

  Serialization::Format::JSON parsedJSON;
  parsedJSON.Parse(resultantJSON.ToString(Serialization::Format::Style::Readable));
  //std::cout << "parsed JSON:" << '\n' << parsedJSON.ToString(Serialization::Format::Style::Readable) << '\n';

  std::cout << "built and parsed are equivalent: " << (resultantJSON.ToString(Serialization::Format::Style::Readable) == parsedJSON.ToString(Serialization::Format::Style::Readable)) << '\n';

  int testInt = Deserialize<int>(testJSON, "test");
  std::cout << "test int deserialized: " << (testInt == 1) << '\n';

  int deserializedInt;
  DeserializeTo(deserializedInt, resultantJSON, "int");
  std::cout << "int deserialized: " << (deserializedInt == 1) << '\n';
  float deserializedFloat;
  DeserializeTo(deserializedFloat, resultantJSON, "float");
  std::cout << "float deserialized: " << (deserializedFloat == 1.0f) << '\n';
  double deserializedDouble;
  DeserializeTo(deserializedDouble, resultantJSON, "double");
  std::cout << "double deserialized: " << (deserializedDouble == 1.0) << '\n';
  std::string deserializedString;
  DeserializeTo(deserializedString, resultantJSON, "string");
  std::cout << "string deserialized: " << (deserializedString == "a") << '\n';
  bool deserializedBool;
  DeserializeTo(deserializedBool, resultantJSON, "bool");
  std::cout << "bool deserialized: " << (deserializedBool == true) << '\n';

  Person deserializedPerson;
  DeserializeTo(deserializedPerson, resultantJSON, "person");
  print_fields(deserializedPerson);

  std::vector<int> deserializedVector;
  DeserializeTo(deserializedVector, resultantJSON, "vector");
  for (int i = 0; i < deserializedVector.size(); i++) {
    std::cout << "deserialized vector[" << i << "] " << deserializedVector[i] << '\n';
  }

  People deserializedPeople;
  DeserializeTo(deserializedPeople, resultantJSON, "people");
  for (Person &person : deserializedPeople.GetPeople()) {
    print_fields(person);
  }
}