//
//  main.cpp
//  Assignment 1.2
//
//  Created by Hampus Ekedahl on 2023-02-16.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {

      // Create a text string, which is used to output the text file
      string myText;

      // Read from the text file
      ifstream MyReadFile("Assignment 1 Spain map.txt");

      // Use a while loop together with the getline() function to read the file line by line
      while (getline (MyReadFile, myText)) {
        // Output the text from the file
        cout << myText;
      }

      // Close the file
      MyReadFile.close();
    return 0;
}
