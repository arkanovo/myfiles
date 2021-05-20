#include <iostream>

class NegativeParameter
{
protected:
const char* action; const char* param; unsigned int value;
public:
NegativeParameter(const char* action, const char* param, unsigned int value) : action(action), param(param), value(value) {}
NegativeParameter(const NegativeParameter& e) : action(e.action), param(e.param),
value(e.value) {}
~NegativeParameter() {}
inline unsigned int getValue() { return value; }
inline void what() { std::cout << "Action: " << action << "! Using " << param << ": " << value << ". Exception: Parameter is a negative!\n"; }
};
class IndexMorethenLenght
{
protected:
const char* action;
int index;
public:
IndexMorethenLenght(const char* action, int index) : action(action), index(index)
{}
IndexMorethenLenght(const IndexMorethenLenght& e) : action(e.action),
index(e.index) {}
~IndexMorethenLenght() {}
inline int getIndex() { return index; }
inline void what() { std::cout << "Action: " << action << ". Index used: " << index << ". Exception: Index more then lenght!\n"; }
};
class IncoherentGraph
{
protected:
const char* action;
public:
IncoherentGraph(const char* action) : action(action) {} IncoherentGraph(const IncoherentGraph& e) : action(e.action) {}
~IncoherentGraph() {}
inline void what() { std::cout << "Action: " << action << ". Exception: Incoherent graph!\n"; }
};

template <class T> inline int binaryFind(T mass[], T elem, unsigned int size)	// O(logN)
{
if (size == 0) return -1;
unsigned int l = 0, r = size - 1, mid;
while (l != r)
{
mid = (l + r) >> 1;
if (elem == mass[mid]) return mid;
elem > mass[mid] ? l = ++mid : r = mid;
}
return elem == mass[l] ? l : -1;
}
template <class T> inline void swap(T& value1, T& value2) { T var = value1; value1 = value2, value2 = var; }
template <class T> void QuickSort(T* mass, unsigned short first, unsigned short last)
{
if (first < last)
{
unsigned short left = first + 1, right = last; T value = mass[first];
while (left != right)
{
if (mass[left] < value)

++left;
else
{
while (left != --right && value < mass[right]); swap(mass[left], mass[right]);
}
}
swap(mass[first], mass[--left]); QuickSort(mass, first, left),
QuickSort(mass, right, last);
}
}
template <template <class T> class Elem, class T> Elem<T>* merge(Elem<T>* fir, Elem<T>* sec)
{
Elem<T> var, * head = &var, * current = head;
while (fir != NULL && sec != NULL) fir->getData() < sec->getData() ?
(current->setRight(fir), current = fir, fir = fir->getRight())
:
(current->setRight(sec), current = sec, sec = sec->getRight()); current->setRight(fir == 0 ? sec : fir);
return head->getRight();
}
template <template <class T> class Elem, class T> Elem<T>* MergeSortDoubleList(Elem<T>* beg)
{
if (beg == 0 || beg->getRight() == 0) return beg; Elem<T>* fir = beg, * sec = beg->getRight(); while (sec != NULL && sec->getRight() != 0)
beg = beg->getRight(), sec = sec->getRight()->getRight(); sec = beg->getRight();
beg->setRight(NULL);
return merge(MergeSortDoubleList(fir), MergeSortDoubleList(sec));
}
template <template <class T> class Elem, class T> void QuickSortDoubleList(Elem<T>* beg, Elem<T>* end, unsigned short first, unsigned short last)
{
if (first < last)
{
unsigned short left = first + 1, right = last;  Elem<T>* leftElem = beg->getRight(), * rightElem = end; T value = beg->getData();
while (left != right)
{
if (leftElem->getData() < value)
++left, leftElem = leftElem->getRight();
else
{
rightElem = rightElem->getLeft();
while (left != --right && value < rightElem->getData()) rightElem = rightElem->getLeft();
swap(leftElem, rightElem);
}
}
--left, leftElem = leftElem->getLeft(); swap(beg, leftElem);
QuickSortList(beg, leftElem, first, left), QuickSortList(rightElem, end, right, last);
}
}

