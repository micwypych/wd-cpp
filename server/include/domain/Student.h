//
// Created by mwypych on 28/05/18.
//

#ifndef JIMP_EXERCISES_STUDENT_H
#define JIMP_EXERCISES_STUDENT_H
#include <string>
#include <memory>
#include <crow_all.h>

class Student {
 public:
  Student(unsigned int id_,
          const std::string &first_name_,
          const std::string &last_name_,
          const std::string &program_,
          int age_,
          const std::string &pesel_);

  operator crow::json::wvalue() const;

  unsigned int Id() const {
    return id_;
  }

  std::string FirstName() const {
    return first_name_;
  }

  std::string LastName() const {
    return last_name_;
  }

  std::string Program() const {
    return program_;
  }

  int Age() const {
    return age_;
  }

  std::string Pesel() const {
    return pesel_;
  }

  static const unsigned long UNKNOWN_ID;
  static Student StudentFromJson(const crow::json::rvalue &x);

 private:
  unsigned int id_;
  std::string first_name_;
  std::string last_name_;
  std::string program_;
  int age_;
  std::string pesel_;
};

#endif //JIMP_EXERCISES_STUDENT_H
