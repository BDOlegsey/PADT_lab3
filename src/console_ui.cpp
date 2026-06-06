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

ConsoleUi::ConsoleUi() : slot_a_(nullptr), slot_b_(nullptr) {}

ConsoleUi::~ConsoleUi() {
    delete slot_a_;
    delete slot_b_;
}

void ConsoleUi::PrintMenu() const {
    std::printf("\n");
    std::printf("=== Lab 3 matrix calculator ===\n");
    std::printf(" 1. Run tests\n");
    std::printf(" 2. Make matrix A\n");
    std::printf(" 3. Make matrix B\n");
    std::printf(" 4. Show matrices\n");
    std::printf(" 5. A := A + B\n");
    std::printf(" 6. A := A * scalar\n");
    std::printf(" 7. Norm of A\n");
    std::printf(" 8. Swap rows in A\n");
    std::printf(" 9. Swap cols in A\n");
    std::printf("10. Multiply row of A\n");
    std::printf("11. Multiply col of A\n");
    std::printf("12. Row += factor * other row in A\n");
    std::printf("13. Col += factor * other col in A\n");
    std::printf("14. Trace of A (square only)\n");
    std::printf("15. Make A := identity(n)\n");
    std::printf("16. Multiply sparse A * B\n");
    std::printf("17. Check orthogonality of A\n");
    std::printf("18. Drop matrix\n");
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
                case 2:  MakeMatrix(0); break;
                case 3:  MakeMatrix(1); break;
                case 4:  ShowMatrices(); break;
                case 5:  AddMatrices(); break;
                case 6:  MulScalarMenu(); break;
                case 7:  NormMenu(); break;
                case 8:  SwapRowsMenu(); break;
                case 9:  SwapColsMenu(); break;
                case 10: MulRowMenu(); break;
                case 11: MulColMenu(); break;
                case 12: AddRowMenu(); break;
                case 13: AddColMenu(); break;
                case 14: TraceMenu(); break;
                case 15: IdentityMenu(); break;
                case 16: MultiplySparseMenu(); break;
                case 17: OrthogonalCheckMenu(); break;
                case 18: DropSlot(); break;
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
    if (!std::getline(std::cin, line)) {
        return 0;
    }
    std::stringstream ss(line);
    int value = -1;
    ss >> value;
    return value;
}

int ConsoleUi::ReadInt(const char* prompt) const {
    std::printf("%s", prompt);
    std::string line;
    if (!std::getline(std::cin, line)) {
        throw lab2::InvalidArgument("input ended");
    }
    std::stringstream ss(line);
    int value = 0;
    if (!(ss >> value)) {
        throw lab2::InvalidArgument("not an integer");
    }
    return value;
}

double ConsoleUi::ReadDouble(const char* prompt) const {
    std::printf("%s", prompt);
    std::string line;
    if (!std::getline(std::cin, line)) {
        throw lab2::InvalidArgument("input ended");
    }
    std::stringstream ss(line);
    double value = 0.0;
    if (!(ss >> value)) {
        throw lab2::InvalidArgument("not a number");
    }
    return value;
}

Matrix<double>*& ConsoleUi::SlotRef(int slot) {
    return (slot == 0) ? slot_a_ : slot_b_;
}

void ConsoleUi::ReplaceSlot(int slot, Matrix<double>* value) {
    Matrix<double>*& target = SlotRef(slot);
    if (target != value) {
        delete target;
        target = value;
    }
}

Matrix<double>* ConsoleUi::ReadMatrix() {
    std::printf("kind: 1=rectangular  2=square  3=sparse  4=upper  5=lower  6=diagonal  7=orthogonal\n");
    int kind = ReadInt("kind: ");
    int rows = 0, cols = 0;
    if (kind == kSquare || kind == kUpperTri || kind == kLowerTri ||
        kind == kDiagonal || kind == kOrthogonal) {
        const int n = ReadInt("size: ");
        rows = n;
        cols = n;
    } else if (kind == kRectangular || kind == kSparse) {
        rows = ReadInt("rows: ");
        cols = ReadInt("cols: ");
    } else {
        throw lab2::InvalidArgument("unknown matrix kind");
    }
    if (rows < 0 || cols < 0) {
        throw lab2::InvalidArgument("size is negative");
    }
    const int total = rows * cols;
    lab2::DynamicArray<double> vals(total > 0 ? total : 1);
    std::printf("enter %d values, row by row, whitespace-separated:\n", total);
    int read = 0;
    while (read < total) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw lab2::InvalidArgument("input ended before all values were read");
        }
        std::stringstream ss(line);
        double v;
        while (read < total && (ss >> v)) {
            vals.Set(read, v);
            ++read;
        }
        if (!ss.eof() && ss.fail() && read < total) {
            throw lab2::InvalidArgument("bad number in input");
        }
    }
    const double* ptr = (total > 0) ? &vals.Get(0) : nullptr;
    if (kind == kSquare) {
        return new SquareMatrix<double>(rows, ptr);
    }
    if (kind == kRectangular) {
        return new RectangularMatrix<double>(rows, cols, ptr);
    }
    if (kind == kSparse) {
        return new SparseMatrix<double>(rows, cols, ptr);
    }
    if (kind == kUpperTri) {
        return new TriangularMatrix<double>(rows, TriKind::Upper, ptr);
    }
    if (kind == kLowerTri) {
        return new TriangularMatrix<double>(rows, TriKind::Lower, ptr);
    }
    if (kind == kDiagonal) {
        return new DiagonalMatrix<double>(rows, ptr);
    }
    return new OrthogonalMatrix<double>(rows, ptr);
}

