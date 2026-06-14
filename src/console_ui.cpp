#include "console_ui.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/errors.h"

namespace lab3 {
namespace tests {
void RunAllTests();
}
}  // namespace lab3

namespace lab3 {

ConsoleUi::ConsoleUi()
    : slot_a_(nullptr), slot_b_(nullptr),
      sparse_a_(nullptr), sparse_b_(nullptr) {}

ConsoleUi::~ConsoleUi() {
    delete slot_a_;
    delete slot_b_;
    delete sparse_a_;
    delete sparse_b_;
}

void ConsoleUi::PrintMenu() const {
    std::printf("\n");
    std::printf("=== Lab 3 matrix calculator ===\n");
    std::printf(" 1. Run tests\n");
    std::printf(" 2. Make dense matrix A\n");
    std::printf(" 3. Make dense matrix B\n");
    std::printf(" 4. Make sparse matrix A\n");
    std::printf(" 5. Make sparse matrix B\n");
    std::printf(" 6. Show matrices\n");
    std::printf(" 7. A := A + B  (dense)\n");
    std::printf(" 8. A := A * scalar  (dense)\n");
    std::printf(" 9. Norm of A  (dense)\n");
    std::printf("10. Swap rows in A  (dense)\n");
    std::printf("11. Swap cols in A  (dense)\n");
    std::printf("12. Multiply row of A  (dense)\n");
    std::printf("13. Multiply col of A  (dense)\n");
    std::printf("14. Row += factor * row  (dense)\n");
    std::printf("15. Col += factor * col  (dense)\n");
    std::printf("16. Trace of A  (square)\n");
    std::printf("17. Make A := identity(n)  (square)\n");
    std::printf("18. Sparse A := A + B\n");
    std::printf("19. Sparse A := A * scalar\n");
    std::printf("20. Sparse norm of A\n");
    std::printf("21. Sparse A * B\n");
    std::printf("22. Check orthogonality of A  (dense)\n");
    std::printf("23. Drop matrix\n");
    std::printf(" 0. Exit\n");
}

void ConsoleUi::Run() {
    while (true) {
        PrintMenu();
        int choice = ReadMenuChoice();
        try {
            switch (choice) {
                case 0:  return;
                case 1:  RunTests(); break;
                case 2:  MakeDenseMatrix(0); break;
                case 3:  MakeDenseMatrix(1); break;
                case 4:  MakeSparseMatrix(); break;
                case 5:  MakeSparseMatrix(); break;
                case 6:  ShowMatrices(); break;
                case 7:  AddMatrices(); break;
                case 8:  MulScalarMenu(); break;
                case 9:  NormMenu(); break;
                case 10: SwapRowsMenu(); break;
                case 11: SwapColsMenu(); break;
                case 12: MulRowMenu(); break;
                case 13: MulColMenu(); break;
                case 14: AddRowMenu(); break;
                case 15: AddColMenu(); break;
                case 16: TraceMenu(); break;
                case 17: IdentityMenu(); break;
                case 18: MultiplySparseMenu(); break;
                case 19: {
                    if (sparse_a_ == nullptr) throw lab2::InvalidArgument("sparse A not set");
                    double s = ReadDouble("scalar: ");
                    sparse_a_->MulScalar(s);
                    PrintSparseMatrix("sparse A", sparse_a_);
                    break;
                }
                case 20: {
                    if (sparse_a_ == nullptr) throw lab2::InvalidArgument("sparse A not set");
                    std::printf("||sparse A|| = %g\n", sparse_a_->Norm());
                    break;
                }
                case 21: {
                    if (sparse_a_ == nullptr || sparse_b_ == nullptr)
                        throw lab2::InvalidArgument("sparse A or B not set");
                    SparseMatrix<double> c = sparse_a_->Multiply(*sparse_b_);
                    PrintSparseMatrix("A*B", &c);
                    break;
                }
                case 22: OrthogonalCheckMenu(); break;
                case 23: DropSlot(); break;
                default: std::printf("unknown choice\n");
            }
        } catch (const std::exception& ex) {
            std::printf("error: %s\n", ex.what());
        }
    }
}

void ConsoleUi::RunTests() { tests::RunAllTests(); }

int ConsoleUi::ReadMenuChoice() const {
    std::string line;
    std::printf("> ");
    if (!std::getline(std::cin, line)) return 0;
    std::stringstream ss(line);
    int value = -1;
    ss >> value;
    return value;
}

int ConsoleUi::ReadInt(const char* prompt) const {
    std::printf("%s", prompt);
    std::string line;
    if (!std::getline(std::cin, line)) throw lab2::InvalidArgument("input ended");
    std::stringstream ss(line);
    int value = 0;
    if (!(ss >> value)) throw lab2::InvalidArgument("not an integer");
    return value;
}

double ConsoleUi::ReadDouble(const char* prompt) const {
    std::printf("%s", prompt);
    std::string line;
    if (!std::getline(std::cin, line)) throw lab2::InvalidArgument("input ended");
    std::stringstream ss(line);
    double value = 0.0;
    if (!(ss >> value)) throw lab2::InvalidArgument("not a number");
    return value;
}

Matrix<double>*& ConsoleUi::SlotRef(int slot) {
    return (slot == 0) ? slot_a_ : slot_b_;
}

void ConsoleUi::ReplaceSlot(int slot, Matrix<double>* value) {
    Matrix<double>*& target = SlotRef(slot);
    if (target != value) { delete target; target = value; }
}

Matrix<double>* ConsoleUi::ReadDenseMatrix() {
    std::printf("kind: 1=rectangular  2=square  4=upper  5=lower  6=diagonal  7=orthogonal\n");
    int kind = ReadInt("kind: ");
    int rows = 0, cols = 0;
    if (kind == kSquare || kind == kUpperTri || kind == kLowerTri ||
        kind == kDiagonal || kind == kOrthogonal) {
        const int n = ReadInt("size: ");
        rows = n; cols = n;
    } else if (kind == kRectangular) {
        rows = ReadInt("rows: ");
        cols = ReadInt("cols: ");
    } else {
        throw lab2::InvalidArgument("unknown dense matrix kind");
    }
    if (rows < 0 || cols < 0) throw lab2::InvalidArgument("size is negative");
    const int total = rows * cols;
    lab2::DynamicArray<double> vals(total > 0 ? total : 1);
    std::printf("enter %d values row by row:\n", total);
    int read = 0;
    while (read < total) {
        std::string line;
        if (!std::getline(std::cin, line)) throw lab2::InvalidArgument("input ended");
        std::stringstream ss(line);
        double v;
        while (read < total && (ss >> v)) { vals.Set(read, v); ++read; }
    }
    const double* ptr = (total > 0) ? &vals.Get(0) : nullptr;
    if (kind == kSquare)       return new SquareMatrix<double>(rows, ptr);
    if (kind == kRectangular)  return new RectangularMatrix<double>(rows, cols, ptr);
    if (kind == kUpperTri)     return new TriangularMatrix<double>(rows, TriKind::Upper, ptr);
    if (kind == kLowerTri)     return new TriangularMatrix<double>(rows, TriKind::Lower, ptr);
    if (kind == kDiagonal)     return new DiagonalMatrix<double>(rows, ptr);
    return new OrthogonalMatrix<double>(rows, ptr);
}

void ConsoleUi::MakeSparseMatrix() {
    int rows = ReadInt("rows: ");
    int cols = ReadInt("cols: ");
    if (rows < 0 || cols < 0) throw lab2::InvalidArgument("size is negative");
    const int total = rows * cols;
    lab2::DynamicArray<double> vals(total > 0 ? total : 1);
    std::printf("enter %d values row by row:\n", total);
    int read = 0;
    while (read < total) {
        std::string line;
        if (!std::getline(std::cin, line)) throw lab2::InvalidArgument("input ended");
        std::stringstream ss(line);
        double v;
        while (read < total && (ss >> v)) { vals.Set(read, v); ++read; }
    }
    const double* ptr = (total > 0) ? &vals.Get(0) : nullptr;
    SparseMatrix<double>* m = new SparseMatrix<double>(
        static_cast<size_t>(rows), static_cast<size_t>(cols), ptr);
    int slot = ReadInt("slot (0=A, 1=B): ");
    if (slot == 0) { delete sparse_a_; sparse_a_ = m; }
    else           { delete sparse_b_; sparse_b_ = m; }
    std::printf("ok\n");
}

void ConsoleUi::MakeDenseMatrix(int slot) {
    Matrix<double>* m = ReadDenseMatrix();
    ReplaceSlot(slot, m);
    std::printf("ok\n");
}

void ConsoleUi::PrintDenseMatrix(const char* label, const Matrix<double>* m) const {
    std::printf("%s = ", label);
    if (m == nullptr) { std::printf("(empty)\n"); return; }
    std::printf("[%dx%d]\n", m->GetRows(), m->GetCols());
    for (int r = 0; r < m->GetRows(); ++r) {
        std::printf("  ");
        for (int c = 0; c < m->GetCols(); ++c) {
            if (c > 0) std::printf(" ");
            std::printf("%g", m->Get(r, c));
        }
        std::printf("\n");
    }
}

void ConsoleUi::PrintSparseMatrix(const char* label, const SparseMatrix<double>* m) const {
    std::printf("%s = ", label);
    if (m == nullptr) { std::printf("(empty)\n"); return; }
    std::printf("[%zux%zu, nnz=%zu]\n", m->GetRows(), m->GetCols(), m->GetNnz());
}

void ConsoleUi::ShowMatrices() const {
    PrintDenseMatrix("A", slot_a_);
    PrintDenseMatrix("B", slot_b_);
    PrintSparseMatrix("sparse A", sparse_a_);
    PrintSparseMatrix("sparse B", sparse_b_);
}

void ConsoleUi::AddMatrices() {
    if (slot_a_ == nullptr || slot_b_ == nullptr)
        throw lab2::InvalidArgument("A or B is not initialized");
    slot_a_->AddMatrix(*slot_b_);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::MulScalarMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    double s = ReadDouble("scalar: ");
    slot_a_->MulScalar(s);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::NormMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    std::printf("||A|| = %g\n", slot_a_->Norm());
}

void ConsoleUi::SwapRowsMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    int i = ReadInt("i: "); int j = ReadInt("j: ");
    slot_a_->SwapRows(i, j);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::SwapColsMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    int i = ReadInt("i: "); int j = ReadInt("j: ");
    slot_a_->SwapCols(i, j);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::MulRowMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    int row = ReadInt("row: "); double k = ReadDouble("factor: ");
    slot_a_->MulRow(row, k);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::MulColMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    int col = ReadInt("col: "); double k = ReadDouble("factor: ");
    slot_a_->MulCol(col, k);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::AddRowMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    int t = ReadInt("target: "); int s = ReadInt("source: "); double f = ReadDouble("factor: ");
    slot_a_->AddRowMultiplied(t, s, f);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::AddColMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    int t = ReadInt("target: "); int s = ReadInt("source: "); double f = ReadDouble("factor: ");
    slot_a_->AddColMultiplied(t, s, f);
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::TraceMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    const SquareMatrix<double>* sq = dynamic_cast<const SquareMatrix<double>*>(slot_a_);
    if (sq == nullptr) throw lab2::InvalidArgument("A is not a square matrix");
    std::printf("trace(A) = %g\n", sq->Trace());
}

