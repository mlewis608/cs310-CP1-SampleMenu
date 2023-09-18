#include <iostream>
#include <fstream>
using namespace std;
#include <getopt.h>
#include <assert.h>
#include "Parser.h"

void do_one(string s1) {
   cout << "do_one(" << s1 << ")" << endl;
}

void do_two(string s1, string s2) {
   cout << "do_two(" << s1 << ", " << s2 << ")" << endl;
}

void do_three(string s1, string s2, int i) {
   cout << "do_three(" << s1 << ", " << s2 << ", " << i << ")" << endl;
}

bool accept_commands(istream &is, bool silent=false, bool echo=false) {
   string command;  
   string line;

   while (1) {
      if (!silent) {
         cout << endl << "Enter a command: " << endl;
         cout << "Choose from " << endl <<
            "   one <string>" << endl <<
            "   two <string> <string>" << endl << 
	    "   three <string> <string> <int>" << endl << 
            "   quit" << endl; 
         cout << ": ";
      }

      getline(is, line);
      if (echo) {
         cout << endl;
         cout << "======================================================" << 
		 endl;
         cout << line << endl;
         cout << "======================================================" << 
		 endl;
      }

      Parser p(line);
      if (p.getOperation().empty()) {
         if (is.fail())
            return false;
         continue;
      }

      if (p.getOperation() == "quit") {
         if (p.numArgs() > 0) 
            cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
         return true;
      }

      else if (p.getOperation() == "one") {
         if (p.numArgs() < 1) 
            cout << std::endl << "Can't operate with " << MISSING_ARGS << endl;
         else {
            if (p.numArgs() > 1) 
               cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
            do_one(p.getArg(1));
         }
      }
      else if (p.getOperation() == "two") {
         if (p.numArgs() < 2) 
            cout << std::endl << "Can't operate with " << MISSING_ARGS << endl;
         else {
            if (p.numArgs() > 2) 
               cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
            do_two(p.getArg(1), p.getArg(2));
         }
      }
      else if (p.getOperation() == "three") {
         if (p.numArgs() < 3) 
            cout << std::endl << "Can't operate with " << MISSING_ARGS << endl;
         else {
            if (p.numArgs() > 3) 
               cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
            if (!Parser::isInteger(p.getArg(3))) {
               cout << "Error: field " << p.getArg(3) << 
                                " is not an integer" << endl;
            }
            else {
              int int_param = stoi(p.getArg(3));
              do_three(p.getArg(1), p.getArg(2), int_param);
            }
         }
      }
      else {
         cout << std::endl << 
              "Command not recognized. Please try again." << endl; 
      }
   }
   return true;
}

int main()
{
  accept_commands(cin, false, false);
  return 0;
}
