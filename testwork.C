
#include "testwork.h"

template <typename T>
void examinevector(std::vector<T> &)
{}


template
void examinevector(std::vector<std::size_t> &);

template
void examinevector(std::vector<std::ptrdiff_t> &);

template
void examinevector(std::vector<unsigned int> &);

template
void examinevector(std::vector<int> &);
