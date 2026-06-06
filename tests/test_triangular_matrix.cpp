#include "../include/errors.h"
#include "../include/triangular_matrix.h"
#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestTriangularMatrix() {
    std::printf("\n[TriangularMatrix<T>]\n");

    {
        const int data[] = {1,2,3, 0,4,5, 0,0,6};
        TriangularMatrix<int> u(3, TriKind::Upper, data);
        T_ASSERT("upper kind", u.GetKind() == TriKind::Upper);
        T_ASSERT_EQ("upper (0,2)", u.Get(0, 2), 3);
        T_ASSERT_EQ("upper zero below", u.Get(2, 0), 0);
    }

    {
        const int data[] = {1,0,0, 2,3,0, 4,5,6};
        TriangularMatrix<int> l(3, TriKind::Lower, data);
        T_ASSERT("lower kind", l.GetKind() == TriKind::Lower);
        T_ASSERT_EQ("lower (2,1)", l.Get(2, 1), 5);
        T_ASSERT_EQ("lower zero above", l.Get(0, 1), 0);
    }

    {
        const int a[] = {1,2,0, 0,3,4, 0,0,5};
        const int b[] = {1,1,0, 0,1,1, 0,0,1};
        TriangularMatrix<int> u1(3, TriKind::Upper, a);
        TriangularMatrix<int> u2(3, TriKind::Upper, b);
        u1.AddMatrix(u2);
        T_ASSERT_EQ("add (0,1)", u1.Get(0, 1), 3);
        T_ASSERT_EQ("add (1,2)", u1.Get(1, 2), 5);
    }

    {
        const double data[] = {3,4,0, 0,0,0, 0,0,0};
        TriangularMatrix<double> u(3, TriKind::Upper, data);
        T_ASSERT_NEAR("norm 3-4", u.Norm(), 5.0, 1e-9);
    }

    {
        const int data[] = {1,2,0, 0,3,4, 0,0,5};
        TriangularMatrix<int> u(3, TriKind::Upper, data);
        u.MulScalar(2);
        T_ASSERT_EQ("scalar (0,1)", u.Get(0, 1), 4);
        T_ASSERT_EQ("scalar zero stays", u.Get(2, 0), 0);
    }

    {
        const int bad[] = {1,0,0, 9,3,0, 0,0,4};
        T_ASSERT_THROWS("bad upper data", lab2::InvalidArgument,
                        TriangularMatrix<int>(3, TriKind::Upper, bad));
    }

    {
        const int a[] = {1,2,0, 0,3,0, 0,0,4};
        const int b[] = {1,0,0, 2,3,0, 4,5,6};
        TriangularMatrix<int> u(3, TriKind::Upper, a);
        TriangularMatrix<int> l(3, TriKind::Lower, b);
        T_ASSERT_THROWS("kind mismatch", lab2::InvalidArgument, u.AddMatrix(l));
    }

    {
        const int data[] = {1,2,0, 0,3,4, 0,0,5};
        TriangularMatrix<int> u(3, TriKind::Upper, data);
        T_ASSERT_THROWS("set below upper", lab2::InvalidArgument, u.Set(1, 0, 7));
    }
}

}  // namespace tests
}  // namespace lab3
