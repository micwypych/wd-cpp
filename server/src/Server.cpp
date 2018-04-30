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

void RunServer() {
  //FIXME concurrent access!
  std::vector<Student> students{{102314, "Alojzy", "Motyka", "informatyka", 22, "00000000000"},
                                {564321, "Krzysztof", "Mallory", "astronomia", 19, "00000000000"}};

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
      ([&students]() {
        json::wvalue x;
        x = students;
        std::string json_message = json::dump(x);
        CROW_LOG_INFO << " - MESSAGE: " << json_message;
        return x;
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