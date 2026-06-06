#include "../include/errors.h"
#include "../include/sparse_matrix.h"
#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestSparseMatrix() {
    std::printf("\n[SparseMatrix<T>]\n");

    {
        SparseMatrix<int> m(3, 3);
        T_ASSERT_EQ("nnz empty", m.GetNnz(), 0);
        T_ASSERT_EQ("implicit zero", m.Get(1, 2), 0);
    }

    {
        SparseMatrix<int> m(3, 3);
        m.Set(0, 1, 5);
        m.Set(2, 2, 7);
        T_ASSERT_EQ("nnz after set", m.GetNnz(), 2);
        T_ASSERT_EQ("get stored", m.Get(0, 1), 5);
        T_ASSERT_EQ("get absent", m.Get(1, 0), 0);
        m.Set(0, 1, 0);
        T_ASSERT_EQ("nnz after erase", m.GetNnz(), 1);
    }

    {
        const int data[] = {1,0,0, 0,2,0, 0,0,3};
        SparseMatrix<int> a(3, 3, data);
        T_ASSERT_EQ("from-array nnz", a.GetNnz(), 3);
        T_ASSERT_EQ("from-array (1,1)", a.Get(1, 1), 2);
    }

    {
        const int data[] = {1,0,0, 0,2,0, 0,0,3};
        SparseMatrix<int> a(3, 3, data);
        SparseMatrix<int> b(3, 3, data);
        a.AddMatrix(b);
        T_ASSERT_EQ("add (0,0)", a.Get(0, 0), 2);
        T_ASSERT_EQ("add (1,1)", a.Get(1, 1), 4);
        T_ASSERT_EQ("add zero stays", a.Get(0, 1), 0);
    }

    {
        const int data[] = {1,0,0, 0,2,0, 0,0,3};
        SparseMatrix<int> m(3, 3, data);
        m.MulScalar(0);
        T_ASSERT_EQ("mul by 0 nnz", m.GetNnz(), 0);
    }

    {
        const int data[] = {2,0,0, 0,3,0, 0,0,4};
        SparseMatrix<int> m(3, 3, data);
        m.MulScalar(2);
        T_ASSERT_EQ("scalar (0,0)", m.Get(0, 0), 4);
        T_ASSERT_EQ("scalar (2,2)", m.Get(2, 2), 8);
    }

    {
        const double data[] = {3,0, 0,4};
        SparseMatrix<double> m(2, 2, data);
        T_ASSERT_NEAR("norm", m.Norm(), 5.0, 1e-9);
    }

    {
        const int da[] = {1,0, 0,1};
        const int db[] = {0,5, 3,0};
        SparseMatrix<int> a(2, 2, da);
        SparseMatrix<int> b(2, 2, db);
        SparseMatrix<int> c = a.Multiply(b);
        T_ASSERT_EQ("mul identity row0", c.Get(0, 1), 5);
        T_ASSERT_EQ("mul identity row1", c.Get(1, 0), 3);
    }

    {
        const int a[] = {1,0,0, 0,1,0};
        const int b[] = {1,0, 0,1, 0,0};
        SparseMatrix<int> ma(2, 3, a);
        SparseMatrix<int> mb(3, 2, b);
        SparseMatrix<int> mc = ma.Multiply(mb);
        T_ASSERT_EQ("mul 2x3*3x2 (0,0)", mc.Get(0, 0), 1);
        T_ASSERT_EQ("mul 2x3*3x2 (1,1)", mc.Get(1, 1), 1);
    }

    {
        SparseMatrix<int> a(2, 3);
        SparseMatrix<int> b(2, 2);
        T_ASSERT_THROWS("mul shape mismatch", lab2::InvalidArgument, a.Multiply(b));
    }

    {
        SparseMatrix<int> a(2, 2);
        SparseMatrix<int> b(3, 3);
        T_ASSERT_THROWS("add mismatch", lab2::InvalidArgument, a.AddMatrix(b));
    }

    {
        SparseMatrix<int> m(3, 3);
        T_ASSERT_THROWS("get oob", lab2::IndexOutOfRange, m.Get(3, 0));
        T_ASSERT_THROWS("set oob", lab2::IndexOutOfRange, m.Set(0, 5, 1));
    }
}

}  // namespace tests
}  // namespace lab3
