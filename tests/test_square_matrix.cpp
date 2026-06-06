#include "../include/errors.h"
#include "../include/square_matrix.h"
#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestSquareMatrix() {
    std::printf("\n[SquareMatrix<T>]\n");

    {
        SquareMatrix<int> m(3);
        T_ASSERT_EQ("size", m.GetSize(), 3);
    }

    {
        const int data[] = {1, 2, 3, 4};
        SquareMatrix<int> m(2, data);
        T_ASSERT_EQ("from-array", m.Get(1, 0), 3);
    }

    {
        T_ASSERT_THROWS("neg size", lab2::InvalidArgument, SquareMatrix<int>(-1));
    }

    {
        SquareMatrix<int> id = SquareMatrix<int>::Identity(3);
        T_ASSERT_EQ("identity (0,0)", id.Get(0, 0), 1);
        T_ASSERT_EQ("identity off-diag", id.Get(0, 1), 0);
    }

    {
        const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        SquareMatrix<int> m(3, data);
        T_ASSERT_EQ("trace 3x3", m.Trace(), 1 + 5 + 9);
    }

    {
        const int a[] = {1, 2, 3, 4};
        const int b[] = {10, 20, 30, 40};
        SquareMatrix<int> m1(2, a);
        SquareMatrix<int> m2(2, b);
        m1.AddMatrix(m2);
        T_ASSERT_EQ("inherited add", m1.Get(0, 0), 11);
    }

    {
        const int data[] = {1, 2, 3, 4};
        SquareMatrix<int> a(2, data);
        SquareMatrix<int> b(a);
        b.Set(0, 0, 99);
        T_ASSERT_EQ("copy independent", a.Get(0, 0), 1);
    }
}

}  // namespace tests
}  // namespace lab3
