#include "crow_all.h"
#include <iostream>
#include <string>

using namespace std;
using namespace crow;

class Student {
 public:
  Student(long long int id_,
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

 private:
  long long id_;
  string first_name_;
  string last_name_;
  string program_;
  int age_;
  string pesel_;
};

void RunServer() {
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
      ([]() {
        std::vector<Student> students{{10231234, "Alojzy", "Motyka", "informatyka", 22, "00000000000"},
                                      {56432321, "Krzysztof", "Mallory", "astronomia", 19, "00000000000"}};
        json::wvalue x;
        x = students;
        std::string json_message = json::dump(x);
        CROW_LOG_INFO << " - MESSAGE: " << json_message;
        return x;
      });

  app.port(9876).multithreaded().run();
}