void ConsoleUi::MakeMatrix(int slot) {
    Matrix<double>* m = ReadMatrix();
    ReplaceSlot(slot, m);
    std::printf("ok\n");
}

void ConsoleUi::PrintMatrix(const char* label, const Matrix<double>* m) const {
    std::printf("%s = ", label);
    if (m == nullptr) {
        std::printf("(empty)\n");
        return;
    }
    std::printf("[%dx%d]\n", m->GetRows(), m->GetCols());
    for (int r = 0; r < m->GetRows(); ++r) {
        std::printf("  ");
        for (int c = 0; c < m->GetCols(); ++c) {
            if (c > 0) {
                std::printf(" ");
            }
            std::printf("%g", m->Get(r, c));
        }
        std::printf("\n");
    }
}

void ConsoleUi::ShowMatrices() const {
    PrintMatrix("A", slot_a_);
    PrintMatrix("B", slot_b_);
}

void ConsoleUi::AddMatrices() {
    if (slot_a_ == nullptr || slot_b_ == nullptr) {
        throw lab2::InvalidArgument("A or B is not initialized");
    }
    slot_a_->AddMatrix(*slot_b_);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::MulScalarMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    double s = ReadDouble("scalar: ");
    slot_a_->MulScalar(s);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::NormMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    std::printf("||A|| = %g\n", slot_a_->Norm());
}

void ConsoleUi::SwapRowsMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    int i = ReadInt("i: ");
    int j = ReadInt("j: ");
    slot_a_->SwapRows(i, j);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::SwapColsMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    int i = ReadInt("i: ");
    int j = ReadInt("j: ");
    slot_a_->SwapCols(i, j);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::MulRowMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    int row = ReadInt("row: ");
    double k = ReadDouble("factor: ");
    slot_a_->MulRow(row, k);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::MulColMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    int col = ReadInt("col: ");
    double k = ReadDouble("factor: ");
    slot_a_->MulCol(col, k);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::AddRowMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    int target = ReadInt("target row: ");
    int source = ReadInt("source row: ");
    double k = ReadDouble("factor: ");
    slot_a_->AddRowMultiplied(target, source, k);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::AddColMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    int target = ReadInt("target col: ");
    int source = ReadInt("source col: ");
    double k = ReadDouble("factor: ");
    slot_a_->AddColMultiplied(target, source, k);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::TraceMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    SquareMatrix<double>* sq = dynamic_cast<SquareMatrix<double>*>(slot_a_);
    if (sq == nullptr) {
        throw lab2::InvalidArgument("A is not a square matrix");
    }
    std::printf("trace(A) = %g\n", sq->Trace());
}

void ConsoleUi::IdentityMenu() {
    int n = ReadInt("size: ");
    SquareMatrix<double>* id = new SquareMatrix<double>(n);
    for (int i = 0; i < n; ++i) {
        id->Set(i, i, 1.0);
    }
    ReplaceSlot(0, id);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::MultiplySparseMenu() {
    if (slot_a_ == nullptr || slot_b_ == nullptr) {
        throw lab2::InvalidArgument("A or B is not initialized");
    }
    SparseMatrix<double>* a = dynamic_cast<SparseMatrix<double>*>(slot_a_);
    SparseMatrix<double>* b = dynamic_cast<SparseMatrix<double>*>(slot_b_);
    if (a == nullptr || b == nullptr) {
        throw lab2::InvalidArgument("both A and B must be sparse");
    }
    SparseMatrix<double>* result = new SparseMatrix<double>(a->Multiply(*b));
    ReplaceSlot(0, result);
    PrintMatrix("A", slot_a_);
}

void ConsoleUi::OrthogonalCheckMenu() {
    if (slot_a_ == nullptr) {
        throw lab2::InvalidArgument("A is not initialized");
    }
    OrthogonalMatrix<double>* q = dynamic_cast<OrthogonalMatrix<double>*>(slot_a_);
    if (q == nullptr) {
        throw lab2::InvalidArgument("A is not an orthogonal matrix");
    }
    std::printf("orthogonal: %s\n", q->IsOrthogonal() ? "yes" : "no");
}

void ConsoleUi::DropSlot() {
    int which = ReadInt("which (1=A, 2=B): ");
    if (which == 1) {
        ReplaceSlot(0, nullptr);
    } else if (which == 2) {
        ReplaceSlot(1, nullptr);
    } else {
        throw lab2::InvalidArgument("unknown slot");
    }
    std::printf("ok\n");
}

}  // namespace lab3
