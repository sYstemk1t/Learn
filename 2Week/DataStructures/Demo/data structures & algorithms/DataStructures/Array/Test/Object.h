#ifndef _R00TK1T_OBJECT_H
#define _R00TK1T_OBJECT_H 1

#include <iostream>

using std::cout; using std::endl;

namespace r00tk1t
{
    class Object
    {
    public:
        Object()
        {
            cout << "enter default constructor" << endl;
        }

        Object(const Object &rhs)
        {
            cout << "enter copy constructor" << endl;
        }

        Object(Object &&rhs)
        {
            cout << "enter move constructor" << endl;
        }

        Object& operator=(const Object &rhs)
        {
            cout << "enter copy assignment" << endl;
            return *this;
        }

        Object& operator=(Object &&rhs)
        {
            cout << "enter move assignment" << endl;
            return *this;
        }

        ~Object()
        {
            cout << "enter destructor" << endl;
        }
    private:
        int a;
    };
}

#endif