#ifndef DATABASEPARSER_H
#define DATABASEPARSER_H
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#include "builder.h"

class DatabaseParser{
protected:
    Builder* m_Builder;
public:
    void setBuilder(Builder* builder){
        m_Builder = builder;
    }

    void parse(string file){
        std::ifstream csvFile(file);
        if (csvFile.is_open()){
            string line = "";
            while(getline(csvFile,line)){
                string petType = line.substr(0,line.find(','));
                if (petType == "Dog"){
                    m_Builder->addDog(line);
                }
                else if (petType == "Cat"){
                    m_Builder->addCat(line);
                }
                else if (petType == "Fish"){
                    m_Builder->addFish(line);
                }
                else if (petType == "Bird"){
                    m_Builder->addBird(line);
                }
                else {
                    cout << "Invalid pet type" << endl;
                }
            }
        }
        csvFile.close();
    }

};
#endif // DATABASEPARSER_H
