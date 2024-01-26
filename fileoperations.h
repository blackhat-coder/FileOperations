// This header uses 'const char *' for the filepath input
#ifndef FILEREADING_FILEOPERATIONS_H
#define FILEREADING_FILEOPERATIONS_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>


class fileoperate{

public:
    fileoperate(const char *basefilepath){ //Constructor
        no_of_lines = 0;
        filepath = basefilepath;

        if (file_valid() != true){
            std::cout << "DIRECTORY ERROR" << std::endl;
        }else {
            std::cout << "Do you want to create file? y/n: " ;
            std::string reply;
            std::cin >> reply ;
            std::cout << std::endl;

            if (reply == "y" | reply == "Y") {
                try {
                    std::cout << "Input Filename: " ;
                    std::cin >> filename;

                    strcpy(finalpath, basefilepath);
                    strcat(finalpath, filename); // The only place I do not use 'convert_finalpath()' function.

                    std::ofstream h(finalpath, std::ios_base::out);
                    h.close();

                } catch (...) {
                    std::cout << "Oops! Couldn't create file in " << basefilepath << " directory" << std::endl;
                }
            }else if (reply == "n" | reply == "N"){
                std::cout << "No file created \n";

                std::cout << "Do you wish to edit a file? y/n: ";
                std::string reply2;
                std::cin >> reply2;

                if(reply2 == "y" | reply2 == "Y"){
                    std::cout << "Input Filename: " ;
                    std::cin >> filename;
                }else if(reply2 == "n" | reply2 == "N"){
                    exit(-2);
                }else{
                    std::cout << "INVALID PARAMETER \n";
                }
            }else{
                std::cout << "INVALID PARAMETER" << std::endl;
            }
        }

        //Set-up 'finalpath' variable
        convert_finalpath(finalpath);
        std::cout << finalpath;
    }

    void nline(){
        lines_counter();

        std::cout << "lines: " << no_of_lines << std::endl;
    }

    void write(std::string text, char mode){
        // "a" = Append, "w" = Overwrite
        if (mode == 'a') {
            std::ofstream w(finalpath, std::ios_base::app);

            //Only start writing on a newline if the file is NOT empty
            if(!filepath_empty(finalpath))
                w << std::endl;

            w << text ;
            std::cout << "Successfully written to " << filename << "\n";
        }else if (mode == 'w'){
            std::ofstream w(finalpath);
            w << text ;

            std::cout << "Successfully overwrote " << filename << "\n";
        }
    }

    void merge(const char *filepath2){
        std::string line;
        std::ifstream m(filepath2, std::ios_base::in);

        std::cout << "Merging file " << filepath2 << " to " << filepath << std::endl;
        while (!m.eof()){
            std::getline(m, line);
            write(line , 'a'); // Append string from 'r' to file in our basefilepath

        }
        std::cout << "Merging Done" << std::endl;
        m.close();
    }

    void readfile(){
        std::string line;
        std::ifstream r(finalpath, std::ios_base::in);

        while(!r.eof()){
            getline(r, line);
            std::cout << line << std::endl;
        }

        r.close();
    }

private:
    const char *filepath;
    char filename[50];
    char finalpath[200];
    int no_of_lines;

    void lines_counter(){
        std::ifstream l(finalpath, std::ios_base::in);
        std::string ss;

        while (!l.eof()) {
            std::getline(l, ss);
            no_of_lines += 1;
        }

        l.close();
    }

    bool file_valid(){
        std::ifstream check(filepath, std::ios_base::in);

        if (check.bad()){ //.fail() => Dir.Err for some reason
            return false;
        }else{
            return true;
        }

        check.close();
    }

    bool file_empty(std::ifstream& file){
        return file.peek() == std::ifstream::traits_type::eof();
    }
    bool filepath_empty(const char *_filepath){
        std::ifstream checkfile(_filepath, std::ios_base::out);
        return checkfile.peek() == std::ifstream::traits_type::eof();
    }

    char convert_finalpath(char final_p[200]){
        strcpy(final_p, filepath);
        strcat(final_p, filename);
    }
};

#endif
