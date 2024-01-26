//DEMO
#include <iostream>
#include "fileoperations.h"

int main(){
    char* path;
    std::cout << "What directory are you working in? (Enter Filepath. Add '\\' at the end)\n >>> ";
    std::cin >> path;

    fileoperate fileop(path);
    std::string txt;

    //Using the functions
    fileop.nline();

    std::cout << "\nWhat would you like to do to the file?\n";
    std::cout << "A = Append to File; \nO = Overwrite File; \nM = Merge with another file; \nR = Read a File\n >>> ";

    char reply;
    std::cin >> reply;

    if(reply == 'a' | reply == 'A'){
        //Append
        std::cout << "Input Text: ";
        std::cin >> txt;
        fileop.write(txt, 'a');
    }
    if(reply == 'o' | reply == 'O'){
        //Overwrite
        std::cout << "Input Text: ";
        std::cin >> txt;
        fileop.write(txt, 'w');
    }
    if(reply == 'm' | reply == 'M'){
        //Merge
        std::cout << "Input Directory(Filepath) of the file to be merged: ";
        std::cin >> txt;
        fileop.merge(txt.c_str());
    }
    if(reply == 'r' | reply == 'R'){
        //Read
        fileop.readfile();
    }

	return 0;
}
