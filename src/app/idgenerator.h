#ifndef HASHGENERATOR_H
#define HASHGENERATOR_H

#include <QString>

// PATTERN: Singleton

class IdGenerator
{
    static int counter;
    static IdGenerator *_instance;

    IdGenerator();

public:
    static IdGenerator* Instance();

    static QString generate();
};

#endif // HASHGENERATOR_H
