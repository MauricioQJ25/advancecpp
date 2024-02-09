//
// program: lamdaAndVector.cpp
// author: Mauricio Quijada
// date: February 07, 2024
// description: This programs shows how to use a function lamda when we need to find a value in a vector of objects.
//


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class Person{
private:
    std::string _name;
    int _birthyear;
    int _deathyear;
public:
    Person(std::string name, int birthyear, int deathyear):
    _name(name), _birthyear(birthyear), _deathyear(deathyear)
    {}
    ~Person(){}

    bool  stillAlive(const int year){
        if (year > this->_deathyear){
            return false;
        }
        return true;
    }

    int livingyears(){
        return this->_birthyear - this->_deathyear;
    }

    void showdata(){
        std::cout << "\nName: "<< this->_name
         << " BY: "<< this->_birthyear
         << " DY: "<< this->_deathyear << std::endl;
    }
    std::string getName() const {
        return this->_name;
    }
    int getbd(){
        return this->_birthyear;
    }
    int getdd(){
        return this->_deathyear;
    }
};

class DB{
    std::vector<Person>* _pvectorPtr;
public:
    DB(std::vector<Person>* pvectorPtr):
     _pvectorPtr(pvectorPtr){}
    void showdata(){
        std::cout << "---------------Content -----------------" << std::endl;
        for (auto it = this->_pvectorPtr->begin(); it != this->_pvectorPtr->end(); it++){
            it->showdata();
        }
        std::cout << "---------------------- -----------------" << std::endl;
    }
    
    void search(const std::string name, const int year){
        auto it = find_if(this->_pvectorPtr->begin(), this->_pvectorPtr->end(), [&name](const Person& p){return (p.getName() == name);});
        if(it != this->_pvectorPtr->end()){
            std::cout << " \nPerson Found" << std::endl;
            it->showdata();
            if(it->stillAlive(year)){
                std::cout << "This person is still alive" << std::endl;
            }
        }
        std::cout << "---------------------- -----------------" << std::endl;
    }

    void deletePerson( const std::string name){
        auto it = find_if(this->_pvectorPtr->begin(), this->_pvectorPtr->end(), [&name](const Person& p){return (p.getName() == name);});
        if(it != this->_pvectorPtr->end()){
            std::cout << " \nPerson Found" << std::endl;
            it->showdata();
            this->_pvectorPtr->erase(it);
            std::cout << "\nPerson deleted " << std::endl;
            return;
        }
        std::cout << "\nPerson not found " << std::endl;
        std::cout << "---------------------- -----------------" << std::endl;
    }
    // void insert()
    
};

class CSVParser{
private:
    std::vector<std::string> lines;

    void getlinesParser(){
        std::ifstream myfile; 
        myfile.open(this->_filename.c_str());
        std::string line = "";
        getline(myfile, line);
        while(getline(myfile, line)){
            this->lines.push_back(line);
            line = "";
        }
    }
public:
    std::string _filename;
    std::vector<Person> *_ptrVPersons;

    CSVParser(std::string filename, std::vector<Person> *ptrVPersons):
         _filename(filename),
         _ptrVPersons(ptrVPersons){}

    void printLines(){
        for(auto line : lines){
            std::cout << line << std::endl;
        }
    }
    
    void getData(){
        this->getlinesParser();
        std::string name;
        std::string byear;
        std::string dyear;
        for(auto line : lines){
            std::stringstream inputString(line);
            getline(inputString, name, ',');
            getline(inputString, byear, ',');
            getline(inputString, dyear);
            this->_ptrVPersons->push_back(Person(name, std::stoi(byear), std::stoi(dyear)));
        }
    }
};



int main(int argc, char* argv[]){
    std::vector<Person> persons;
    CSVParser parser = CSVParser("myfile.csv", &persons);
    parser.getData();
    DB personDB = DB(&persons);
    personDB.showdata();
    return 0;
}