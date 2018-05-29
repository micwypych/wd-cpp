/**
 * Created by mwypych on 29/05/18.
 */
angular.module('wd-students').directive('objectView', ['AddEditedFilter', function (AddEditedFilter) {
    return {
        templateUrl: 'object_view.html',
        restrict: 'AE',
        scope: {
            objectName: '=objectName',
            fieldNamesColumnHeaders: '=columnHeadersWithId',
            fieldNamesButIdToRetrieve: '=fieldNamesButId',
            objectService: '=objectService'
        },
        link: function ($scope, $element, $attrs) {
            var self = $scope;
            var Student = self.objectService;
            self.students = [];
            self.fieldNamesToRetrieve = ['id'].concat(self.fieldNamesButIdToRetrieve);
            self.newStudent = {};
            self.editedStudents = {};
            var fetchStudents = function () {
                self.students = Student.query();
                var len = self.students.length;
                for (var i = 0; i < len; i++) {
                    self.students[i] = AddEditedFilter(self.students[i]);
                }
            };
            var fetchOnlySingle = function (id) {
                var student = Student.get({id: id});
                console.log('downloaded student is: ' + angular.toJson(student));
                modifyStudentById(id, student);
            };
            var resetNewStudent = function () {
                self.newStudent = {};
            };
            var resetEditedStudent = function (id) {
                delete self.editedStudents[id];
            };
            var setEditedStudent = function (id, newValue) {
                var len = self.students.length;
                for (var i = 0; i < len; i++) {
                    if (self.students[i].id == id) {
                        self.students[i].edited = newValue;
                    }
                }
            };
            var getStudentById = function (id) {
                var len = self.students.length;
                for (var i = 0; i < len; i++) {
                    if (self.students[i].id == id) {
                        return self.students[i];
                    }
                }
                return {};
            };
            var modifyStudentById = function (id, student) {
                var len = self.students.length;
                for (var i = 0; i < len; i++) {
                    if (self.students[i].id == id) {
                        self.students[i] = student;
                        return;
                    }
                }
                self.students.append(student);
            };
            self.editStudent = function (id) {
                console.log('trying to edit student of id: ' + id);
                setEditedStudent(id, true);
                self.editedStudents[id] = getStudentById(id);
            };
            self.deleteStudent = function (student) {
                console.log('try to delete student of id: ' + student.id);
                Student.delete(student).$promise
                    .then(fetchStudents);
            };
            self.createStudent = function () {
                console.log('create new student: ' + self.newStudent);
                Student.save(self.newStudent).$promise
                    .then(fetchStudents)
                    .then(resetNewStudent);
            };
            self.modifyStudent = function (id) {
                console.log('change student: ' + angular.toJson(self.editedStudents[id]));
                Student.save({id: self.editedStudents[id].id}, self.editedStudents[id]).$promise
                    .then(function () {
                        setEditedStudent(id, false);
                    })
                    .then(function () {
                        fetchOnlySingle(id);
                    });
            };
            self.cancelEditionOf = function (id) {
                console.log('try to cancel edition of student of id: ' + id);
                resetEditedStudent(id);
                setEditedStudent(id, false);
            };
            self.cancelCreation = function () {
                console.log('try to cancel creation of new student');
                resetNewStudent();
            };

            fetchStudents();
        }
    }
}]);