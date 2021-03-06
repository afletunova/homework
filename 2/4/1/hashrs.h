#pragma once

#include "hashfunction.h"

/*!
 * Taken from https://habrahabr.ru/post/219139/
 */

class HashRs : public HashFunction
{
public:
    unsigned int getHash(const QString &word, const int &hashSize);
};
