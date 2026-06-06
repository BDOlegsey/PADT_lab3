#include "../include/errors.h"
#include "../include/matrix.h"
#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestMatrix() {
    std::printf("\n[Matrix<T>]\n");

    {
        Matrix<int> m(2, 3);
        T_ASSERT_EQ("default zero (0,0)", m.Get(0, 0), 0);
        T_ASSERT_EQ("rows", m.GetRows(), 2);
        T_ASSERT_EQ("cols", m.GetCols(), 3);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        Matrix<int> m(2, 3, data);
        T_ASSERT_EQ("from-array (0,0)", m.Get(0, 0), 1);
        T_ASSERT_EQ("from-array (1,2)", m.Get(1, 2), 6);
    }

    {
        Matrix<int> m(2, 2);
        T_ASSERT_THROWS("oob row", lab2::IndexOutOfRange, m.Get(2, 0));
        T_ASSERT_THROWS("oob col", lab2::IndexOutOfRange, m.Get(0, 2));
        T_ASSERT_THROWS("neg row", lab2::IndexOutOfRange, m.Get(-1, 0));
    }

    {
        T_ASSERT_THROWS("neg size", lab2::InvalidArgument, Matrix<int>(-1, 2));
        T_ASSERT_THROWS("zero/nonzero", lab2::InvalidArgument, Matrix<int>(0, 2));
    }

    {
        const int a[] = {1, 2, 3, 4};
        const int b[] = {10, 20, 30, 40};
        Matrix<int> m1(2, 2, a);
        Matrix<int> m2(2, 2, b);
        m1.AddMatrix(m2);
        T_ASSERT_EQ("add 00", m1.Get(0, 0), 11);
        T_ASSERT_EQ("add 11", m1.Get(1, 1), 44);
    }

    {
        const int a[] = {1, 2};
        const int b[] = {1, 2, 3};
        Matrix<int> m1(1, 2, a);
        Matrix<int> m2(1, 3, b);
        T_ASSERT_THROWS("add mismatch", lab2::InvalidArgument, m1.AddMatrix(m2));
    }

    {
        const int a[] = {1, 2, 3, 4};
        Matrix<int> m(2, 2, a);
        m.MulScalar(3);
        T_ASSERT_EQ("scalar 00", m.Get(0, 0), 3);
        T_ASSERT_EQ("scalar 11", m.Get(1, 1), 12);
    }

    {
        const double data[] = {3.0, 4.0};
        Matrix<double> m(1, 2, data);
        T_ASSERT_NEAR("norm 3-4", m.Norm(), 5.0, 1e-9);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        Matrix<int> m(2, 3, data);
        m.SwapRows(0, 1);
        T_ASSERT_EQ("swap rows (0,0)", m.Get(0, 0), 4);
        T_ASSERT_EQ("swap rows (1,2)", m.Get(1, 2), 3);
        T_ASSERT_THROWS("swap rows oob", lab2::IndexOutOfRange, m.SwapRows(0, 5));
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        Matrix<int> m(2, 3, data);
        m.SwapCols(0, 2);
        T_ASSERT_EQ("swap cols (0,0)", m.Get(0, 0), 3);
        T_ASSERT_EQ("swap cols (0,2)", m.Get(0, 2), 1);
    }

    {
        const int data[] = {1, 2, 3, 4};
        Matrix<int> m(2, 2, data);
        m.MulRow(0, 10);
        T_ASSERT_EQ("mul row 0,0", m.Get(0, 0), 10);
        T_ASSERT_THROWS("mul row oob", lab2::IndexOutOfRange, m.MulRow(5, 1));
    }

    {
        const int data[] = {1, 2, 3, 4};
        Matrix<int> m(2, 2, data);
        m.AddRowMultiplied(1, 0, -3);
        T_ASSERT_EQ("zero out (1,0)", m.Get(1, 0), 0);
        T_ASSERT_EQ("zero out (1,1)", m.Get(1, 1), -2);
        T_ASSERT_THROWS("self row add", lab2::InvalidArgument, m.AddRowMultiplied(0, 0, 1));
    }

    {
        const int data[] = {1, 2, 3, 4};
        Matrix<int> a(2, 2, data);
        Matrix<int> b(a);
        T_ASSERT("copy equals", a.Equals(b));
        b.Set(0, 0, 99);
        T_ASSERT("copy is independent", a.Get(0, 0) == 1 && b.Get(0, 0) == 99);
    }

    {
        Matrix<int> m(0, 0);
        T_ASSERT_EQ("empty rows", m.GetRows(), 0);
        T_ASSERT_NEAR("empty norm", m.Norm(), 0.0, 1e-9);
    }
}

}  // namespace tests
}  // namespace lab3
