/**
 *  TODO:
 *  1. Create include guard / header guard
 *  2. Define the class 'Vector'
 *  3. Declare necessary members
 *  4. Define templated member functions in this file
 */
#ifndef VECTOR_H
#define VECTOR_H
template <typename T>
class Vector
{
private:
    T *m_elements;      // Den underliggande arrayen som innehåller alla objekt.
    int m_nrOfElements; // Antalet element i arrayen som för tillfället används.
    int m_capacity;     // Antalet platser som för tillfället är allokerat för den underliggande arrayen.

    // Resize function
    void resize(int newCapacity);

    const static int DEFAULT_SIZE = 25;

public:
    Vector();                                       // Initerar vektorn med en standardstorlek.
    ~Vector();                                      // Sätter vektorn i ett förstörbart skick.
    Vector(const Vector &other);                    // Initierar vektorn som en kopia av en annam vektor.
    Vector &operator=(const Vector &other);         // Gör den tilldelade vektorn till en kopia av en annan vektor.
    Vector(Vector &&other);                         // Vektorn initieras och tar över ansvaret av allt innehåll från en annan vektor. Den andra vektorn ska lämnas i ett förstörbart skick.
    Vector &operator=(Vector &&other);              // Vektorn tar över ansvaret av allt innehåll från en annan vektor. Den andra vektorn ska lämnas i ett förstörbart skick.
    T &at(const int index) const;                   // Returnerar ett specifikt element på giltigt index.
    T &operator[](const int index) const;           // Returnerar ett specifikt element på giltigt index.
    T &front() const;                               // Returnerar det första elementet i vektorn.
    T &back() const;                                // Returnerar det sista elementet i vektorn.
    const T *data() const;                          // Returnerar en konstantpekare till den underliggande arrayen.
    int size() const;                               // Returnerar antalet objekt som för tillfället finns sparade som element i vektorn.
    int capacity() const;                           // Returnerar kapaciteten på den underliggande arrayen. Notera att arrayen kan innehålla platser som inte används.
    bool empty() const;                             // Returnerar true om vektorn inte innehåller några objekt, annars false.
    void clear();                                   // Tömmer vektorn på alla objekt.
    void insert(const int index, const T &element); // Placerar ett nytt objekt på ett giltigt index. Det ska vara möjligt lägga till ett objekt först, sist, eller någonstans i mitten av vektorn.
    void erase(const int index);                    // Tar bort ett objekt från ett giltigt index.
    void push_back(const T &element);               // Placerar ett nytt objekt längst bak i vektorn.
    void pop_back();                                // Tar bort det sista objekt i vektorn.
};
#endif /*VECTOR_H*/

template <typename T>
inline Vector<T>::Vector()
{
    this->m_capacity = DEFAULT_SIZE;
    this->m_nrOfElements = 0;
    this->m_elements = new T[this->m_capacity];
}
template <typename T>
inline Vector<T>::~Vector()
{
    delete[] this->m_elements;
}

template <typename T>
inline Vector<T>::Vector(const Vector &other)
{
    delete[] this->m_elements;
    this->m_capacity = other.m_capacity;
    this->m_nrOfElements = other.m_nrOfElements;
    this->m_elements = new T[this->m_capacity];
    for (int i = 0; i < this->m_nrOfElements; i++)
    {
        this->m_elements[i] = other.m_elements[i];
    }
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other)
{
    if (this != &other)
    {
        delete[] this->m_elements;
        this->m_capacity = other.m_capacity;
        this->m_nrOfElements = other.m_nrOfElements;
        this->m_elements = new T[this->m_capacity];
        for (int i = 0; i < this->m_nrOfElements; i++)
        {
            this->m_elements[i] = other.m_elements[i];
        }
    }
    return *this;
}

template <typename T>
inline Vector<T>::Vector(Vector<T> &&other)
{
    this->m_capacity = other.m_capacity;
    this->m_nrOfElements = other.m_nrOfElements;
    this->m_elements = other.m_elements;
    other.m_elements = nullptr;
}

