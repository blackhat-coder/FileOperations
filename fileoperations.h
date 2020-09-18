
#ifndef FILEREADING_FILEOPERATIONS_H
#define FILEREADING_FILEOPERATIONS_H

#include <iostream>
#include <fstream>
#include "ostream"


class fileoperate{

public:
    fileoperate(std::string basefilepath){
        no_of_lines = 0;
        filepath = basefilepath.c_str() ;

        if (file_valid() == true){
            std::cout << "DIRECTORY ERROR" << std::endl;
        }else {
            std::cout << "Do you want to create file? y/n" ;
            std::string reply;
            std::cin >> reply ;
            std::cout << std::endl;

            if (reply == "y" | reply == "Y") {
                try {
                    std::ofstream h(basefilepath);
                    h.close();

                } catch (...) {
                    std::cout << "Oops! Couldn't create file in " << basefilepath << " directory" << std::endl;
                }
            }else if (reply == "n" | reply == "N"){
                std::cout << "No file created" << std::endl;
            }else{
                std::cout << "INVALID PARAMETER" << std::endl;
            }
        }

    }

    void nline(){
        no_lines();

        std::cout << "lines: " << no_of_lines << std::endl;
    }

    void write(std::string text, std::string mode){
        if (mode == "a") {
            std::ofstream w(filepath, std::ios_base::app);
            w << std::endl;
            w << text ;
        }else if (mode == "w"){
            std::ofstream w(filepath);
            w << text ;
        }
    }

    void merge(std::string filepath2){

        std::string line;
        std::ifstream r(filepath2, std::ios_base::in);

        std::cout << "Merging file " << filepath2 << " to " << filepath << std::endl;
        while (!r.eof()){
            std::getline(r, line);
            write(line , "a");

        }
        std::cout << "Done" << std::endl;
    }

    void readfile(){
        std::string line;
        std::ifstream r(filepath, std::ios_base::in);

        while(!r.eof()){
            getline(r, line);
            std::cout << line << std::endl;
        }

        r.close();
    }

private:
    std::string filepath;
    int no_of_lines;

    void no_lines(){
        std::ifstream l(filepath, std::ios_base::in);
        std::string ss;

        while (!l.eof()) {
            std::getline(l, ss);
            no_of_lines += 1;
        }

        l.close();
    }

    bool file_valid(){
        std::ifstream check(filepath, std::ios_base::in);

        if (check.fail()){
            return false;
        }else{
            return true;
        }

        check.close();
    }
};

#endif
