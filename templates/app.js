angular.module('wd-students', ['ngResource', 'ngRoute'])
    .config(['$routeProvider', function ($routerProvider) {
        $routerProvider.when('/', {
            templateUrl: 'object_view_widget.html',
            controller: 'StudentCtrl',
            controllerAs: 'ctrl'
        }).when('/student', {
            templateUrl: 'object_view_widget.html',
            controller: 'StudentCtrl',
            controllerAs: 'ctrl'
        }).when('/teacher', {
            templateUrl: 'object_view_widget.html',
            controller: 'TeacherCtrl',
            controllerAs: 'ctrl'
        }).when('/building', {
            templateUrl: 'object_view_widget.html',
            controller: 'BuildingCtrl',
            controllerAs: 'ctrl'
        }).when('/room', {
            templateUrl: 'object_view_widget.html',
            controller: 'RoomCtrl',
            controllerAs: 'ctrl'
        }).when('/program', {
            templateUrl: 'object_view_widget.html',
            controller: 'ProgramCtrl',
            controllerAs: 'ctrl'
        }).when('/course', {
            templateUrl: 'object_view_widget.html',
            controller: 'CourseCtrl',
            controllerAs: 'ctrl'
        }).when('/timetable', {
            templateUrl: 'timetable_widget.html',
            controller: 'TimeTableCtrl',
            controllerAs: 'ctrl'
        }).otherwise({redirectTo: '/'});
    }])
    .controller('StudentCtrl', ['StudentService', function (srv) {
        var self = this;
        self.pageName = 'Panel Studentów';
        self.columnHeaders = ['#', 'Imię', 'Nazwisko', 'Kierunek', 'Wiek', 'PESEL'];
        self.fieldNamesButId = ['first_name', 'last_name', 'program', 'age', 'pesel'];
        self.Service = srv;
    }])
    .controller('TeacherCtrl', ['TeacherService', function (srv) {
        var self = this;
        self.pageName = 'Panel Nauczycieli Akademickich';
        self.columnHeaders = ['#', 'Imię', 'Nazwisko', ['Prowadzone kursy']];
        self.fieldNamesButId = ['first_name', 'last_name', 'courses'];
        self.Service = srv;
    }])
    .controller('BuildingCtrl', ['BuildingService', function (srv) {
        var self = this;
        self.pageName = 'Panel Budynków i Sal';
        self.columnHeaders = ['#', 'Nazwa Budynku', ['Pomieszczenia']];
        self.fieldNamesButId = ['name', 'rooms'];
        self.Service = srv;
    }])
    .controller('RoomCtrl', ['RoomService', function (srv) {
        var self = this;
        self.pageName = 'Panel Sal';
        self.columnHeaders = ['#', 'Room Name', 'Building', 'Type'];
        self.fieldNamesButId = ['name', 'building', 'type'];
        self.Service = srv;
    }])
    .controller('ProgramCtrl', ['ProgramService', function (srv) {
        var self = this;
        self.pageName = 'Panel Programów Studiów';
        self.columnHeaders = ['#', 'Program', 'Semester', ['Courses']];
        self.fieldNamesButId = ['program', 'semester', 'courses'];
        self.Service = srv;
    }])
    .controller('CourseCtrl', ['CourseService', function (srv) {
        var self = this;
        self.pageName = 'Panel Oferowanych Kursów';
        self.columnHeaders = ['#', 'Course Name', 'ECTS', 'Teaching Language', 'Teacher\'s Name and Surname', 'Program', 'Semester', 'Room'];
        self.fieldNamesButId = ['name', 'ects', 'teaching_language', 'teachers_name_surname', 'program', 'semester', 'room'];
        self.Service = srv;
    }])
    .controller('TimeTableCtrl', ['TimeTableItemService', 'TimeTableLocationService', function (Item, Location) {
        var self = this;
        self.mod = 'Hello World!';
        self.locations = [];
        self.dayTimeTable = [];
        var forEachTimeTableExecute = function (foo) {
            for (var i = 0; i < self.dayTimeTable.length; i++) {
                foo(self.dayTimeTable[i], i);
            }
        };
        var resetTimeTable = function () {
            for (var i = 0; i < 5; i++) {
                self.dayTimeTable[i] = new Timetable();
            }
        };
        var fetchLocations = function () {
            //self.locations = Location.query();
            self.locations = ['Loc1', 'Loc2', 'Loc3'];
            forEachTimeTableExecute(function (t, i) {
                t.addLocations(self.locations);
            });
        };
        var addEventsToTimeTable = function (timeTable, events) {
            for (var i = 0; i < events.length; i++) {
                var item = events[i];
                timeTable.addEvent(item.eventname, item.location, new Date(item.startdate), new Date(item.enddate), item.url);
            }
        };
        var fetchTimeTableItems = function () {
            //var items = TimeTableItem.query();
            var items = [{
                eventname: 'Event1',
                location: 'Loc2',
                startdate: '2018-05-23T10:00:00Z',
                enddate: '2018-05-23T12:00:00Z',
                url: '/timetable/item/100'
            },
                {
                    eventname: 'Event2',
                    location: 'Loc1',
                    startdate: '2018-05-23T10:00:00Z',
                    enddate: '2018-05-23T12:00:00Z',
                    url: '/timetable/item/101'
                },
                {
                    eventname: 'Event3',
                    location: 'Loc3',
                    startdate: '2018-05-16T12:00:00Z',
                    enddate: '2018-05-16T14:00:00Z',
                    url: '/timetable/item/102'
                },
                {
                    eventname: 'Event4',
                    location: 'Loc3',
                    startdate: '2018-05-16T10:00:00Z',
                    enddate: '2018-05-16T12:00:00Z',
                    url: '/timetable/item/103'
                }];
            var eventsPerDay = [items, [], [], items, []];
            forEachTimeTableExecute(function (timetable, i) {
                addEventsToTimeTable(timetable, eventsPerDay[i]);
            });
        };
        var renderTimeTable = function (timetable, placeholdername) {
            var renderer = new Timetable.Renderer(timetable);
            renderer.draw(placeholdername);
        };
        var renderTimeTables = function () {
            var days = ['#ttmonday', '#tttuesday', '#ttwednesday', '#ttthursday', '#ttfriday'];
            forEachTimeTableExecute(function (timetable, i) {
                renderTimeTable(timetable, days[i]);
            });
        };
        var fetchTimeTable = function () {
            resetTimeTable();
            fetchLocations();
            fetchTimeTableItems();
            renderTimeTables();
        };

        fetchTimeTable();
    }])
    .factory('StudentService', ['$resource', function ($resource) {
        return $resource('/api/student/:id', {id: '@id'});
    }])
    .factory('TeacherService', ['$resource', function ($resource) {
        return $resource('/api/teacher/:id', {id: '@id'});
    }])
    .factory('BuildingService', ['$resource', function ($resource) {
        return $resource('/api/building/:id', {id: '@id'});
    }])
    .factory('RoomService', ['$resource', function ($resource) {
        return $resource('/api/room/:id', {id: '@id'});
    }])
    .factory('ProgramService', ['$resource', function ($resource) {
        return $resource('/api/program/:id', {id: '@id'});
    }])
    .factory('CourseService', ['$resource', function ($resource) {
        return $resource('/api/course/:id', {id: '@id'});
    }])
    .factory('TimeTableItemService', ['$resource', function ($resource) {
        return $resource('/api/timetable/item/:id', {id: '@id'});
    }])
    .factory('TimeTableLocationService', ['$resource', function ($resource) {
        return $resource('/api/timetable/location/:id', {id: '@id'});
    }])
    .filter('AddEdited', [function () {
        return function (obj) {
            obj.edited = false;
            return obj;
        };
    }]);