void ConsoleUi::IdentityMenu() {
    int n = ReadInt("size: ");
    ReplaceSlot(0, new SquareMatrix<double>(SquareMatrix<double>::Identity(n)));
    PrintDenseMatrix("A", slot_a_);
}

void ConsoleUi::MultiplySparseMenu() {
    if (sparse_a_ == nullptr || sparse_b_ == nullptr)
        throw lab2::InvalidArgument("sparse A or B not set");
    SparseMatrix<double> c = sparse_a_->Multiply(*sparse_b_);
    PrintSparseMatrix("A*B", &c);
}

void ConsoleUi::OrthogonalCheckMenu() {
    if (slot_a_ == nullptr) throw lab2::InvalidArgument("A is not initialized");
    const OrthogonalMatrix<double>* ort = dynamic_cast<const OrthogonalMatrix<double>*>(slot_a_);
    if (ort != nullptr) {
        std::printf("orthogonal: %s\n", ort->IsOrthogonal() ? "yes" : "no");
        return;
    }
    const SquareMatrix<double>* sq = dynamic_cast<const SquareMatrix<double>*>(slot_a_);
    if (sq == nullptr) { std::printf("A is not square\n"); return; }
    const int n = sq->GetSize();
    bool ok = true;
    for (int i = 0; i < n && ok; ++i) {
        for (int j = 0; j < n && ok; ++j) {
            double dot = 0.0;
            for (int k = 0; k < n; ++k)
                dot += static_cast<double>(sq->Get(k, i)) * static_cast<double>(sq->Get(k, j));
            const double expected = (i == j) ? 1.0 : 0.0;
            if (std::fabs(dot - expected) > 1e-9) ok = false;
        }
    }
    std::printf("orthogonal: %s\n", ok ? "yes" : "no");
}

void ConsoleUi::DropSlot() {
    int slot = ReadInt("slot (0=dense A, 1=dense B, 2=sparse A, 3=sparse B): ");
    if (slot == 0) { delete slot_a_; slot_a_ = nullptr; }
    else if (slot == 1) { delete slot_b_; slot_b_ = nullptr; }
    else if (slot == 2) { delete sparse_a_; sparse_a_ = nullptr; }
    else if (slot == 3) { delete sparse_b_; sparse_b_ = nullptr; }
    else throw lab2::InvalidArgument("unknown slot");
    std::printf("dropped\n");
}

}  // namespace lab3
