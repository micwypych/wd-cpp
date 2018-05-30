#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "crow_all.h"

#include <domain/Student.h>
#include <infrastructure/IdGenerator.h>
#include <infrastructure/IncrementalConcurrentIdGenerator.h>
#include <infrastructure/StudentController.h>

using namespace std;
using namespace crow;

void LinkStudentResourceToStudentControllerAndServer(SimpleApp *server, StudentController *students) {
  SimpleApp &app = *server;
  CROW_GET(app, "/api/student")
      ([students]() {
        return students->AllStudents();
      });

  CROW_POST(app, "/api/student")
      ([students](const request &req) {
        return students->CreateStudent(req);
      });

  CROW_POST(app, "/api/student/<uint>")
      ([students](const request &req, unsigned int id) {
        return students->UpdateStudent(req, id);
      });

  CROW_DELETE(app, "/api/student/<uint>")
      ([students](unsigned int id) {
        return students->DeleteStudent(id);
      });

  CROW_GET(app, "/api/student/<uint>")
      ([students](unsigned int id) {
        return students->SingleStudent(id);
      });
}

void RunServer() {
  //FIXME concurrent access!
  std::vector<Student> students{{102314, "Alojzy", "Motyka", "informatyka", 22, "00000000000"},
                                {564321, "Krzysztof", "Mallory", "astronomia", 19, "00000000000"}};

  unique_ptr<IdGenerator> generator = make_unique<IncrementalConcurrentIdGenerator>(100);

  SimpleApp app;
  CROW_GET(app, "/api/hello/<int>")
      ([](int count) {
        if (count > 100)
          return crow::response(400);
        ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
      });

  CROW_GET(app, "/")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("index.html");
      });

  CROW_GET(app, "/object_view.html")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("object_view.html");
      });

  CROW_GET(app, "/object_view_directive.js")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("object_view_directive.js");
      });

  CROW_GET(app, "/create_student.html")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("create_student.html");
      });

  CROW_GET(app, "/create_object.html")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("create_object.html");
      });

  CROW_GET(app, "/menu.html")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("menu.html");
      });

  CROW_GET(app, "/timetable.html")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("timetable.html");
      });

  CROW_GET(app, "/assets/timetable.js")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("assets/timetable.js");
      });

  CROW_GET(app, "/assets/timetablejs.css")
      ([]() {
        mustache::context ctx;
        return mustache::load_text("assets/timetablejs.css");
      });

  unique_ptr<IdGenerator> ids = make_unique<IncrementalConcurrentIdGenerator>(1000);
  unique_ptr<StudentRepository> repository = make_unique<StudentRepository>(std::move(ids));
  unique_ptr<StudentController> controller = make_unique<StudentController>(std::move(repository));

  LinkStudentResourceToStudentControllerAndServer(&app, controller.get());

  logger::setLogLevel(LogLevel::Debug);
  //THIS LINE RUNS INFINITE LOOP THEREFORE ALL unique_ptr ARE ALIVE
  app.port(9876).multithreaded().run();

}
