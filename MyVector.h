#ifndef LAB_5___MYVECTOR_H
#define LAB_5___MYVECTOR_H

const int MAX_SIZE = 5;

template <typename T> class MyVector;

template <typename T>
std::ostream &operator<<(std::ostream& out, const MyVector<T>& v);

template <typename T>
class MyVector
{
public:
    MyVector();
    MyVector(const T &el, int maxsz = MAX_SIZE);
    MyVector(const MyVector<T>& v);
    ~MyVector();

    virtual void add_element(const T &el);
    void delete_element(int i);
    T&  operator[](int i);
    const T&  operator[](int i) const;

    void sort() const;

    int find(const T &el) const;
    MyVector<T>& operator=(const MyVector<T>& v);
    friend std::ostream& operator<<<T>(std::ostream& out, const MyVector& v);

protected:
    int maxsize;
    int size;
    T* arr;

private:
    void resize();
};

template <typename T>
MyVector<T>::MyVector(): maxsize(MAX_SIZE), size(0){
    arr = new T[maxsize];
}

template <typename T>
MyVector<T>::MyVector(const T &el, int maxsz): maxsize(maxsz), size(1) {
    arr = new T[maxsize];
    arr[0] = el;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &v) {
    this->operator=(v);
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] arr;
}

template <typename T>
void MyVector<T>::add_element(const T &el) {
    if (size==maxsize) {
        resize();
    }
    arr[size] = el;
    ++size;
    sort();
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &v) {
    if (this == &v) {
        return *this;
    }
    maxsize = v.maxsize;
    size=v.size;
    arr = new T[maxsize];

    for (int i=0; i<size; ++i) arr[i] = v.arr[i];
    return *this;
}

template <typename T>
void MyVector<T>::resize() {
    T* temp;

    if (size == maxsize) {
        maxsize = static_cast<int>(maxsize * 1.5);
    }
    else if (size == maxsize/2) {
        maxsize = static_cast<int>(maxsize / 1.5);
        if (maxsize < MAX_SIZE) {
            maxsize = MAX_SIZE;
        }
    }

    temp = new T[maxsize];

    for (int i=0; i<size; ++i) temp[i] = arr[i];

    delete []arr;
    arr = temp;
}

template <typename T>
void MyVector<T>::delete_element(int i) {
    if (i >= 0 && i < size) {
        if (size == maxsize / 2) resize();
        --size;
        for (int j = i; j < size; ++j) arr[j] = arr[j + 1];
        arr[size] = nullptr;
    }
}

template <typename T>
const T &MyVector<T>::operator[](int i) const {
    return arr[i];
}

template <typename T>
T &MyVector<T>::operator[](int i) {
    return arr[i];
}

template <typename T>
int MyVector<T>::find(const T &el) const{
    sort();
    int l=0, r = size-1;
    int c = 0;
    while (l <= r) {
        c = (l + r)/2;
        if (arr[c] < el) {
            l = c + 1;
        }
        else if (arr[c] > el) {
            r = c - 1;
        }
        else return c;
    }
    return -1;
}

template <typename T>
void MyVector<T>::sort() const{
    int flag=0;
    for (int i=0; i<size-1; ++i) {
        flag = 0;
        for (int j=0; j<size-1-i; ++j){
            if (arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0) break;
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &v) {
    for (int i=0; i<v.size; ++i) {
        out << v.arr[i] << ((i == v.size-1) ? "" : " , ");
    }
    return out;
}

template <>
class MyVector<char*>
{
public:
    MyVector(const char* el = nullptr, int maxsz = MAX_SIZE);
    MyVector(const MyVector<char*> &v);
    ~MyVector();

    virtual void add_element(const char* el);
    void delete_element(int i);
    char* operator[](int i) const;

    void sort() const;

    int find(const char* el) const;
    MyVector<char*>& operator=(const MyVector<char*>& v);
    friend std::ostream& operator<<(std::ostream& out, const MyVector& v);

protected:
    int maxsize;
    char** arr;

    int size;
private:
    void resize();
};

MyVector<char*>::MyVector(const char* el, int maxsz): maxsize(maxsz), size(0) {
    arr = new char*[maxsize];
    if (el) {
        ++size;
        arr[0] = new char[strlen(el)+1];
        strcpy(arr[0], el);
    }
}

MyVector<char*>::MyVector(const MyVector<char*> &v) {
    this->operator=(v);
}

MyVector<char*>::~MyVector() {
    for (int i = 0; i < size; ++i) delete arr[i];
    delete[] arr;
}

void MyVector<char*>::add_element(const char* el) {
    if(size==maxsize) resize();
    arr[size] = new char[strlen(el)+1];
    strcpy(arr[size], el);
    ++size;
    sort();
}

MyVector<char*>& MyVector<char*>::operator=(const MyVector<char*> &v) {
    if(this == &v)
        return *this;
    maxsize = v.maxsize;
    size=v.size;
    arr = new char*[maxsize];
    for(int i=0; i<size; ++i) {
        arr[i] = new char[strlen(v.arr[i]) + 1];
        strcpy(arr[i], v.arr[i]);
    }
    return *this;
}

void MyVector<char*>::resize() {
    char** temp;

    if(size == maxsize) {
        maxsize = static_cast<int>(maxsize * 1.5);
    }
    else if(size == maxsize/2) {
        maxsize = static_cast<int>(maxsize / 1.5);
        if(maxsize < MAX_SIZE) maxsize = MAX_SIZE;
    }

    temp = new char*[maxsize];

    for (int i=0; i<size; ++i) {
        temp[i] = new char[strlen(arr[i])+1];
        strcpy(temp[i], arr[i]);
    }

    delete[] arr;
    arr = temp;
}

int MyVector<char*>::find(const char* el) const {
    sort();
    int l = 0, r = size-1;
    int c = 0;
    while (l <= r) {
        c = (l + r)/2;
        if (strcmp(arr[c], el)<0) {
            l = c + 1;
        }
        else if (strcmp(arr[c], el)>0) {
            r = c - 1;
        }
        else return c;
    }
    return -1;
}

void MyVector<char*>::sort() const {
    int flag=0;
    for(int i=0; i<size-1; ++i){
        flag = 0;
        for(int j=0; j<size-1-i; ++j){
            if (strcmp(arr[j], arr[j+1]) > 0){
                std::swap(arr[j], arr[j+1]);
                flag = 1;
            }
        }
        if(flag == 0) break;
    }
}

char* MyVector<char*>::operator[](int i) const{
    return arr[i];
}


void MyVector<char*>::delete_element(int i) {
    if (i >= 0 && i < size) {
        if (size == maxsize / 2) resize();
        delete arr[i];
        --size;
        for (int j = i; j < size; ++j) arr[j] = arr[j + 1];
        arr[size] = nullptr;
    }
}

std::ostream &operator<<(std::ostream &out, const MyVector<char*> &v) {
    for (int i=0; i<v.size; ++i) {
        out << v.arr[i] << ((i == v.size-1) ? "" : " , ");
    }
    return out;
}
#endif