template <class T> class Node
{
protected:
T data;
unsigned short height; Node<T>* left; Node<T>* right; Node<T>* parent;
public:

Node(T data = T())
: data(data), height(1), left(NULL), right(NULL), parent(NULL) {}

inline bool operator >	(const Node<T>& N) const { return data > N.getData(); } inline bool operator <	(const Node<T>& N) const { return data < N.getData(); } inline bool operator >= (const Node<T>& N) const { return data >= N.getData(); } inline bool operator <= (const Node<T>& N) const { return data <= N.getData(); } inline bool operator == (const Node<T>& N) const { return data == N.getData(); } inline bool operator != (const Node<T>& N) const { return data != N.getData(); }

inline T getData() const { return data; }
inline Node<T>* getLeft() const { return left; } inline Node<T>* getRight() const { return right; } inline Node<T>* getParent() const { return parent; }
inline unsigned short getHeight() const { return height; }

inline void setData(T d) { data = d; }
inline void setLeft(Node<T>* l) { left = l; } inline void setRight(Node<T>* r) { right = r; } inline void setParent(Node<T>* p) { parent = p; }
inline void setHeight(unsigned short h) { height = h; }
};
template <class T> inline Node<T>* Min(Node<T>* current)
{
while (current->getLeft() != NULL) current = current->getLeft();
return current;
}
template <class T> inline Node<T>* Max(Node<T>* current)
{
while (current->getRight() != NULL) current = current->getRight();
return current;
}
template <class T> class TreeIterator : public std::iterator<std::input_iterator_tag, T>
{
protected:
Node<T>* ptr;
public:
TreeIterator() : ptr(NULL) {} TreeIterator(Node<T>* n) : ptr(n) {}
TreeIterator(const TreeIterator<T>& it) : ptr(it.ptr) {}

bool operator != (const TreeIterator<T>& other) const { return ptr != other.ptr; } bool operator == (const TreeIterator<T>& other) const { return ptr == other.ptr; } T operator * () const { if (ptr == NULL) return T(); return ptr->getData(); } TreeIterator<T>& operator ++ ()
{
if (ptr != NULL)
{
if (ptr->getRight() != NULL) ptr = Min(ptr->getRight());
else if (ptr->getParent() != NULL)
{
bool isRight = false;
do { isRight = *ptr->getParent() < *ptr, ptr = ptr->getParent(); }
while (isRight && ptr->getParent() != NULL);
if (isRight && ptr->getParent() == NULL) ptr = NULL;
}
else ptr = NULL;
}
return *this;
}
TreeIterator<T> operator ++ (int v)
{
TreeIterator var(*this);
if (ptr != NULL)
{
if (ptr->getRight() != NULL) ptr = Min(ptr->getRight());
else if (ptr->getParent() != NULL)
{
bool isRight = false;

do { isRight = *ptr->getParent() < *ptr, ptr = ptr->getParent(); }
while (isRight && ptr->getParent() != NULL);
if (isRight && ptr->getParent() == NULL) ptr = NULL;
}
else ptr = NULL;
}
return var;
}
TreeIterator<T>& operator -- ()
{
if (ptr != NULL)
{
if (ptr->getLeft() != NULL) ptr = Max(ptr->getLeft());
else if (ptr->getParent() != NULL)
{
bool isLeft = false;
do { isLeft = *ptr->getParent() > *ptr, ptr = ptr->getParent(); }
while (isLeft && ptr->getParent() != NULL);
if (isLeft && ptr->getParent() == NULL) ptr = NULL;
}
else ptr = NULL;
}
return *this;
}
TreeIterator<T> operator -- (int v)
{
TreeIterator var(*this);
if (ptr != NULL)
{
if (ptr->getLeft() != NULL) ptr = Max(ptr->getLeft());
else if (ptr->getParent() != NULL)
{
bool isLeft = false;
do { isLeft = *ptr->getParent() > *ptr, ptr = ptr->getParent(); }
while (isLeft && ptr->getParent() != NULL);
if (isLeft && ptr->getParent() == NULL) ptr = NULL;
}
else ptr = NULL;
}
return var;
}
TreeIterator<T>& operator = (const TreeIterator<T>& it) { ptr = it.ptr; return
*this; }

inline Node<T>* getPtr() { return ptr; }
};
template <class T> class VectorIterator
{
protected:
T* ptr;
unsigned short size;
unsigned short index;
public:
VectorIterator() : ptr(NULL), index(0), size(0) {}
VectorIterator(T* arr, unsigned short size) : ptr(arr), index(0), size(size) {} VectorIterator(T* arr, unsigned short index, unsigned short size) : ptr(arr),
index(index), size(size) {}
VectorIterator(const VectorIterator<T>& it) : ptr(it.ptr), index(it.index), size(it.size) {}

bool operator == (const VectorIterator<T>& other) const { return ptr == other.ptr && index == other.index; }
bool operator != (const VectorIterator<T>& other) const { return ptr != other.ptr
|| index != other.index; }
T operator * () const { if (ptr == NULL) return T(); return ptr[index]; } VectorIterator<T>& operator ++ () // O(1)
{
if (++index >= size) ptr = NULL, index = size = 0;
return *this;
}
VectorIterator<T> operator ++ (int v) // O(1)

{
VectorIterator var(*this);
if (++index >= size) ptr = NULL, index = size = 0;
return var;
}
VectorIterator<T>& operator -- () // O(1)
{
if (--index < 0) ptr = NULL, index = size = 0;
return *this;
}
VectorIterator<T> operator -- (int v) // O(1)
{
VectorIterator var(*this);
if (--index < 0) ptr = NULL, index = size = 0;
return var;
}

VectorIterator<T>& operator = (const VectorIterator<T>& it) { ptr = it.ptr, index
= it.index, size = it.size; return *this; }
};
template <class T> class DoubleLinkElement
{
protected:
T data; DoubleLinkElement<T>* left; DoubleLinkElement<T>* right;
public:
DoubleLinkElement(T data = T())
: data(data), left(NULL), right(NULL) {}

inline bool operator >	(const DoubleLinkElement<T>& N) const { return data > N.getData(); }
inline bool operator <	(const DoubleLinkElement<T>& N) const { return data <
N.getData(); }
inline bool operator == (const DoubleLinkElement<T>& N) const { return data == N.getData(); }
inline bool operator != (const DoubleLinkElement<T>& N) const { return data !=
N.getData(); }

inline T getData() const { return data; }
inline DoubleLinkElement<T>* getLeft() const { return left; }
inline DoubleLinkElement<T>* getRight() const { return right; }

inline void setData(T d) { data = d; }
inline void setLeft(DoubleLinkElement<T>* l) { left = l; }
inline void setRight(DoubleLinkElement<T>* r) { right = r; }
};
template <class T> class DoubleLinkListIterator : public
std::iterator<std::input_iterator_tag, T>
{
protected:
DoubleLinkElement<T>* ptr;
public:
DoubleLinkListIterator() : ptr(NULL) {} DoubleLinkListIterator(DoubleLinkElement<T>* n) : ptr(n) {} DoubleLinkListIterator(const DoubleLinkListIterator<T>& it) : ptr(it.ptr) {}

bool operator != (const DoubleLinkListIterator<T>& other) const { return ptr != other.ptr; }
bool operator == (const DoubleLinkListIterator<T>& other) const { return ptr ==
other.ptr; }
T operator * () const { if (ptr == NULL) return T(); return ptr->getData(); } DoubleLinkListIterator<T>& operator ++ () { ptr = ptr->getRight(); return *this; } DoubleLinkListIterator<T> operator ++ (int v) { DoubleLinkListIterator var(*this);
ptr = ptr->getRight(); return var; }
DoubleLinkListIterator<T>& operator -- () { ptr = ptr->getLeft(); return *this; } DoubleLinkListIterator<T> operator -- (int v) { DoubleLinkListIterator var(*this);
ptr = ptr->getLeft(); return var; }

DoubleLinkListIterator<T>& operator = (const DoubleLinkListIterator<T>& it) { ptr
= it.ptr; return *this; }

};
template <class T> class Tree
{
private:
inline int bfactor(Node<T>* p) // O(1)
{
unsigned short hl = 0, hr = 0;
if (p->getLeft() != NULL)
hl = p->getLeft()->getHeight();
if (p->getRight() != NULL)
hr = p->getRight()->getHeight();
return (int)hr - (int)hl;
}
inline void fixHeight(Node<T>* p) // O(1)
{
unsigned short hl = 0, hr = 0;
if (p->getLeft() != NULL)
hl = p->getLeft()->getHeight();
if (p->getRight() != NULL)
hr = p->getRight()->getHeight();
⦁	>setHeight((hl > hr ? hl : hr) + 1);
}
inline Node<T>* RotateRight(Node<T>* p)
{
Node<T>* q = p->getLeft(); p->setLeft(q->getRight());
if (p->getLeft() != NULL) p->getLeft()->setParent(p); q->setRight(p);
⦁	>setParent(p->getParent()); p->setParent(q);
if (p == root) root = q;
fixHeight(p); fixHeight(q); return q;
}
inline Node<T>* RotateLeft(Node<T>* q)
{
Node<T>* p = q->getRight(); q->setRight(p->getLeft());
if (q->getRight() != NULL) q->getRight()->setParent(q); p->setLeft(q);
p->setParent(q->getParent()); q->setParent(p);
if (q == root) root = p;
fixHeight(q); fixHeight(p); return p;
}
inline Node<T>* Balance(Node<T>* p)
{
fixHeight(p);
if (bfactor(p) == 2)
{
if (bfactor(p->getRight()) < 0)
p->setRight(RotateRight(p->getRight()));
return RotateLeft(p);
}
if (bfactor(p) == -2)
{
if (bfactor(p->getLeft()) > 0)
p->setLeft(RotateLeft(p->getLeft()));
return RotateRight(p);
}
return p;
}
Node <T>* adding(Node <T>* N, bool& deleted, Node <T>* current = NULL)
{
if (N == NULL) return NULL;
if (root == NULL)

{
root = N; size = 1; return N;
}
if (current == NULL) current = root;

if (*current > *N)
{
if (current->getLeft() != NULL)
current->setLeft(Add(N, deleted, current->getLeft()));
else
{
++size;
current->setLeft(N);
current->getLeft()->setParent(current);
}
if (deleted) return current;
}
if (*current < *N)
{
if (current->getRight() != NULL)
current->setRight(Add(N, deleted, current->getRight()));
else
{
++size;
current->setRight(N);
current->getRight()->setParent(current);
}
if (deleted) return current;
}
if (*current == *N) delete N, deleted = true; return current;
}
Node <T>* addingUnique(Node <T>* N, Node <T>* current = NULL)
{
if (N == NULL) return NULL;
if (root == NULL)
{
root = N; size = 1; return N;
}
if (current == NULL) current = root;

if (*current > *N)
{
if (current->getLeft() != NULL)
current->setLeft(AddUnique(N, current->getLeft()));
else
{
++size;
current->setLeft(N);
current->getLeft()->setParent(current);
}
}
if (*current < *N)
{
if (current->getRight() != NULL)
current->setRight(AddUnique(N, current->getRight()));
else
{
++size;
current->setRight(N);
current->getRight()->setParent(current);
}
}
return current;
}
protected:
Node<T>* root;

unsigned int size;
public:
Tree()
: root(NULL), size(0) {}
void Clear(Node<T>* current = NULL)
{
if (size == 0) return;

if (current == NULL) current = root;

if (current->getLeft() != NULL) Clear(current->getLeft());

if (current->getRight() != NULL) Clear(current->getRight());

if (current == root) root = NULL, size = 0;

delete current;

}
Node<T>* Add(Node<T>* N, bool& deleted, Node<T>* current = NULL) { return
Balance(adding(N, deleted, current)); }
Node<T>* AddUnique(Node<T>* N, Node<T>* current = NULL) { return
Balance(addingUnique(N, current)); }
inline void Push(T n) { bool deleted = false; Add(new Node<T>(n), deleted); }
inline void PushUnique(T n) { AddUnique(new Node<T>(n)); }

inline const Tree operator = (const Tree& tree) // O(1)
{
root = tree.root, size = tree.size;
return *this;
}
inline bool operator == (const Tree& tree) const	// O(N)
{
if (size != tree.getSize()) return false; auto it1 = getBegin(), it2 = tree.getBegin();
for (unsigned int i = 0; i < size; ++i, ++it1, ++it2)
if (*it1 != *it2)
return false; return true;
}
inline bool operator != (const Tree& tree) const
{
if (size != tree.getSize()) return true;
auto it1 = getBegin(), it2 = tree.getBegin();
for (unsigned int i = 0; i < size; ++i, ++it1, ++it2)
if (*it1 != *it2)
return true; return false;
}
inline T operator[] (unsigned int index) const
{
if (size == 0 || index >= size - 1) return T();
auto it = getBegin();
for (unsigned int index = 0; index != size; ++index, ++it);
return *it;
}
Node<T>* Min(Node<T>* current = NULL) const
{
if (root == NULL) return NULL;
if (current == NULL) current = root;
while (current->getLeft() != NULL) current = current->getLeft();
return current;
}
Node<T>* Max(Node<T>* current = NULL) const
{
if (root == NULL) return NULL;
if (current == NULL) current = root;
while (current->getRight() != NULL) current = current->getRight();
return current;
}
TreeIterator<T> Find(T data, Node <T>* current = NULL) const

{
if (root == NULL) return NULL;

if (current == NULL) current = root;

if (current->getData() == data) return current;

if (current->getData() > data) return current->getLeft() == NULL ? NULL : Find(data, current->getLeft());

if (current->getData() < data) return current->getRight() == NULL ? NULL : Find(data, current->getRight());
}
inline int FindIndex(T data) const
{
int index = 0;
auto it = getBegin(), obj = Find(data);
if (obj == NULL) return -1; while (it != obj) ++it, ++index; return index;
}

inline Node<T>* getRoot() const { return root; }
inline TreeIterator <T> getBegin() const { return Min(); } inline TreeIterator <T> getEnd() const { return Max(); } inline unsigned int getSize() const { return size; }
};
template <class T> class Vector
{
protected:
inline void CreateNew() // O(N)
{



size;


}
capacity += 256;
T* arrNew = new T[capacity], * value = size > 0 ? arr : NULL, * end = value +

for (T* valueNew = arrNew; value != end; ++value, ++valueNew)
*valueNew = *value;
delete[] arr; arr = arrNew;

inline T At(unsigned short index) const { return arr[index]; } T* arr;
unsigned short size;
unsigned short capacity;
public:
Vector(unsigned short capacity = 0) // O(1)
: arr(new T[capacity]), size(0), capacity(capacity) {} Vector(T begin) // O(1)
: arr(new T[256]), size(0), capacity(256) {}
Vector(const Vector& vec)	// O(N)
: arr(vec.arr), size(vec.size), capacity(vec.capacity) {}
inline void Clear() { delete[] arr, size = 0, capacity = 0; arr = NULL; } // O(1)
inline void Push(T value) { if (FindIndex(value) == -1) PushUnique(value); } // O(N)
inline void PushUnique(T value) // O(N)
{
if (size >= capacity) CreateNew(); arr[size] = value, ++size;
}
inline T PopBack() { T res; size == 0 ? void() : swap(res, arr[size - 1]); return
res; }	// O(1)
inline int FindIndex(T value) const // O(N)
{
unsigned short index = 0; bool parity = size % 2; T* begin = arr;
for (T* end = begin + size - parity; begin != end; ++begin, ++index)
{
if (*begin == value) return index;
++index;
if (*(++begin) == value) return index;
}
return parity && *begin == value ? index : -1;

}
inline int BinaryFind(T value) const
{
if (size == 0) return -1;
unsigned int l = 0, r = size - 1, mid;
while (l != r)
{
mid = (l + r) >> 1;
if (value == arr[mid]) return mid;
value > arr[mid] ? l = mid + 1 : r = mid;
}
return value == arr[l] ? l : -1;
}
inline void Sorting() { QuickSort(arr, 0, size); } // O(NlogN)

inline T operator[](unsigned short index) const { return index >= size || size ==
0 ? T() : arr[index]; }
inline bool operator == (const Vector& vec) const
{
if (size != vec.size) return false;
for (unsigned short i = 0; i < size; ++i)
if (arr[i] != vec.At(i))
return false; return true;
}
inline bool operator != (const Vector& vec) const
{
if (size != vec.size) return true;
for (unsigned short i = 0; i < size; ++i)
if (arr[i] != vec.At(i))
return true; return false;
}
inline const Vector<T> operator = (const Vector<T>& vec)
{
Clear(), arr = vec.arr, size = vec.size, capacity = vec.capacity;
return *this;
}

inline VectorIterator<T> getBegin() const { return VectorIterator<T>(arr, size); }
inline T* getArray() const { return arr; }
inline unsigned short getSize() const { return size; }
inline unsigned short getCapacity() const { return capacity; }
};
template <class T> class DoubleList
{
protected:
DoubleLinkElement<T>* beg; DoubleLinkElement<T>* end; unsigned int size;
public:
DoubleList()
: beg(NULL), end(NULL), size(0) {} DoubleList(T begin)
: beg(new DoubleLinkElement<T>(begin)), end(beg), size(1) {} DoubleList(const DoubleList& list)
: beg(list.beg), end(list.end), size(list.size) {}
inline void Clear()
{
switch (size)
{
case 0: break;
case 1: delete beg; break; default:
DoubleLinkElement<T>* nodeB = beg->getRight(), * nodeE = end->getLeft();
bool equality = size % 2;
for (int index = 0, count = (size >> 1) - 1; index < count; ++index, nodeB
= nodeB->getRight(), nodeE = nodeE->getLeft())
delete nodeB->getLeft(), delete nodeE->getRight(); equality ?
delete nodeB->getRight(), delete nodeB->getLeft()

:
delete nodeE;
delete nodeB;
}
beg = end = NULL, size = 0;
}
inline void Push(T value) { if (FindIndex(value) == -1) PushUnique(value); }
inline void PushUnique(T value)
{
DoubleLinkElement<T>* add = new DoubleLinkElement<T>(value);
if (++size == 1) { beg = end = add; return; }
end->setRight(add), add->setLeft(end), end = add;
}

inline void PushFront(T value)
{
DoubleLinkElement<T>* add = new DoubleLinkElement<T>(value);
if (++size == 1) { beg = end = add; return; }
beg->setLeft(add), add->setRight(beg), beg = add;
}
inline T PopFront()
{
if (size == 0) return T();
T res = DoubleList<T>::beg->getData();
if (DoubleList<T>::size > 1)
{
DoubleLinkElement<T>* newBegin = beg->getRight();
newBegin->setLeft(NULL), delete beg, beg = newBegin, --size;
return res;
}
else
{
beg = end = NULL, size = 0;
return res;
}
}
inline T PopBack()
{
if (size == 0) return T();
T res = DoubleList<T>::end->getData();
if (DoubleList<T>::size > 1)
{
DoubleLinkElement<T>* var = end->getLeft(); res = end->getData(); var-
>setLeft(NULL), delete end, end = var, --size;
return res;
}
else
{
beg = end = NULL, size = 0;
return res;
}
}

inline T operator[] (unsigned int index) const
{
if (index >= size) return T(); DoubleLinkElement<T>* finder = beg;
for (unsigned int i = 0; i < index; ++i, finder->getRight());
return finder->getData();
}
inline bool operator == (const DoubleList& list) const
{
if (size != list.size) return false;
for (auto it = getBegin(), itL = list.getBegin(); it != NULL; ++it, ++itL)
if (*it != *itL)
return false; return true;
}
inline bool operator != (const DoubleList& list) const
{
if (size != list.size) return true;

for (auto it = getBegin(), itL = list.getBegin(); it != NULL; ++it, ++itL)
if (*it != *itL)
return true; return false;
}
inline const DoubleList<T> operator = (const DoubleList<T>& list)
{
Clear(), beg = list.beg, end = list.end, size = list.size;
return *this;
}

inline DoubleLinkElement<T>* Find(T value) const
{
int index = 0, count = (size >> 1) + size % 2;
for (DoubleLinkElement<T>* varB = beg, *varE = end; index < count; ++index, varB = varB->getRight(), varE = varE->getLeft())
{
if (varB->getData() == value) return varB;
if (varE->getData() == value) return varE;
}
return NULL;
}
inline int FindIndex(T value) const
{
int index = 0, count = (size >> 1) + size % 2;
for (DoubleLinkElement<T>* varB = beg, *varE = end; index < count; ++index, varB = varB->getRight(), varE = varE->getLeft())
{
if (varB->getData() == value) return index;
if (varE->getData() == value) return size - ++index;
}
return -1;
}
inline void QuickSort() // O(NlogN)
{
DoubleLinkElement<T>* none = new DoubleLinkElement<T>(); none->setLeft(end), end->setRight(none);
QuickSortDoubleList(beg, none, 0, size); delete none, end->setRight(NULL);
}
inline void MergeSort() // O(NlogN)
{
beg = MergeSortDoubleList(beg), beg->setLeft(NULL), end = beg;
while (end->getRight() != NULL)
end->getRight()->setLeft(end), end = end->getRight();
}
inline void Sorting() { MergeSort(); }

inline DoubleLinkListIterator<T> getBegin() const { return beg; } inline DoubleLinkListIterator<T> getEnd() const { return end; } inline unsigned int getSize() const { return size; }
};

