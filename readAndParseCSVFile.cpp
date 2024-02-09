#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class CSVParser{
private:
    
public:
    std::string _filename;
    std::vector<std::string> lines;

    CSVParser(std::string filename): _filename(filename){}
    void getlines(){
        std::ifstream myfile; 
        myfile.open(this->_filename.c_str());
        std::string line = "";
        while(getline(myfile, line)){
            this->lines.push_back(line);
            line = "";
        }
    }

    void printLines(){
        for(auto line : lines){
            std::cout << line << std::endl;
        }
    }
};


int main(int argc, char *argv[]){
    CSVParser parser = CSVParser("myfile.csv");
    parser.getlines();
    parser.printLines();
    
}