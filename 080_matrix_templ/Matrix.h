#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(vector<vector<T> >()) {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(vector<vector<T> >()) {
    rows.resize(numRows);
    typename vector<vector<T> >::iterator it = rows.begin();
    while (it != rows.end()) {
      it->resize(numColumns);
      ++it;
    }
  }

  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}

  ~Matrix() {}

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      numColumns = rhs.numColumns;
      numRows = rhs.numRows;
      rows = rhs.rows;
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const vector<T> & operator[](int index) const {
    assert((0 <= index) && (index < numRows));
    return rows[index];
  }

  vector<T> & operator[](int index) {
    assert((0 <= index) && (index < numRows));
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const { return rows == rhs.rows; }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert((numColumns == rhs.numColumns) && (numRows == rhs.numRows));
    Matrix<T> ans(numRows, numColumns);
    typename vector<vector<T> >::const_iterator thisIt = rows.begin();
    typename vector<vector<T> >::const_iterator rhsIt = rhs.rows.begin();
    typename vector<vector<T> >::iterator ansIt = ans.rows.begin();
    while (ansIt != ans.rows.end()) {
      typename vector<T>::const_iterator thisColIt = thisIt->begin();
      typename vector<T>::const_iterator rhsColIt = rhsIt->begin();
      typename vector<T>::iterator ansColIt = ansIt->begin();
      while (ansColIt != ansIt->end()) {
        *ansColIt = *thisColIt + *rhsColIt;
        ++ansColIt;
        ++thisColIt;
        ++rhsColIt;
      }
      ++ansIt;
      ++thisIt;
      ++rhsIt;
    }
    return ans;
  }
};

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs) {
  s << "[";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++) {
      s << rhs[i][j];
      if (j != rhs.getColumns() - 1) {
        s << ", ";
      }
    }
    s << "}";
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << "]";
  return s;
}

#endif
