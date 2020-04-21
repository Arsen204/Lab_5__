#ifndef LAB_5___MYSET_H
#define LAB_5___MYSET_H
#include "MyVector.h"

template <typename T> class MySet;

template <typename T>
std::ostream &operator<<(std::ostream &out, const MySet<T> &s);

template <typename T>
MySet<T> operator+(const MySet<T>& s1,const MySet<T>& s2);

template <typename T>
MySet<T> operator-(const MySet<T>& s1,const MySet<T>& s2);

template <typename T>
MySet<T> operator*(const MySet<T>& s1,const MySet<T>& s2);

template <typename T>
class MySet:public MyVector<T> {
public:
    MySet<T>(const T &el): MyVector<T>(el) {};

    friend std::ostream& operator<< <T>(std::ostream& out, const MySet<T>& s);
    friend MySet<T> operator+ <T>(const MySet<T>& s1,const MySet<T>& s2);
    friend MySet<T> operator- <T>(const MySet<T>& s1,const MySet<T>& s2);
    friend MySet<T> operator* <T>(const MySet<T>& s1,const MySet<T>& s2);

    bool operator==(const MySet<T>& s);
    MySet<T>& operator+=(const MySet<T>& s);
    MySet<T>& operator-=(const MySet<T>& s);
    MySet<T>& operator*=(const MySet<T>& s);
    void add_element(const T &el);
    void delete_element(const T &el);

    bool is_element(const T &el) const;
};

template <typename T>
void MySet<T>::add_element(const T &el) {
    if (this->size == 0 || !is_element(el)) {
        MyVector<T>::add_element(el);
    }
}

template <typename T>
void MySet<T>::delete_element(const T &el) {
    if (find(el) != -1){
        MyVector<T>::delete_element(find(el));
    }
}

template <typename T>
bool MySet<T>::is_element(const T &el) const{
    return this->find(el) != -1;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const MySet<T> &s) {
    out << "{";
    for (int i = 0; i < s.size; i++) {
        out << s[i] << ((i == s.size - 1) ? "" : " , ");
    }
    out << "}";
    return out;
}

template <typename T>
MySet<T> operator+(const MySet<T> &s1, const MySet<T> &s2) {
    MySet<T> temp(s1);
    return temp += s2;
}

template <typename T>
MySet<T> operator-(const MySet<T> &s1, const MySet<T> &s2) {
    MySet<T> temp(s1);
    return temp -= s2;
}

template <typename T>
MySet<T> operator*(const MySet<T> &s1, const MySet<T> &s2) {
    MySet<T> temp(s1);
    return temp *= s2;
}

template <typename T>
bool MySet<T>::operator==(const MySet<T> &s) {
    if (this->size == s.size) {
        for (int i = 0; i<this->size; ++i) {
            if (strcmp((*this)[i], s[i]) != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
MySet<T> &MySet<T>::operator+=(const MySet<T> &s) {
    for (int i = 0; i<s.size; ++i) {
        if (find(s[i]) == -1) add_element(s[i]);
    }
    return *this;
}

template <typename T>
MySet<T> &MySet<T>::operator-=(const MySet<T> &s) {
    for (int i=0; i<s.size; ++i) {
        if (is_element(s[i])) {
            delete_element(s[i]);
        }
    }
    return *this;
}

template <typename T>
MySet<T> &MySet<T>::operator*=(const MySet<T> &s) {
    for (int i=0; i<this->size; ++i) {
        if (!s.is_element((*this)[i])) {
            delete_element((*this)[i]);
        }
    }
    return *this;
}

template <>
class MySet<char*>:public MyVector<char*> {
public:
    MySet<char*>(const char* el = nullptr): MyVector<char*>(el) {};

    friend std::ostream& operator<< (std::ostream& out, const MySet<char*>& s);
    friend MySet<char*> operator+ (const MySet<char*>& s1,const MySet<char*>& s2);
    friend MySet<char*> operator- (const MySet<char*>& s1,const MySet<char*>& s2);
    friend MySet<char*> operator* (const MySet<char*>& s1,const MySet<char*>& s2);

    bool operator==(const MySet<char*>& s);
    MySet<char*>& operator+=(const MySet<char*>& s);
    MySet<char*>& operator-=(const MySet<char*>& s);
    MySet<char*>& operator*=(const MySet<char*>& s);
    void add_element(const char* el) override;
    void delete_element(const char* el);

    bool is_element(const char* el) const;
};

void MySet<char*>::add_element(const char *el) {
    if (size == 0 || !is_element(el)) {
        MyVector::add_element(el);
    }
}


void MySet<char*>::delete_element(const char *el) {
    if (find(el) != -1){
        MyVector::delete_element(find(el));
    }
}

bool MySet<char*>::is_element(const char *el) const{
    return find(el) != -1;
}

std::ostream &operator<<(std::ostream &out, const MySet<char *> &s) {
    out << "{";
    for (int i = 0; i < s.size; i++) {
        out << s[i] << ((i == s.size - 1) ? "" : " , ");
    }
    out << "}";
    return out;
}

MySet<char*> operator+(const MySet<char*> &s1, const MySet<char*> &s2) {
    MySet<char*> temp(s1);
    return temp += s2;
}

MySet<char*> operator-(const MySet<char*> &s1, const MySet<char*> &s2) {
    MySet<char*> temp(s1);
    return temp -= s2;
}

MySet<char*> operator*(const MySet<char*> &s1, const MySet<char*> &s2) {
    MySet<char*> temp(s1);
    return temp *= s2;
}

bool MySet<char*>::operator==(const MySet<char*> &s) {
    if (size == s.size) {
        for (int i = 0; i<size; ++i) {
            if (strcmp((*this)[i], s[i]) != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}


MySet<char*> &MySet<char*>::operator+=(const MySet<char*> &s) {
    for (int i = 0; i<s.size; ++i) {
        if (find(s[i]) == -1) add_element(s[i]);
    }
    return *this;
}

MySet<char*> &MySet<char*>::operator-=(const MySet<char*> &s) {
    for (int i=0; i<s.size; ++i) {
        if (is_element(s[i])) {
            delete_element(s[i]);
        }
    }
    return *this;
}

MySet<char*> &MySet<char*>::operator*=(const MySet<char*> &s) {
    for (int i=0; i<this->size; ++i) {
        if (!s.is_element((*this)[i])) {
            delete_element((*this)[i]);
        }
    }
    return *this;
}

#endif //LAB_5___MYSET_H
