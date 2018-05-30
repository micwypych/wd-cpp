//
// Created by mwypych on 28/05/18.
//
#include <utility>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include <domain/Student.h>
#include <infrastructure/IdGenerator.h>
#include <infrastructure/StudentRepository.h>

using ::std::move;
using ::std::transform;
using ::std::to_string;
using ::std::invalid_argument;
using ::std::runtime_error;
using ::std::reference_wrapper;
using ::std::vector;
using ::std::experimental::make_optional;

StudentRepository::StudentRepository(std::unique_ptr<IdGenerator> id_generator)
    : id_gen_{move(id_generator)},
      students_{} {}

void StudentRepository::Insert(const Student &student) {
  if (student.Id() != Student::UNKNOWN_ID) {
    throw invalid_argument{"When inserting new Student into repository its id shouldn't be set!"};
  }
  StudentId new_id = NextId();
  //FIXME: concurrent access - not safe!
  auto hint = students_.find(new_id);
  Student
      new_student{new_id, student.FirstName(), student.LastName(), student.Program(), student.Age(), student.Pesel()};
  students_.emplace_hint(hint, new_id, move(new_student));
}

void StudentRepository::Update(unsigned int id, const Student &student) {
  if (student.Id() != id) {
    throw invalid_argument{"One cannot modify id of the updated student!"};
  }
  //FIXME: concurrent access - not safe!
  auto found = students_.find(id);
  if (found != students_.end()) {
    Student &to_update = found->second;
    to_update = student;
  } else {
    throw runtime_error{"There is no Student in the repository with id " + to_string(id)};
  }
}

StudentRepository::OptionalStudent StudentRepository::FindById(StudentRepository::StudentId id) const {
  //FIXME: concurrent access - not safe!
  auto found = students_.find(id);
  if (found != students_.end()) {
    return make_optional(found->second);
  } else {
    return {};
  }
}

StudentRepository::OptionalMutableStudent StudentRepository::FindById(StudentRepository::StudentId id) {
  //FIXME: concurrent access - not safe!
  auto found = students_.find(id);
  if (found != students_.end()) {
    Student &to_return = found->second;
    return make_optional<reference_wrapper<Student>>(to_return);
  } else {
    return {};
  }
}

void StudentRepository::Delete(StudentRepository::StudentId id) {
  if (id == Student::UNKNOWN_ID) {
    throw invalid_argument{"When deleting Student from repository its id should be set!"};
  }
  //FIXME: concurrent access - not safe!
  auto found = students_.find(id);
  if (found != students_.end()) {
    students_.erase(found);
  } else {
    throw runtime_error{"There is no Student in the repository with id " + to_string(id)};
  }
}

std::vector<Student> StudentRepository::All() const {
  //FIXME: concurrent access - not safe!
  vector<Student> response{};
  response.reserve(students_.size());
  transform(students_.cbegin(), students_.cend(), back_inserter(response), [](const auto &p) { return p.second; });
  return response;
}

StudentRepository::StudentId StudentRepository::NextId() const {
  return id_gen_->NextId();
}