#ifndef LAB3_CONSOLE_UI_H
#define LAB3_CONSOLE_UI_H

#include "../include/diagonal_matrix.h"
#include "../include/matrix.h"
#include "../include/orthogonal_matrix.h"
#include "../include/rectangular_matrix.h"
#include "../include/sparse_matrix.h"
#include "../include/square_matrix.h"
#include "../include/triangular_matrix.h"

namespace lab3 {

class ConsoleUi {
public:
    ConsoleUi();
    ~ConsoleUi();

    void Run();

private:
    enum MatrixKind {
        kRectangular  = 1,
        kSquare       = 2,
        kSparse       = 3,
        kUpperTri     = 4,
        kLowerTri     = 5,
        kDiagonal     = 6,
        kOrthogonal   = 7
    };

    void PrintMenu() const;

    void RunTests();
    void MakeDenseMatrix(int slot);
    void MakeSparseMatrix();
    void ShowMatrices() const;
    void AddMatrices();
    void MulScalarMenu();
    void NormMenu();
    void SwapRowsMenu();
    void SwapColsMenu();
    void MulRowMenu();
    void MulColMenu();
    void AddRowMenu();
    void AddColMenu();
    void TraceMenu();
    void IdentityMenu();
    void MultiplySparseMenu();
    void OrthogonalCheckMenu();
    void DropSlot();

    Matrix<double>* ReadDenseMatrix();
    void PrintDenseMatrix(const char* label, const Matrix<double>* m) const;
    void PrintSparseMatrix(const char* label, const SparseMatrix<double>* m) const;
    void ReplaceSlot(int slot, Matrix<double>* value);
    int ReadInt(const char* prompt) const;
    double ReadDouble(const char* prompt) const;
    int ReadMenuChoice() const;
    Matrix<double>*& SlotRef(int slot);

    Matrix<double>*       slot_a_;
    Matrix<double>*       slot_b_;
    SparseMatrix<double>* sparse_a_;
    SparseMatrix<double>* sparse_b_;
};

}  // namespace lab3

#endif
