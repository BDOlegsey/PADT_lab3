## LAB 3

RUN
```
mkdir build 2>nul || true && g++ -std=c++17 -Wall -Wextra -Iinclude -Isrc -Itests src/main.cpp src/console_ui.cpp tests/test_runner.cpp tests/test_framework.cpp tests/test_matrix.cpp tests/test_square_matrix.cpp tests/test_rectangular_matrix.cpp tests/test_sparse_matrix.cpp tests/test_triangular_matrix.cpp tests/test_diagonal_matrix.cpp tests/test_orthogonal_matrix.cpp include/bit_sequence.cpp -o build/lab3
./build/lab3
```

TESTS
```
mkdir build 2>nul || true && g++ -std=c++17 -Wall -Wextra -Iinclude -Isrc -Itests tests/test_main.cpp tests/test_runner.cpp tests/test_framework.cpp tests/test_matrix.cpp tests/test_square_matrix.cpp tests/test_rectangular_matrix.cpp tests/test_sparse_matrix.cpp tests/test_triangular_matrix.cpp tests/test_diagonal_matrix.cpp tests/test_orthogonal_matrix.cpp include/bit_sequence.cpp -o build/lab3_tests
./build/lab3_tests
```
