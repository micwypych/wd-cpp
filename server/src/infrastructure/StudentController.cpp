//
// Created by mwypych on 28/05/18.
//
#include <utility>
#include <memory>
#include <crow_all.h>
#include <domain/Student.h>
#include <infrastructure/StudentRepository.h>
#include <infrastructure/StudentController.h>

namespace json = ::crow::json;

using crow::request;
using crow::response;
using std::move;

StudentController::StudentController(std::unique_ptr<StudentRepository> repository)
    : repository_{move(repository)} {}

crow::response StudentController::CreateStudent(const request &req) {
  auto x = json::load(req.body);
  if (!x)
    return response(400);
  CROW_LOG_INFO << " - MESSAGE: " << x;
  Student s = Student::StudentFromJson(x);
  repository_->Insert(s);
  return response(204);
}

crow::response StudentController::DeleteStudent(unsigned int id) {
  auto found = repository_->FindById(id);
  if (found) {
    repository_->Delete(id);
    CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was found";
    return response(204);
  } else {
    CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was not found";
    return response(404);
  }
}

crow::response StudentController::SingleStudent(unsigned int id) {
  auto found = repository_->FindById(id);
  if (found) {
    json::wvalue student;
    student = static_cast<Student &>(*found);
    CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was found";
    return response(student);
  } else {
    CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was not found";
    return response(404);
  }
}

crow::response StudentController::UpdateStudent(const crow::request &req, unsigned int id) {
  auto x = json::load(req.body);
  if (!x)
    return response(400);
  CROW_LOG_INFO << " - MESSAGE: " << x;
  Student s = Student::StudentFromJson(x);
  if (repository_->FindById(id)) {
    repository_->Update(id, s);
    CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was found";
    return response(204);
  } else {
    CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was not found";
    return response(404);
  }
}

crow::response StudentController::AllStudents() {
  json::wvalue x;
  x = repository_->All();
  std::string json_message = json::dump(x);
  CROW_LOG_INFO << " - MESSAGE: " << json_message;
  return response(x);
}