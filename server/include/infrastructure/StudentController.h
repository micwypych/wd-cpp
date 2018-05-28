//
// Created by mwypych on 28/05/18.
//

#ifndef JIMP_EXERCISES_STUDENTCONTROLLER_H
#define JIMP_EXERCISES_STUDENTCONTROLLER_H
#include <memory>
#include "crow_all.h"
#include <infrastructure/IdGenerator.h>
#include <infrastructure/StudentRepository.h>

class StudentController {
 public:
  StudentController(std::unique_ptr<StudentRepository> repository);
  virtual ~StudentController() = default;
  virtual crow::response CreateStudent(const crow::request &req);
  virtual crow::response DeleteStudent(unsigned int id);
  virtual crow::response SingleStudent(unsigned int id);
  virtual crow::response UpdateStudent(const crow::request &req, unsigned int id);
  virtual crow::response AllStudents();

  static Student StudentFromJson(const crow::json::rvalue &x);
 private:
  std::unique_ptr<StudentRepository> repository_;
};

#endif //JIMP_EXERCISES_STUDENTCONTROLLER_H
