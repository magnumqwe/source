#include <iostream>
#include <limits>


void free_matrix(int** a, size_t rows) {
    if (a != nullptr) {
        for (size_t i = 0; i < rows; ++i) {
            delete[] a[i];
        }
        delete[] a;
    }
}

int** concat_rows(const int* const* lhs, size_t n1, size_t m1,
                  const int* const* rhs, size_t n2, size_t m2) {
    if (m1 > std::numeric_limits<std::size_t>::max() - m2) {
        return nullptr;
    }

    std::size_t rows = (n1 > n2) ? n1 : n2;
    int** result = new (std::nothrow) int*[rows]();
    if (result == nullptr) {
        return nullptr;
    }

    for (size_t i = 0; i < rows; ++i) {
        size_t len1 = (i < n1) ? m1 : 0;
        size_t len2 = (i < n2) ? m2 : 0;

        result[i] = new (std::nothrow) int[len1 + len2];
        if (result[i] == nullptr) {
            free_matrix(result, rows);
            return nullptr;
        }

        for (std::size_t j = 0; j < len1; ++j) {
            result[i][j] = lhs[i][j];
        }
        for (std::size_t j = 0; j < len2; ++j) {
            result[i][len1 + j] = rhs[i][j];
        }
    }
    return result;
}

bool rest_of_line_empty() {
    int c;
    while ((c = std::cin.get()) != EOF && c != '\n') {
        if (!std::isspace(c)) {
            return false;
        }
    }
    return true;
}

bool read_dims(int& n, int& m) {
    return (std::cin >> n >> m) && n > 0 && m > 0 && rest_of_line_empty();
}

int read_matrix(int**& matrix, size_t n, size_t m) {
    matrix = new (std::nothrow) int*[n]();
    if (matrix == nullptr) {
        return 2;
    }
    for (size_t i = 0; i < n; ++i) {
        matrix[i] = new (std::nothrow) int[m];
        if (matrix[i] == nullptr) {
            free_matrix(matrix, n);
            matrix = nullptr;
            return 2;
        }
        for (size_t j = 0; j < m; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                free_matrix(matrix, n);
                matrix = nullptr;
                return 1;
            }
        }
    }
    if (!rest_of_line_empty()) {
        free_matrix(matrix, n);
        matrix = nullptr;
        return 1;
    }
    return 0;
}

void print_result(const int* const* res, size_t n1, size_t m1,
                size_t n2, size_t m2) {
    size_t rows = (n1 > n2) ? n1 : n2;
    for (size_t i = 0; i < rows; ++i) {
        size_t len = ((i < n1) ? m1 : 0) + ((i < n2) ? m2 : 0);
        for (size_t j = 0; j < len; ++j) {
            std::cout << res[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int n1 = 0, m1 = 0, n2 = 0, m2 = 0;
    int** lhs = nullptr;
    int** rhs = nullptr;
    int** result = nullptr;
    int status = 0;

    std::cout << "колво строк и столбцов первой матрицы: ";
    if (!read_dims(n1, m1)) {
        status = 1;
    } else {
        std::cout << "элементы первой матрицы:\n";
        status = read_matrix(lhs, n1, m1);
    }

    if (status == 0) {
        std::cout << "колво строк и столбцов второй матрицы: ";
        if (!read_dims(n2, m2)) {
            status = 1;
        } else {
            std::cout << "элементы второй матрицы:\n";
            status = read_matrix(rhs, n2, m2);
        }
    }

    if (status == 0) {
        result = concat_rows(lhs, n1, m1, rhs, n2, m2);
        if (result == nullptr) {
            status = 2;
        } else {
            print_result(result, n1, m1, n2, m2);
        }
    }

    if (status == 1) {
        std::cerr << "Ошибка ввода\n";
    } else if (status == 2) {
        std::cerr << "Ошибка выделения памяти\n";
    }

    size_t max_rows = (n1 > n2) ? n1 : n2;
    free_matrix(result, max_rows);
    free_matrix(rhs, n2);
    free_matrix(lhs, n1);

    return status;
}