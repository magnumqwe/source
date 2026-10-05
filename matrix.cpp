#include <iostream>

using namespace std;

int main() {
    try {
        unsigned int rows, cols;
        if (!(cin >> rows >> cols) || rows == 0 || cols == 0)
            throw runtime_error("bad input");

        int** m = new int*[rows];
        for (int i = 0; i < rows; i++) {
            m[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                if (!(cin >> m[i][j])) throw runtime_error("bad input");
        }

        int** t = new int*[cols];
        for (int i = 0; i < cols; i++) {
            t[i] = new int[rows];
            for (int j = 0; j < rows; j++)
                t[i][j] = m[j][i];
        }

        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++)
                cout << t[i][j] << (j + 1 < rows ? " " : "\n");
        }

        for (int i = 0; i < rows; i++){
            delete[] m[i]; 
        }
        delete[] m;
        for (int i = 0; i < cols; i++) {
            delete[] t[i];
        }
        delete[] t;

        return 0;
    } catch (const bad_alloc&) {
        return 2;
    } catch (...) {
        return 1;
    }
}