template <typename T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this != &other)
    {
        delete[] this->m_elements;
        this->m_capacity = other.m_capacity;
        this->m_nrOfElements = other.m_nrOfElements;
        this->m_elements = new T[this->m_capacity];
        for (int i = 0; i < this->m_nrOfElements; i++)
        {
            this->m_elements[i] = other.m_elements[i];
        }
    }
    return *this;
}

template <typename T>
inline T &Vector<T>::at(const int index) const
{
    if (index < 0 || index >= this->m_nrOfElements)
    {
        throw std::out_of_range("Index out of range.");
    }
    return this->m_elements[index];
}

template <typename T>
inline T &Vector<T>::operator[](const int index) const
{
    if (index < 0 || index >= this->m_nrOfElements)
    {
        throw std::out_of_range("Index out of range.");
    }
    return this->m_elements[index];
}

template <typename T>
inline T &Vector<T>::front() const
{
    if (this->m_nrOfElements == 0)
    {
        throw std::out_of_range("Vector is empty.");
    }
    return this->m_elements[0];
}
template <typename T>
inline T &Vector<T>::back() const
{
    if (this->m_nrOfElements == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return this->m_elements[this->m_nrOfElements - 1];
}
// Function to return constant pointer to m_elements
template <typename T>
inline const T *Vector<T>::data() const
{
    return this->m_elements;
}

// Returnerar kapaciteten på den underliggande arrayen. Notera att arrayen kan innehålla platser som inte används.
template <typename T>
int Vector<T>::size() const
{
    return this->m_nrOfElements;
}
template <typename T>
inline int Vector<T>::capacity() const
{
    return this->m_capacity;
}
template <typename T>
inline bool Vector<T>::empty() const
{
    return this->m_nrOfElements == 0;
}
// Tömmer vektorn på alla objekt.
template <typename T>
inline void Vector<T>::clear()
{
    delete[] this->m_elements;
    this->m_elements = new T[this->m_capacity];
}
// Placerar ett nytt objekt på ett giltigt index. Det ska vara möjligt lägga till ett objekt först, sist, eller någonstans i mitten av vektorn.
template <typename T>
inline void Vector<T>::insert(const int index, const T &element)
{
    // Inderts item at index, bumping other items up
    if (index < 0 || index > this->m_nrOfElements)
    {
        throw std::out_of_range("Index out of range");
    }
    if (this->m_nrOfElements == this->m_capacity)
    {
        this->resize(this->m_capacity * 2);
    }

    for (int i = this->m_nrOfElements; i > index; i--)
    {
        this->m_elements[i] = this->m_elements[i - 1];
    }
    this->m_elements[index] = element;
    this->m_nrOfElements++;
}
// Tar bort ett objekt från ett giltigt index.
template <typename T>
inline void Vector<T>::erase(const int index)
{
    if (index > this->m_nrOfElements)
    {
        throw std::out_of_range("Index out of range");
    }

    for (int i = index; i < this->m_nrOfElements; i++)
    {
        this->m_elements[i] = this->m_elements[i + 1];
    }
    this->m_nrOfElements--;
}
// Placerar ett nytt objekt längst bak i vektorn.
template <typename T>
inline void Vector<T>::push_back(const T &element)
{
    if (this->m_nrOfElements == this->m_capacity)
    {
        this->resize(this->m_capacity * 2);
    }
    this->m_elements[this->m_nrOfElements++] = element;
}
template <typename T>
inline void Vector<T>::pop_back()
{

    if (this->m_nrOfElements == 0)
    {
        return;
    }
    else
    {
        this->m_nrOfElements--;
    }
}
template <typename T>
inline void Vector<T>::resize(int newSize)
{
    T *newElements = new T[newSize];
    for (int i = 0; i < m_nrOfElements; i++)
    {
        newElements[i] = m_elements[i];
    }
    delete[] m_elements;
    m_elements = newElements;
    m_capacity = newSize;
}