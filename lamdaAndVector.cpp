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

class Person{
public:
    std::string _name;
    int _birthyear;
    int _deathyear;
    Person(std::string name, int birthyear, int deathyear):
    _name(name), _birthyear(birthyear), _deathyear(deathyear)
    {}
    ~Person(){}
    bool stillAlive(int year){
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
};

class DB{
public:
    void showdatal(std::vector<Person> &pvector){
        std::cout << "---------------Content -----------------" << std::endl;
        for (auto it = pvector.begin(); it != pvector.end(); it++){
            it->showdata();
        }
        std::cout << "---------------------- -----------------" << std::endl;
    }

    void search(std::vector<Person> &pvector, std::string name, int year){
        auto it = find_if(pvector.begin(), pvector.end(), [&name](const Person& p){return (p._name == name);});
        if(it != pvector.end()){
            std::cout << " \nPerson Found" << std::endl;
            it->showdata();
            if(it->stillAlive(year)){
                std::cout << "This person is still alive" << std::endl;
            }
        }
    }

    void deletePerson(std::vector<Person> &pvector, std::string name){
        auto it = find_if(pvector.begin(), pvector.end(), [&name](const Person& p){return (p._name == name);});
        if(it != pvector.end()){
            std::cout << " \nPerson Found" << std::endl;
            it->showdata();
            pvector.erase(it);
            std::cout << "\nPerson deleted " << std::endl;
            return;
        }
        std::cout << "\nPerson not found " << std::endl;
    }
};



int main(int argc, char* argv[]){
    std::vector<Person> pvector;
    pvector.emplace(pvector.begin(), Person("bill", 1991,2100));

    Person p1 = Person("mauricio", 2000, 2100);
    Person p2 = Person("ernesto", 3000, 3100);
    Person p3 = Person("julian", 4000, 4100);

    pvector.push_back(p1);
    pvector.push_back(p2);
    pvector.push_back(p3);

    DB PersonDB = DB();

    PersonDB.showdatal(pvector);
    PersonDB.search(pvector, "mauricio", 2099);

    PersonDB.deletePerson(pvector, "bill");
    PersonDB.deletePerson(pvector, "bill");
    PersonDB.showdatal(pvector);

    return 0;
}