//
// Created by mwypych on 28/05/18.
//

#ifndef JIMP_EXERCISES_STUDENTREPOSITORY_H
#define JIMP_EXERCISES_STUDENTREPOSITORY_H
#include <vector>
#include <experimental/optional>
#include <functional>
#include <Student.h>
#include <infrastructure/IdGenerator.h>

class StudentRepository {
 public:
  using OptionalMutableStudent = std::experimental::optional<std::reference_wrapper<Student>>;
  using OptionalStudent = std::experimental::optional<Student>;
  using StudentId = unsigned int;

  StudentRepository(std::unique_ptr<IdGenerator> id_generator);
  virtual ~StudentRepository() = default;
  virtual void Insert(const Student &student);
  virtual void Update(StudentId id, const Student &student);
  virtual OptionalStudent FindById(StudentId id) const;
  virtual OptionalMutableStudent FindById(StudentId id);
  virtual void Delete(StudentId id);
  virtual std::vector<Student> All() const;

  virtual StudentId NextId() const;

 private:
  std::unique_ptr<IdGenerator> id_gen_;
  std::map<StudentId, Student> students_;
};

#endif //JIMP_EXERCISES_STUDENTREPOSITORY_H