class DisjoinSetsUnit
{
protected:
int* parent;
int* rank;
unsigned int size;
unsigned int capacity;
public:
DisjoinSetsUnit(unsigned int capacity = 0)
: parent(new int[capacity]), rank(new int[capacity]), size(0), capacity(capacity) {}
DisjoinSetsUnit(const DisjoinSetsUnit& DSU)
: parent(DSU.parent), rank(DSU.rank), size(DSU.size), capacity(DSU.capacity)
{}
inline void Clear() { delete[] parent, delete[] rank, size = capacity = 0; }
inline void Push(int x) { if (size < capacity) parent[x] = x, rank[x] = 0, ++size;
}
inline int Find(int x) const { return size > 0 ? (x == parent[x] ? x : parent[x] =
Find(parent[x])) : -1; }

inline int Union(int x, int y, bool has = false)
{
if (size == 0 || !has || (x = Find(x)) == (y = Find(y)))
return -1;

if (rank[x] < rank[y])
return parent[x] = y;
else
{
if (rank[x] == rank[y]) ++rank[x];
return parent[y] = x;;
}
}

inline int* getParent() const { return parent; }
inline int* getRank() const { return rank; }
inline unsigned int getSize() const { return size; }
inline unsigned int getCapacity() const { return capacity; }
};
class Rib
{
protected:
unsigned short len;
char begin;
char end;
public:
Rib(char begin = '\0', char end = '\0', short len = 0) // O(1)
: len(len)
{
begin > end ?
(this->begin = end, this->end = begin)
:
(this->begin = begin, this->end = end);
if (len < 0) throw NegativeParameter("constructor", "weight", len);
}
Rib(const Rib& r) // O(1)
: len(r.len), begin(r.begin), end(r.end) {}

inline bool operator >	(const Rib& r) const { return len != r.len ? len > r.len : begin != r.begin ? begin > r.begin : end != r.end ? end > r.end : false; } // O(1)
inline bool operator <	(const Rib& r) const { return len != r.len ? len < r.len : begin != r.begin ? begin < r.begin : end != r.end ? end < r.end : false; } // O(1)
inline bool operator >= (const Rib& r) const { return len != r.len ? len >= r.len
: begin != r.begin ? begin >= r.begin : end != r.end ? end >= r.end : true; } // O(1)
inline bool operator <= (const Rib& r) const { return len != r.len ? len >= r.len
: begin != r.begin ? begin >= r.begin : end != r.end ? end >= r.end : true; } // O(1)
inline bool operator == (const Rib& r) const { return len == r.len && begin == r.begin && end == r.end; } // O(1)
inline bool operator != (const Rib& r) const { return len != r.len || begin !=
r.begin || end != r.end; } // O(1)

inline const Rib operator = (const Rib& rib) // O(1)
{
begin = rib.begin, end = rib.end, len = rib.len;
return *this;
}

friend inline std::ostream& operator << (std::ostream& stream, const Rib& r) // O(1)
{
stream << r.getBegin() << r.getEnd() << "(" << r.getLen() << ")";
return stream;
}
friend inline std::istream& operator >> (std::istream& stream, Rib& r)	// O(1)
{
unsigned short len; char begin, end; stream >> begin >> end >> len; r.setRib(begin, end, len);
return stream;
}


inline void print() const { std::cout << "Rib by name " << begin << end << " = "
<< len << "\n"; } // O(1)

inline unsigned short getLen() const { return len; } // O(1) inline char getBegin() const { return begin; }	// O(1) inline char getEnd() const { return end; }	// O(1)

inline void setBegin(char b) { begin = b; }	// O(1)
inline void setEnd(char e) { end = e; }	// O(1)
inline void setLen(short len)	// O(1)
{
len < 0 ? throw NegativeParameter("setLen", "len", len) : this->len = len;
}
inline void setRib(char begin, char end, short len)	// O(1)
{
begin > end ?
(this->begin = end, this->end = begin)
:
(this->begin = begin, this->end = end); setLen(len);
}
};
template <template <class T> class ContainerRibs, template <class T> class
ContainerPoints> class Graph
{
private:
virtual inline void lake(bool** lakes, int b, int e, unsigned int pcount) const
{
if (lakes[b][e] && lakes[e][b]) return;
lakes[b][e] = lakes[e][b] = true;
for (unsigned int i = 0; i < pcount; ++i) lakes[b][i] || lakes[e][i] ?
(lake(lakes, b, i, pcount), lake(lakes, e, i, pcount))
:
void();
}
virtual inline bool hasLake(ContainerRibs<Rib>& arr, ContainerPoints<char> name)
const
{
auto itR = arr.getBegin();
unsigned int i = 0, j, sizeV = arr.getSize(), pcountV = name.getSize();
bool** lakes = new bool* [pcountV], ret = true; for (; i < pcountV; ++i)
{
lakes[i] = new bool[pcountV]; for (j = 0; j < pcountV; ++j) lakes[i][j] = i == j;
}

for (i = 0; i < sizeV; ++i, ++itR)
lake(lakes, name.FindIndex((*itR).getBegin()), name.FindIndex((*itR).getEnd()), pcountV);

for (i = 0; i < pcountV; ++i)
{
for (j = 0; ret && j < pcountV; ++j) ret = lakes[i][j];
delete[] lakes[i];
}
delete[] lakes;
return ret;
}
virtual inline void setTree(const ContainerRibs<Rib>& arr, const
ContainerPoints<char>& name)
{
this->name = name, this->arr = arr, size = arr.getSize(), pcount = name.getSize();
!hasLake(this->arr, this->name) ? throw IncoherentGraph("setTree") : void();
}

protected:
virtual inline void adding(const Rib& rib, bool unique = false)
{
unique ? arr.PushUnique(rib) : arr.Push(rib); name.Push(rib.getBegin()), name.Push(rib.getEnd()), ++size, pcount =
name.getSize();
}
ContainerRibs<Rib> arr; ContainerPoints<char> name; unsigned short size;	// Nr unsigned short pcount; // Nc
public:
Graph()	// O(1)
: pcount(0), size(0) {}
Graph(Rib* mass, unsigned short size, bool unique = false)
{
if (unique)
for (Rib* value = size > 0 ? mass : NULL, * end = value + size; value != end; ++value)
arr.PushUnique(*value), name.Push(value->getBegin()), name.Push(value-
>getEnd());
else
for (Rib* value = size > 0 ? mass : NULL, * end = value + size; value != end; ++value)
arr.Push(*value), name.Push(value->getBegin()), name.Push(value-
>getEnd());
this->size = arr.getSize(), pcount = name.getSize();
if (!hasLake(arr, name)) throw IncoherentGraph("setRibs");
}
Graph(const Graph& graph) // O(1)
: size(graph.size), pcount(graph.pcount), name(graph.name), arr(graph.arr) {}
virtual inline void clear() { arr.Clear(), name.Clear(), size = pcount = 0; }

virtual inline const Graph operator = (const Graph& graph) // O(1)
{
arr = graph.arr, name = graph.name, size = graph.size, pcount = graph.pcount;
return *this;
}
virtual inline bool operator == (const Graph& graph) const { return arr == graph.getRibs(); }
virtual inline bool operator != (const Graph& graph) const { return arr !=
graph.getRibs(); }
virtual inline Rib	operator [] (int index)	const
{



NULL;

}
index < 0 ? throw NegativeParameter("operator []", "index", index) : (unsigned)index > size ? throw IndexMorethenLenght("operator []", index) :

return arr[index];


inline friend std::ostream& operator << (std::ostream& stream, const Graph& graph)
// O(Nr)
{
unsigned int size = graph.getSize(); stream << size << "\n";
for (unsigned int i = 0; i < size; ++i)
i != size - 1 ? stream << graph[i] << "\n" : stream << graph[i];
return stream;
}
inline friend std::istream& operator >> (std::istream& stream, Graph& graph)
// O(Nr)
{
int len; stream >> len;
ContainerRibs<Rib> arr; ContainerPoints<char> name;
if (len > 0)
{
for (int i = 0; i < len; ++i)
{
Rib r; stream >> r;
arr.Push(r), name.Push(r.getBegin()), name.Push(r.getEnd());
}

graph.setTree(arr, name);
}
return stream;
}

virtual inline void printRib(int index) const // O(Nr)
{
Rib rib = this->operator[](index);
std::cout << "Rib by name " << rib.getBegin() << rib.getEnd() << " = " << rib.getLen() << "\n";
}
virtual inline void printRibs()	const // O(Nr+Nc)
{
std::cout << "Ribs of ";
auto itR = arr.getBegin(); auto itC = name.getBegin();
for (unsigned int i = 0; i < pcount; ++i, ++itC) std::cout << *itC; std::cout << ":\n{ ";
for (unsigned int i = 0; i < size; ++i, ++itR) std::cout << *itR;
std::cout << " }\n";
}

virtual inline ContainerRibs	<Rib> getRibs()	const { return arr; } virtual inline ContainerPoints<char> getName() const { return name; } virtual inline unsigned short getSize()	const { return size; } virtual inline unsigned short getPCount() const { return pcount; } virtual inline unsigned int getWeight()	const
{
unsigned int weight = 0, i = 0; auto itR = arr.getBegin(); for (; i < size; ++i, ++itR) weight += (*itR).getLen(); return weight;
}
inline Graph AlgorithmKruskala()
{
arr.Sorting(), name.Sorting(); Graph min; Rib rib;
int in1, in2; unsigned int maxP = 1, i = 0, j = 0;
auto itR = arr.getBegin(); auto itC = name.getBegin();
char* points = new char[pcount]; unsigned int* classes = new unsigned int[pcount], * countcl = new unsigned int[pcount];
for (; i < pcount; ++i, ++itC)
points[i] = *itC, classes[i] = i, countcl[i] = 1;
for (i = 0; i < size && pcount != maxP; ++i, ++itR)
{
rib = *itR;
in1 = binaryFind(points, rib.getBegin(), pcount), in2 = binaryFind(points, rib.getEnd(), pcount);
if (classes[in1] != classes[in2])
{


void();
min.adding(rib);
countcl[classes[in1]] < countcl[classes[in2]] ? swap(in1, in2) :

++countcl[classes[in1]], --countcl[classes[in2]];
for (j = 0; j < pcount && countcl[classes[in2]] != 0; ++j) classes[j] == classes[in2] && j != in2 ?
(classes[j] = classes[in1], ++countcl[classes[in1]], --

countcl[classes[in2]]) : NULL;
classes[in2] = classes[in1], maxP = countcl[classes[in1]];
}
}
delete[] points, delete[] classes, delete[] countcl;
return min;
}
virtual inline DoubleList<Rib> getMinPathBetween(char beg, char end)
{
auto begin_iter = name.FindIndex(beg); DoubleList<Rib> listPath;
if (size == 0 || begin_iter == -1 || name.FindIndex(end) == -1) return
listPath;
unsigned int* path = new unsigned int[pcount], i = 0;
for (; i < pcount; ++i)
name[i] != beg ? path[i] = -1 : path[i] = 0;

for (DoubleList<char> listVertex(beg); listVertex.getSize() > 0; listVertex.PopFront())
{
char vertex = *listVertex.getBegin();
for (i = 0; i < size; ++i)
{
char first = arr[i].getBegin(), second = arr[i].getEnd();
unsigned int indexF = name.FindIndex(first), indexS = name.FindIndex(second);
if (vertex == first && path[indexS] > arr[i].getLen() + path[indexF])
listVertex.PushUnique(second), path[indexS] = arr[i].getLen() +

path[indexF];
path[indexS]) path[indexS];
}

else if (vertex == second && path[indexF] > arr[i].getLen() + listVertex.PushUnique(first), path[indexF] = arr[i].getLen() +

}
while (beg != end)
for (i = 0; i < size; ++i)
{
char first = arr[i].getBegin(), second = arr[i].getEnd();
unsigned int indexF = name.FindIndex(first), indexS = name.FindIndex(second);
if (end == first && path[indexS] == path[indexF] - arr[i].getLen())
listPath.PushFront(arr[i]), end = second;
else if (end == second && path[indexF] == path[indexS] - arr[i].getLen())
listPath.PushFront(arr[i]), end = first;
}
return listPath;
}

void setRibs(const Vector<Rib>& arr)
{
if (arr.getSize() == 0) return; if (size != 0) clear();
size = arr.getSize();
auto itR = arr.getBegin();
for (unsigned int i = 0; i < size; ++i, ++itR)
this->arr.Push(*itR), name.Push((*itR).getBegin()), name.Push((*itR).getEnd());
pcount = name.getSize();
if (!hasLake(this->arr, name)) throw IncoherentGraph("setRibs");
}
};
class LeanGraph : public Graph <Vector, Vector>
{
public:
LeanGraph() : Graph <Vector, Vector>() {}
LeanGraph(Rib* mass, unsigned short size, bool unique = false) : Graph <Vector, Vector>(mass, size, unique) {}
LeanGraph(const Graph& graph) : Graph <Vector, Vector>(graph) {}

inline LeanGraph AlgorithmKruskala()
{
arr.Sorting(), name.Sorting(); LeanGraph min; int in1, in2;
unsigned short* classes = new unsigned short[pcount], i = 0, j = 0;
for (; i < pcount; ++i) classes[i] = i;
for (i = 0; i < size; ++i)
{
in1 = name.BinaryFind(arr[i].getBegin()), in2 = name.BinaryFind(arr[i].getEnd());
if (classes[in1] != classes[in2])
{
min.adding(arr[i]);
for (j = 0; j < pcount; ++j)
classes[j] == classes[in2] && j != in2 ? (classes[j] = classes[in1]) : NULL;
classes[in2] = classes[in1];

}
}
delete[] classes;
return min;
};
};
class FastGraph : public Graph <Vector, Vector>
{
public:
FastGraph() : Graph <Vector, Vector>() {}
FastGraph(Rib* mass, unsigned short size, bool unique = false) : Graph <Vector, Vector>(mass, size, unique) {}
FastGraph(const Graph& graph) : Graph <Vector, Vector>(graph) {}

inline FastGraph AlgorithmKruskala()
{
arr.Sorting(), name.Sorting();
FastGraph min; DisjoinSetsUnit classes(pcount);
int in1, in2, class1, class2, unionCl; unsigned int maxP = 1, i = 0, * count =
new unsigned int[pcount];
for (; i < pcount; ++i) classes.Push(i), count[i] = 1;
for (Rib* rib = arr.getArray(), *end = rib + size; rib != end && pcount != maxP; ++rib)
{
in1 = name.BinaryFind(rib->getBegin()), in2 = name.BinaryFind(rib->getEnd());
if ((class1 = classes.Find(in1)) != (class2 = classes.Find(in2))) min.adding(*rib), unionCl = classes.Union(in1, in2, true), unionCl == class2 ?
(maxP = count[class2] += count[class1], count[class1] = 0)
:
(maxP = count[class1] += count[class2], count[class2] = 0);
}
classes.Clear(), delete[] count;
return min;
};
};

