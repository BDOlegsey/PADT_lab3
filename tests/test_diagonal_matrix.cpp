#include "../include/diagonal_matrix.h"
#include "../include/errors.h"
#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestDiagonalMatrix() {
    std::printf("\n[DiagonalMatrix<T>]\n");

    {
        DiagonalMatrix<int> d(3);
        T_ASSERT_EQ("zero (0,0)", d.Get(0, 0), 0);
        T_ASSERT_EQ("zero off-diag", d.Get(0, 1), 0);
    }

    {
        const int data[] = {1,0,0, 0,2,0, 0,0,3};
        DiagonalMatrix<int> d(3, data);
        T_ASSERT_EQ("from-array (0,0)", d.Get(0, 0), 1);
        T_ASSERT_EQ("from-array (2,2)", d.Get(2, 2), 3);
        T_ASSERT_EQ("off-diag zero", d.Get(0, 1), 0);
    }

    {
        const int a[] = {1,0,0, 0,2,0, 0,0,3};
        const int b[] = {4,0,0, 0,5,0, 0,0,6};
        DiagonalMatrix<int> d1(3, a);
        DiagonalMatrix<int> d2(3, b);
        d1.AddMatrix(d2);
        T_ASSERT_EQ("add (0,0)", d1.Get(0, 0), 5);
        T_ASSERT_EQ("add (1,1)", d1.Get(1, 1), 7);
        T_ASSERT_EQ("off stays 0", d1.Get(0, 1), 0);
    }

    {
        const int data[] = {2,0,0, 0,4,0, 0,0,6};
        DiagonalMatrix<int> d(3, data);
        d.MulScalar(3);
        T_ASSERT_EQ("scalar (0,0)", d.Get(0, 0), 6);
        T_ASSERT_EQ("scalar (2,2)", d.Get(2, 2), 18);
    }

    {
        const double data[] = {3,0, 0,4};
        DiagonalMatrix<double> d(2, data);
        T_ASSERT_NEAR("norm", d.Norm(), 5.0, 1e-9);
    }

    {
        DiagonalMatrix<int> d(3);
        d.Set(1, 1, 42);
        T_ASSERT_EQ("set diag", d.Get(1, 1), 42);
        T_ASSERT_THROWS("set off-diag", lab2::InvalidArgument, d.Set(0, 1, 5));
    }

    {
        const int bad[] = {1,0,0, 0,2,7, 0,0,3};
        T_ASSERT_THROWS("bad data", lab2::InvalidArgument,
                        DiagonalMatrix<int>(3, bad));
    }

    {
        const int a[] = {1,0,0, 0,2,0, 0,0,3};
        DiagonalMatrix<int> d(3, a);
        SquareMatrix<int> sq(3, a);
        T_ASSERT_THROWS("not diagonal", lab2::InvalidArgument, d.AddMatrix(sq));
    }
}

}  // namespace tests
}  // namespace lab3
