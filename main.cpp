using namespace std;
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Create and open a text file
    ofstream output("output.txt");
    ifstream input("input.txt");

    if(!output.is_open() || !input.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Write to the file
    output << "Hello, World!\n";
    output << "This is a sample text file.\n";

    // Close the file
    output.close();
    input.close();

    // Open the file again to read from it
    ifstream ReadFile("example.txt");
    string line;

    // Read and display the content of the file line by line
    while (getline(ReadFile, line)) {
        cout << line << endl;
    }

    // Close the file
    ReadFile.close();

    return 42;
}