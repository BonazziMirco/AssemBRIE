#include <iostream>
#include <fstream>

using namespace std;

int** matrix;
int* inOrder;
int* notInOrder;
int n;

int findInOrderIndex(int value, int n) {
    for(int i = 0; i < n; i++) {
        if(inOrder[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}

int processor_preOrder(int start, int end, int counter = 0) {
    // take root from notinorder, find it in inorder,
    // split both arrays into left and right subtrees,
    // recursively process left and right subtrees

    if(start >= end) {
        return -1;
    }
    
    int val;
    int index;
    int leftChild, rightChild;

    val = notInOrder[counter];
    counter++;
    index = findInOrderIndex(val, n);
    leftChild = processor_preOrder(start, index, counter);
    rightChild = processor_preOrder(index + 1, end, counter);
    matrix[val][0] = (leftChild!= -1) + (rightChild != -1);
    matrix[val][1] = leftChild;
    matrix[val][2] = rightChild;
    

    return val;

}

int processor_postOrder(int start, int end, int counter = 0) {
    // take root from notinorder, find it in inorder,
    // split both arrays into left and right subtrees,
    // recursively process left and right subtrees

    if(start >= end) {
        return -1;
    }
    
    int val;
    int index;
    int leftChild, rightChild;

    val = notInOrder[counter];
    counter++;
    index = findInOrderIndex(val, n);
    leftChild = processor_postOrder(start, index, counter);
    rightChild = processor_postOrder(index + 1, end, counter);
    matrix[val][0] = (leftChild!= -1) + (rightChild != -1);
    matrix[val][1] = leftChild;
    matrix[val][2] = rightChild;

    return val;

}

void processor(bool isPreOrder) {
    int val;
    int index;
    int leftChild, rightChild;
    if(isPreOrder) {
        val = notInOrder[0];
        index = findInOrderIndex(val, n);
        leftChild = processor_preOrder(0, index);
        rightChild = processor_preOrder(index + 1, n);
    } else {
        val = notInOrder[n - 1];
        index = findInOrderIndex(val, n);
        leftChild = processor_postOrder(0, index);
        rightChild = processor_postOrder(index + 1, n);
    }

    matrix[val][0] = (leftChild!= -1) + (rightChild != -1);
    matrix[val][1] = leftChild;
    matrix[val][2] = rightChild;
    return;
}

/*
    Allocates arrays and matrix.
    Reads data from the input file and populates the arrays.
*/
void reader(ifstream& file) {
    file >> n;
    matrix = new int*[n];
    for (int i = 0; i < n; ++i)
    matrix[i] = new int[3];

    inOrder = new int[n];
    notInOrder = new int[n];
    bool isPreOrder = false;

    int order;
    int* array;
    bool repeat = false;

    file >> order;
    do{
        if (order == 0) {
            array = inOrder;
        } else {
            array = notInOrder;
            isPreOrder = (order < 0);
        }
        for (int i = 0; i < n; ++i) {
            file >> array[i];
        }
        repeat = !repeat;
    } while(repeat);
    
    cout << "coocadodle" << endl;

    processor(isPreOrder);
}

void writer(int rows, ofstream& file) {
    for (int i = 0; i < rows; ++i) {
        file << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if(!input.is_open()) {
        cout << "Error opening input file: " << argv[1] << endl;
        return 1;
    }
    
    cout << "cognac" << endl;

    reader(input); // Placeholder call to reader function
    
    cout << "bissolo";

    input.close();
    
    cout << "criptitatachuchu";

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
