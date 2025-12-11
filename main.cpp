using namespace std;
#include <iostream>
#include <fstream>

int** matrix;

/*
    Allocates arrays and matrix.
    Reads data from the input file and populates the arrays.
*/
void reader(ifstream& file) {
    int rows;
    file >> rows;
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
    matrix[i] = new int[3];

    int* inorder = new int[rows];
    int* notinorder = new int[rows];
    int whichorder;

    int order;
    int* array;
    bool repeat = false;

    file >> order;
    do{
        if (order == 0) {
            array = inorder;
        } else {
            array = notinorder;
            whichorder = order;
        }
        for (int i = 0; i <= rows; ++i) {
            for (int j = 0; j < 3; ++j) {
                file >> array[i];
            }
        }
        repeat = !repeat;
    } while(repeat);
}

void processor() {
    // take root from notinorder, find it in inorder,
    // split both arrays into left and right subtrees,
    // recursively process left and right subtrees
}

void writer(int rows, ofstream& file) {
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

    reader(input); // Placeholder call to reader function

    input.close();

    /*
     section switch
    */

    ofstream output("output.txt");

    if(!output.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    writer(0, output); // Placeholder call to writer function

    output.close();

    return 42;
}
