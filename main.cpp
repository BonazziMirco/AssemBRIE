#include <iostream>
#include <fstream>

using namespace std;

int** matrix;
int* inOrder;
int* otherOrder;  // Can be pre-order or post-order
int n;
int preIndex = 0;      // For pre-order traversal
int postIndex = 0;     // For post-order traversal

int findInOrderIndex(int value) {
    for(int i = 0; i < n; i++) {
        if(inOrder[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive function to build tree from PRE-order and in-order
int buildTreeFromPreOrder(int inStart, int inEnd) {
    if (inStart > inEnd || preIndex >= n) {
        return -1;
    }
    
    // Current root from pre-order (first element is root)
    int rootVal = otherOrder[preIndex++];
    int inIndex = findInOrderIndex(rootVal);
    
    // Recursively build left and right subtrees
    int leftChild = buildTreeFromPreOrder(inStart, inIndex - 1);
    int rightChild = buildTreeFromPreOrder(inIndex + 1, inEnd);
    
    // Store children information in matrix
    matrix[rootVal][0] = (leftChild != -1) + (rightChild != -1);
    matrix[rootVal][1] = leftChild;
    matrix[rootVal][2] = rightChild;
    
    return rootVal;
}

// Recursive function to build tree from POST-order and in-order
int buildTreeFromPostOrder(int inStart, int inEnd) {
    if (inStart > inEnd || postIndex < 0) {
        return -1;
    }
    
    // Current root from post-order (last element is root, process in reverse)
    int rootVal = otherOrder[postIndex--];
    int inIndex = findInOrderIndex(rootVal);
    
    // In post-order: right subtree comes before left subtree when reading backwards
    int rightChild = buildTreeFromPostOrder(inIndex + 1, inEnd);
    int leftChild = buildTreeFromPostOrder(inStart, inIndex - 1);
    
    // Store children information in matrix
    matrix[rootVal][0] = (leftChild != -1) + (rightChild != -1);
    matrix[rootVal][1] = leftChild;
    matrix[rootVal][2] = rightChild;
    
    return rootVal;
}

void reader(ifstream& file) {
    file >> n;
    
    // Allocate matrix
    matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[3];
        // Initialize with -1 (no child)
        matrix[i][0] = 0;
        matrix[i][1] = -1;
        matrix[i][2] = -1;
    }
    
    inOrder = new int[n];
    otherOrder = new int[n];
    
    int order;
    bool repeat = false;
    bool isPreOrder = false;
    
    do {
        file >> order;
        
        if (order == 0) {
            // In-order traversal
            for (int i = 0; i < n; ++i) {
                file >> inOrder[i];
            }
        } else if (order == 1) {
            // Post-order traversal
            isPreOrder = false;
            for (int i = 0; i < n; ++i) {
                file >> otherOrder[i];
            }
        } else if (order == -1) {
            // Pre-order traversal
            isPreOrder = true;
            for (int i = 0; i < n; ++i) {
                file >> otherOrder[i];
            }
        }
        repeat = !repeat;
    } while(repeat);
    
    // Process based on order type
    if (isPreOrder) {
        // Pre-order case: start from beginning
        preIndex = 0;
        int root = buildTreeFromPreOrder(0, n - 1);
    } else {
        // Post-order case: start from end
        postIndex = n - 1;
        int root = buildTreeFromPostOrder(0, n - 1);
    }
}

void writer(int rows, ofstream& file) {
    for (int i = 0; i < rows; ++i) {
        file << i << " " << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << endl;
    }
}

//deallocate arrays and matrix
void cleanup() {
    if(matrix) {
        for(int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    delete[] inOrder;
    delete[] otherOrder;
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
    
    reader(input);
    input.close();
    
    ofstream output("output.txt");
    if(!output.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    writer(n, output);
    output.close();

    cleanup();

    return 0;
}
