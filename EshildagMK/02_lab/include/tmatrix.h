// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
//eshildag mk
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
    explicit TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("sz = 0 / sz > maxsize");
    pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      if (sz == 0 || sz > MAX_VECTOR_SIZE) {
          throw out_of_range("sz = 0 / sz > maxsize");
      }
      if (arr == nullptr) throw("nullptr");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector<T>& v) : sz(v.size())
  {
      T* new_pMem = new T[sz];
      try {
          std::copy(v.pMem, v.pMem + sz, new_pMem);
      }
      catch (...) {
          delete[] new_pMem;
          throw;
      }
      pMem = new_pMem;
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.size()), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      if (this->sz != v.sz) {
        delete[] pMem;
        this->sz = v.sz;
        pMem = new T[sz];
      }
      for (int i = 0; i < sz; i++) {
        pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      delete[] pMem;

      sz = v.sz;
      pMem = v.pMem;

      v.sz = 0;
      v.pMem = nullptr;

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("ind >= sz");
      }
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("ind >= sz");
      }
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("ind >= sz");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("ind >= sz");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (v.sz != this->sz) return false;
      for (int i = 0; i < sz; i++) {
          if (v.pMem[i] != this->pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !((*this) == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val) const
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] += val;
      }
      return res;
  }
  TDynamicVector operator-(T val) const
  {
      return (*this) + (val * (-1));
  }
  TDynamicVector operator*(T val) const
  {
      TDynamicVector v1(*this);
      for (int i = 0; i < sz; i++) {
          v1.pMem[i] *= val;
      }

      return v1;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const
  {
      if (v.sz != this->sz) throw invalid_argument("err");
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = this->pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v) const
  {
      return (*this) + (v * (-1));
  }
  T operator*(const TDynamicVector& v) const
  {
      if (sz != v.sz) throw invalid_argument("sz != v.sz");
      T res = T();
      for (int i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
      ostr << "{";
      bool first = true;
      for (size_t i = 0; i < v.sz; i++)
          if (!first) {
              ostr << ", " << v.pMem[i];
          }
          else {
              ostr << v.pMem[i];
              first = false;
          }
      ostr << "}";
      return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;

    explicit TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
        if (sz == 0 || sz > MAX_MATRIX_SIZE) {
            throw out_of_range("Incorrect matrix size");
        }
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz - i);
        }
    }

    size_t getDimension() const {
        return sz;
    }

    // сравнение
   bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m[i]) return false;
      }
      return true;
  }

   bool operator!=(const TDynamicMatrix& m) const noexcept
   {
       return !((*this) == m);
   }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] * val;
      }

      return res;
  }
  TDynamicMatrix operator+(const T& val) const
  {
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] + val;
      }

      return res;
  }
  TDynamicMatrix operator-(const T& val) const
  {

      return (*this) + (val * (-1));
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (sz != v.size()) throw invalid_argument("sz != v.size()");

      TDynamicVector<T> res(sz);

      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz - i; j++) {
              res[i] += this->pMem[i][j] * v[i + j];
          }
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
      if (sz != m.sz) throw invalid_argument("sz != m.sz");

      TDynamicMatrix res(*this);

      for (int i = 0; i < sz; i++) {
          res[i] = res[i] + m[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) const  
  {
      if (sz != m.sz) throw invalid_argument("sz != m.sz");
      return (*this) + (m * (-1));
  }

  TDynamicMatrix<T> operator*(const TDynamicMatrix& m) const
  {
      if (sz != m.sz) throw invalid_argument("sz != v.sz");
      TDynamicMatrix<T> res(sz);

      for (size_t i = 0; i < sz; i++) 
      {
          for (size_t j = 0; j < sz-i; j++) 
          {
              for (size_t k = 0; k <= j; k++) 
              {
                  res[i][j] += pMem[i][k] * m.pMem[i + k][j - k];
              }
          }
      }
      return res;
  }
  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.getDimension(); i++) {
          istr >> v[i];
      }
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.getDimension(); i++) {
          for (size_t j = 0; j < i; j++) { ostr << "   "; }
          ostr << v[i] << std::endl;
      }
      return ostr;
  }
};

#endif
