#include <iostream>
#include "../include/tracey/tracey.hpp"

using json = nlohmann::json;

int main()
{
  json test =  {
    {"firstName","Aleksi"},
    {"lastName","Kääriäinen"},
    {"Department","Computer Sc."}};

   // Access the values, if missing a value, returns second parameter
   std::string fName = test.value("firstName", "No such field");
   std::string lName = test.value("lastName", "No such field");
   int sID = test.value("StudentID", 0);
   std::string dept = test.value("Department", "No such field");
   
   // Print the values
   std::cout << "First Name: " << fName << std::endl;
   std::cout << "Last Name: " << lName << std::endl;
   std::cout << "Student ID: " << sID << std::endl;
   std::cout << "Department: " << dept << std::endl;
           
   return 0;
}