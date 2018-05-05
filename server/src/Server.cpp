#include "crow_all.h"
#include <iostream>
#include <string>

using namespace std;
using namespace crow;

class Student {
 public:
  Student(unsigned int id_,
          const string &first_name_,
          const string &last_name_,
          const string &program_,
          int age_,
          const string &pesel_)
      : id_(id_), first_name_(first_name_), last_name_(last_name_), program_(program_), age_(age_), pesel_(pesel_) {}

  operator crow::json::wvalue() const {
    crow::json::wvalue to_return;
    to_return["id"] = id_;
    to_return["first_name"] = first_name_;
    to_return["last_name"] = last_name_;
    to_return["program"] = program_;
    to_return["age"] = age_;
    to_return["pesel"] = pesel_;
    return to_return;
  }
  unsigned int Id() const {
    return id_;
  }

 private:
  unsigned int id_;
  string first_name_;
  string last_name_;
  string program_;
  int age_;
  string pesel_;
};

class IdGenerator {
 public:
  virtual unsigned int NextId() =0;
};

class IncrementalIdGenerator : public IdGenerator {
 public:
  IncrementalIdGenerator(unsigned int current_value) : current_value_(current_value) {}
  unsigned int NextId() override {
    return current_value_++;
  }

 private:
  //FIXME change to atomic
  unsigned int current_value_;
};

Student StudentFromJson(unique_ptr<IdGenerator> &generator, const json::rvalue &x);

void RunServer() {
  //FIXME concurrent access!
  std::vector<Student> students{{102314, "Alojzy", "Motyka", "informatyka", 22, "00000000000"},
                                {564321, "Krzysztof", "Mallory", "astronomia", 19, "00000000000"}};

  unique_ptr<IdGenerator> generator = make_unique<IncrementalIdGenerator>(100);

  SimpleApp app;
  CROW_ROUTE(app, "/api/hello/<int>")
      ([](int count) {
        if (count > 100)
          return crow::response(400);
        ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
      });

  CROW_ROUTE(app, "/")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("index.html");
      });

  CROW_ROUTE(app, "/api/student")
      .methods("GET"_method, "POST"_method)
          ([&students, &generator](const request &req) {
            //TODO at this moment it is imposible to have two crow routes with different methods, I guess...
            //so this ugly solution has to suffice
            auto get_handler =
                [&students]() {
                  json::wvalue x;
                  x = students;
                  std::string json_message = json::dump(x);
                  CROW_LOG_INFO << " - MESSAGE: " << json_message;
                  return response(x);
                };
            auto post_handler = [&students, &generator](const request &req) {
              auto x = json::load(req.body);
              if (!x)
                return response(400);
              CROW_LOG_INFO << " - MESSAGE: " << x;
              Student s = StudentFromJson(generator, x);
              students.push_back(s);
              return response(204);
            };
            if (req.method == "GET"_method) {
              return get_handler();
            } else if (req.method == "POST"_method) {
              return post_handler(req);
            } else {
              return response(404);
            }
          });

  CROW_ROUTE(app, "/api/student/<uint>")
      .methods("DELETE"_method)
          ([&students](unsigned int id) {
            const auto it =
                find_if(students.begin(), students.end(), [id](const auto &student) { return student.Id() == id; });
            if (it != students.end()) {
              students.erase(it);
              CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was found";
              return response(204);
            } else {
              CROW_LOG_INFO << " - MESSAGE: student of id: " << id << " was not found";
              return response(404);
            }
          });

  app.port(9876).multithreaded().run();
}

Student StudentFromJson(unique_ptr<IdGenerator> &generator, const json::rvalue &x) {
  unsigned int id;
  if (!x.has("id") || x["id"].u() == 0) {
    id = generator->NextId();
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