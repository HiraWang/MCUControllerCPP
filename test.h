#ifndef TEST_H
#define TEST_H

#include "utility.h"

class MyClass : public QObject {
    Q_OBJECT

public:
    MyClass();
    ~MyClass();
    void test();

signals:
    void valueChanged(int v);
};

#endif