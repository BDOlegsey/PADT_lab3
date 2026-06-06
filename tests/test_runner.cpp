#include "test_framework.h"

namespace lab3 {
namespace tests {

void TestMatrix();
void TestSquareMatrix();
void TestRectangularMatrix();
void TestSparseMatrix();
void TestTriangularMatrix();
void TestDiagonalMatrix();
void TestOrthogonalMatrix();

void RunAllTests() {
    ResetCounters();

    TestMatrix();
    TestSquareMatrix();
    TestRectangularMatrix();
    TestSparseMatrix();
    TestTriangularMatrix();
    TestDiagonalMatrix();
    TestOrthogonalMatrix();

    std::printf("\n");
    PrintSummary();
}

}  // namespace tests
}  // namespace lab3
