// avrahamavitan@gmail.com
#include <iostream>
#include "SquareMat.hpp"
using namespace std;
using namespace mat; // use our matrix namespace

// show menu options to the user
void printMenu() {
    cout << "\nChoose an operation:" << endl;
    cout << "1. Add (m1 + m2)" << endl;
    cout << "2. Subtract (m1 - m2)" << endl;
    cout << "3. Multiply (m1 * m2)" << endl;
    cout << "4. Scalar Multiply (m1 * scalar)" << endl;
    cout << "5. Element-wise Multiply (m1 % m2)" << endl;
    cout << "6. Modulo with Scalar (m1 % scalar)" << endl;
    cout << "7. Divide by Scalar (m1 / scalar)" << endl;
    cout << "8. Power (m1 ^ exponent)" << endl;
    cout << "9. Transpose (~m1)" << endl;
    cout << "10. Determinant (!m1)" << endl;
    cout << "11. Equality (m1 == m2)" << endl;
    cout << "12. Inequality (m1 != m2)" << endl;
    cout << "13. Compare (m1 > m2)" << endl;
    cout << "14. Increment (++m1)" << endl;
    cout << "15. Access Element m1[i][j]" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    int size;
    cout << "Enter matrix size: ";
    cin >> size; // read dimension from user

    SquareMat m1(size), m2(size); // create two matrices of given size

    cout << "Enter values for matrix m1:" << endl;
    cin >> m1; // read matrix values
    cout << "Enter values for matrix m2:" << endl;
    cin >> m2; // read second matrix

    int choice;
    do {
        printMenu(); // show operations
        cout << "Enter choice: ";
        cin >> choice; // get user's choice

        try {
            switch (choice) {
                case 1: cout << (m1 + m2); break; // addition
                case 2: cout << (m1 - m2); break; // subtraction
                case 3: cout << (m1 * m2); break; // multiply matrices
                case 4: {
                    double s;
                    cout << "Enter scalar: ";
                    cin >> s;
                    cout << (m1 * s); // scalar multiply
                    break;
                }
                case 5: cout << (m1 % m2); break; // element-wise multiply
                case 6: {
                    int s;
                    cout << "Enter integer scalar: ";
                    cin >> s;
                    cout << (m1 % s); // modulo each element
                    break;
                }
                case 7: {
                    double s;
                    cout << "Enter scalar: ";
                    cin >> s;
                    cout << (m1 / s); // divide each element
                    break;
                }
                case 8: {
                    int exp;
                    cout << "Enter exponent: ";
                    cin >> exp;
                    cout << (m1 ^ exp); // matrix power
                    break;
                }
                case 9: cout << (~m1); break; // transpose
                case 10: cout << "Determinant: " << !m1 << endl; break; // determinant
                case 11: cout << (m1 == m2 ? "Equal\n" : "Not equal\n"); break; // equality
                case 12: cout << (m1 != m2 ? "Not equal\n" : "Equal\n"); break; // inequality
                case 13: cout << (m1 > m2 ? "m1 > m2\n" : "m1 <= m2\n"); break; // compare sums
                case 14: ++m1; cout << m1; break; // increment then print
                case 15: {
                    int i, j;
                    cout << "Enter i and j: ";
                    cin >> i >> j;
                    cout << "Element: " << m1[i][j] << endl; // access element
                    break;
                }
                case 0: cout << "Goodbye!\n"; break; // exit
                default: cout << "Invalid choice.\n"; break; // handle wrong input
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl; // show any errors
        }
    } while (choice != 0); // repeat until exit chosen

    return 0; // end program
}
