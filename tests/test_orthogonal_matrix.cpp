#include "../include/errors.h"
#include "../include/orthogonal_matrix.h"
#include "test_framework.h"

#include <cmath>

namespace lab3 {
namespace tests {

void TestOrthogonalMatrix() {
    std::printf("\n[OrthogonalMatrix<T>]\n");

    {
        const double id[] = {1,0,0,1};
        OrthogonalMatrix<double> q(2, id);
        T_ASSERT("identity orthogonal", q.IsOrthogonal());
        T_ASSERT_EQ("size", q.GetSize(), 2);
        T_ASSERT_NEAR("diag", q.Get(0, 0), 1.0, 1e-12);
    }

    {
        const double rot[] = {0,-1,1,0};
        OrthogonalMatrix<double> q(2, rot);
        T_ASSERT("rotation orthogonal", q.IsOrthogonal());
        T_ASSERT_NEAR("norm", q.Norm(), std::sqrt(2.0), 1e-9);
    }

    {
        const double h[] = {-1,0,0, 0,1,0, 0,0,1};
        OrthogonalMatrix<double> q(3, h);
        T_ASSERT("householder orthogonal", q.IsOrthogonal());
    }

    {
        const double id3[] = {1,0,0, 0,1,0, 0,0,1};
        OrthogonalMatrix<double> q(3, id3);
        q.Set(0, 0, 0.0);
        T_ASSERT("no longer orthogonal", !q.IsOrthogonal());
    }

    {
        const double data[] = {1,0,0, 0,1,0, 0,0,1};
        OrthogonalMatrix<double> a(3, data);
        OrthogonalMatrix<double> b(a);
        b.Set(1, 1, 0.0);
        T_ASSERT_NEAR("copy independent", a.Get(1, 1), 1.0, 1e-12);
    }

    {
        const double bad[] = {1,1,0,1};
        T_ASSERT_THROWS("not orthogonal throws", lab2::InvalidArgument,
                        OrthogonalMatrix<double>(2, bad));
    }
}

}  // namespace tests
}  // namespace lab3
