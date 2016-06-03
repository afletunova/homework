#pragma once

#include "tree.h"
#include "divisionbyzeroerror.h"

#include <QtTest/QtTest>
#include <QtCore/QObject>

class TreeTest : public QObject
{
    Q_OBJECT

private:
    Tree *tree;

private slots:
    void cleanup()
    {
        delete tree;
    }

    void simpleExampleTest()
    {
        tree = new Tree("( * 2 2 )");
        QCOMPARE(tree->compute(), 4);
    }

    void ExampleWithMinusTest()
    {
        tree = new Tree("( + ( - 3 -4 ) 8 )");
        QCOMPARE(tree->compute(), 15);
    }

    void DivisionByZeroTest()
    {
        tree = new Tree("( / 2 0 )");
        QVERIFY_EXCEPTION_THROWN(tree->compute(), DivisionByZeroError);
    }
};
