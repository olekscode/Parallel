#include "idgenerator.h"

int IdGenerator::counter = 1;
IdGenerator* IdGenerator::_instance = nullptr;

IdGenerator::IdGenerator()
{}

IdGenerator* IdGenerator::Instance()
{
    if (_instance == nullptr) {
        _instance = new IdGenerator();
    }

    return _instance;
}

QString IdGenerator::generate()
{
    QString id = "PT";

    if (counter / 10 == 0) {
        id += "00";
    }
    else if (counter / 100 == 0) {
        id += "0";
    }
    else if (counter / 1000 != 0) {
        // TODO: Create an exception
        throw "Error";
    }

    id += QString::number(counter++);
    return id;
}
