# wd-cpp

[![Build Status](https://travis-ci.org/micwypych/wd-cpp.svg?branch=master)](https://travis-ci.org/micwypych/wd-cpp)

## C++ server (crow) and JS frontend

The project aim is to teach how to build a simple web application in C++ using MVC pattern. (why C++? you can ask... it is a very good question to ask :) The simple answer is because it is feasible to do so and the real reason is that this application was a part of programming 102 classes which was based on C++ language)

The project cosists of two parts. One is the frontend written in HTML, js, bootstrap, angularjs, karma, and jasmine and was meant to be fully provided and was intended to be ready-to-use without any modification (which, at the moment, is only partially true).
The second part is the backend that is intented to be developed into a server application supporting features implemented in the frontend. 

This simple application should support university managment. There are number of features expected to be implemented:
  * Students' data managment (create, remove, update, delete, list)
  * Academic teachers' data management
  * University buildings and rooms' data management
  * University teaching programs and courses' data management
  * [New schedule preparation algorithm](https://ai.ia.agh.edu.pl/wiki/pl:dydaktyka:jimp2:2017:labs:algorithm) (don't worry just a simple greedy algorithm is sufficient)
  
Because it is a part of introductory programming classes the problem is simplified to handle only data managment in the language itself and therefore:
  * there are no roles of the users (everything is available publically)
  * there is no authentication 
  * there is no permanent data storage implementation behind the repository layer (only in-memory repositories are intended to be implemented)
  * and so on...
  

## pre-requistes 
The most acurate description of pre-requistes to compile and run the app is [the travis.yml](.travis.yml) sections of before_install, install, and script. Which contain dash-enumerated lists of ubutu command line commands to install required software and run unit tests of application.

The code was only tested to run on the Ubuntu/Debian like system which are distribution of Linux system. The further your operating system is from Debian, probably, the more prolems you can encounter on that pristine territory of problems with runnig this code.

So you need to have installed on your machine:
  * git (to clone this repository)
  * g++ compiler
  * cmake 
  * libboost
  * yarn 
  * [CLion IDE](https://www.jetbrains.com/clion/) (you can try different IDE but CLion nicely itegrates with the cmake build system provided, google tests, and supports js code edition too. There is a free student license)
  * valgrind, cppcheck (nice to have too)
  
## how to run the code
First of all you have to clone this repository or fork it (third button above the code here) and then clone your forked repository (recommended). In case of this repositry you can clone it by typing the following command in your terminal window (if you had forked this repository just change my login to yours in the link below):
```
git clone https://github.com/micwypych/wd-cpp.git
```
then change the directory to the cloned one
```
cd wd-cpp
```
you can run **ls** to verfiy the catalogue stracture is like above.
Then go into the **template** directory and install all the js dependencies by:
```
cd template
yarn install
```
you can run the frontend tests to verfiy whether everything works as intended:
```
yarn test
```
to build the server go to the project directory create **build** directory and go there:
```
cd ..
mkdir build && cd build
```
prepare build script with cmake:
```
cmake ..
```
build app:
```
make server
```
to run app you have to once again go into your project directory (it is important because server searches for a local folder serving templated static files to be served from the server. And running from diferent directory ends up in server being unable to find any file) and type:
```
build/server/src/server
```
There should be printed log information on your command line then you can open web browser and go to the (http://localhost:9876)
If everythings works fine the browser should render text of "Wirtualny dziekanat 2.0" and the rest of the page.

## how to edit the code
Open CLion IDE. Hit the **File** then **open** and choose the directory of the project. Here it was **wd-cpp**.
Then click the target menu (to the left of the green triangle of the run button) and choose **edit configutaions...**.
Change the working directory of the **server** target to the project directory, Here it was **wd-cpp**, and click **apply**. Now you can run the server from your IDE. Because the port on which the server works is hard-coded to the 9876 value, please make sure there is only one instance of the application running. 


The code to be edited can be found in the following directories:
  * [server](server) - application main and server setup code: 
    * linking REST endpoints to the controller methods
    * initialisation of the controllers and repositories
  * [domain](server/src/domain) - classes representing the application data like Students, Teachers, and so on, that are important form the buisness perspective 
    * Student class
    * here you should probably put your code of Teacher, Building, Room, Course, Program, and so on classes...
  * [infrastructure](server/src/infrastructure) - classes representing the infrastructure required to run the code like controllers, repositories and so on
    * StudentController class
    * StudentRepository class
    * here you should probably put your code of TeacherController, TeacherRepository, and so on.