void lean()
{
LeanGraph graph, Span_Tree; DoubleList<Rib> Path;
std::cout << "\nUser lean graph:\n";
try { std::cin >> graph; }
catch (IncoherentGraph e) { e.what(); return; }
if (graph.getSize() == 0) { std::cout << "\nError: you entered no tree!\n";
return; }
std::cout << "Original weight: " << graph.getWeight() << std::endl;
char begin, end;
Span_Tree = graph.AlgorithmKruskala(); std::cout << "\nUser min spanning tree:\n"; Span_Tree.printRibs();
std::cout << "Min weight: " << Span_Tree.getWeight() << "\n\nEnter the two points between which you want to find the minimum path:\n";
std::cin >> begin >> end;
Path = graph.getMinPathBetween(begin, end);
std::cout << "\nUser min path between: " << begin << " -> " << end << ":\n{ "; for (auto it = Path.getBegin(); it != NULL; ++it) std::cout << *it << " "; std::cout << "}\n";
}
void fast()
{
FastGraph graph, Span_Tree; DoubleList<Rib> Path;
std::cout << "\nUser fast graph:\n";
try { std::cin >> graph; }
catch (IncoherentGraph e) { e.what(); return; }
if (graph.getSize() == 0) { std::cout << "\nError: you entered no tree!\n";
return; }
std::cout << "Original weight: " << graph.getWeight() << std::endl;
char begin, end;

Span_Tree = graph.AlgorithmKruskala(); std::cout << "\nUser min spanning tree:\n"; Span_Tree.printRibs();
std::cout << "Min weight: " << Span_Tree.getWeight() << "\n\nEnter the two points between which you want to find the minimum path:\n";
std::cin >> begin >> end;
Path = graph.getMinPathBetween(begin, end);
std::cout << "\nUser min path between: " << begin << " -> " << end << ":\n{ "; for (auto it = Path.getBegin(); it != NULL; ++it) std::cout << *it << " "; std::cout << "}\n";
}
int main()
{
std::cout << "Attention: before entering the graph yourself, read the instructions for filling in the graph:\n";
std::cout << "Before filling out, you need to choose which graph to use. Write the appropriate symbol(Lean graph: l, Fast graph: f)\n";
std::cout << "First enter the number of ribs of the tree, then enter each rib in this way:\n";
std::cout << "(name (from 2 points) separated by a space his weight).\n"; std::cout << "Then enter the two points between which you want to find the minimum
path!\n";
char choise; std::cin >> choise;
if (choise == 'f' || choise == 'F') fast();
else if (choise == 'l' || choise == 'L') lean(); else std::cout << "\nNo such graph exists!\n"; system("pause"); return 0;
}
