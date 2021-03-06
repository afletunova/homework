#pragma once
#include <QString>

/*!
 * \brief The HashFunction class - class is used to select the hash function
 */

class HashFunction
{
public:
    virtual unsigned int getHash(const QString &word, const int &hashSize) = 0;
};
