//
// Created by mwypych on 28/05/18.
//
#include <string>
#include <memory>
#include <crow_all.h>
#include <Student.h>

using ::std::string;
using ::std::unique_ptr;
using ::crow::json::rvalue;

const unsigned long Student::UNKNOWN_ID = 0;

Student::Student(unsigned int id_,
                 const string &first_name_,
                 const string &last_name_,
                 const string &program_,
                 int age_,
                 const string &pesel_)
    : id_(id_), first_name_(first_name_), last_name_(last_name_), program_(program_), age_(age_), pesel_(pesel_) {}

Student::operator crow::json::wvalue() const {
  crow::json::wvalue to_return;
  to_return["id"] = id_;
  to_return["first_name"] = first_name_;
  to_return["last_name"] = last_name_;
  to_return["program"] = program_;
  to_return["age"] = age_;
  to_return["pesel"] = pesel_;
  return to_return;
}

Student Student::StudentFromJson(const rvalue &x) {
  unsigned int id;
  if (!x.has("id") || x["id"].u() == 0) {
    id = Student::UNKNOWN_ID;
  } else {
    id = x["id"].u();
  }
  string first_name = x["first_name"].s();
  string last_name = x["last_name"].s();
  string program = x["program"].s();
  int age = static_cast<int>(x["age"]);
  string pesel = x["pesel"].s();
  return {id, first_name, last_name, program, age, pesel};
}
