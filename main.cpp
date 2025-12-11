using namespace std;
#include <iostream>
#include <fstream>

void reader(int** matrix, int rows, ifstream& file) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            file >> matrix[i][j];
        }
    }

}

void writer(int** matrix, int rows, ofstream& file) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream input("input.txt");

    if(!input.is_open()) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    reader(nullptr, 0, input); // Placeholder call to reader function

    input.close();

    /*
     section switch
    */

    ofstream output("output.txt");

    if(!output.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    writer(nullptr, 0, output); // Placeholder call to writer function

    output.close();

    return 42;
}