#include "../include/errors.h"
#include "../include/rectangular_matrix.h"
#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestRectangularMatrix() {
    std::printf("\n[RectangularMatrix<T>]\n");

    {
        RectangularMatrix<int> m(2, 3);
        T_ASSERT_EQ("rows", m.GetRows(), 2);
        T_ASSERT_EQ("cols", m.GetCols(), 3);
        T_ASSERT_EQ("default zero", m.Get(1, 2), 0);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        RectangularMatrix<int> m(2, 3, data);
        T_ASSERT_EQ("from-array (0,0)", m.Get(0, 0), 1);
        T_ASSERT_EQ("from-array (1,1)", m.Get(1, 1), 5);
        T_ASSERT_EQ("from-array (1,2)", m.Get(1, 2), 6);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        RectangularMatrix<int> a(2, 3, data);
        RectangularMatrix<int> b(a);
        b.Set(0, 0, 99);
        T_ASSERT_EQ("copy independent", a.Get(0, 0), 1);
        T_ASSERT_EQ("copy value", b.Get(0, 0), 99);
    }

    {
        const int a[] = {1, 2, 3, 4};
        const int b[] = {5, 6, 7, 8};
        RectangularMatrix<int> m1(2, 2, a);
        RectangularMatrix<int> m2(2, 2, b);
        m1.AddMatrix(m2);
        T_ASSERT_EQ("add (0,0)", m1.Get(0, 0), 6);
        T_ASSERT_EQ("add (1,1)", m1.Get(1, 1), 12);
    }

    {
        const int data[] = {2, 4, 6, 8};
        RectangularMatrix<int> m(2, 2, data);
        m.MulScalar(3);
        T_ASSERT_EQ("scalar (0,0)", m.Get(0, 0), 6);
        T_ASSERT_EQ("scalar (1,1)", m.Get(1, 1), 24);
    }

    {
        const double data[] = {3.0, 4.0};
        RectangularMatrix<double> m(1, 2, data);
        T_ASSERT_NEAR("norm 3-4", m.Norm(), 5.0, 1e-9);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        RectangularMatrix<int> m(2, 3, data);
        m.SwapRows(0, 1);
        T_ASSERT_EQ("swap rows (0,0)", m.Get(0, 0), 4);
        T_ASSERT_EQ("swap rows (1,2)", m.Get(1, 2), 3);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6};
        RectangularMatrix<int> m(2, 3, data);
        m.SwapCols(0, 2);
        T_ASSERT_EQ("swap cols (0,0)", m.Get(0, 0), 3);
        T_ASSERT_EQ("swap cols (0,2)", m.Get(0, 2), 1);
    }

    {
        const int data[] = {1, 2, 3, 4};
        RectangularMatrix<int> m(2, 2, data);
        m.AddRowMultiplied(1, 0, -3);
        T_ASSERT_EQ("elem row (1,0)", m.Get(1, 0), 0);
        T_ASSERT_EQ("elem row (1,1)", m.Get(1, 1), -2);
    }

    {
        T_ASSERT_THROWS("neg size", lab2::InvalidArgument,
                        RectangularMatrix<int>(-1, 2));
    }

    {
        const int a[] = {1, 2};
        const int b[] = {1, 2, 3};
        RectangularMatrix<int> m1(1, 2, a);
        RectangularMatrix<int> m2(1, 3, b);
        T_ASSERT_THROWS("add mismatch", lab2::InvalidArgument, m1.AddMatrix(m2));
    }
}

}  // namespace tests
}  // namespace lab3
