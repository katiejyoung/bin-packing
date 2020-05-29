// Katie Young
// CS 325, Homework Assignment #8

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

int readLines(string dataFile);
int stringToInt(string dataString);
void lineToArray(vector<int> &vect, string dataString, int length);
void firstFit(vector<int> vect,int length, int binSize);
void firstFitDecreasing(vector<int> &vect,int length, int binSize);
void bestFit(vector<int> &vect,int length, int binSize);

int main() {
    cout << "----- First-Fit Algorithm -----" << endl;
    int success = readLines("bin.txt"); // Initiate program

    // Output message according to program success
    if (success != 1) {
        cout << "Error: Failed to open file." << endl;
    }

    return 0;
}

// Reads file line by line and initiates sorting
// Returns 1 if sorting successful
// Returns 0 if file error
int readLines(string dataFile) {
    string fileLine;
    vector<int> items;
    int numTestCases, binCapacity, numItems, itemWeight, i, j;

    ifstream inputFile(dataFile.c_str()); // Open passed file

    // If open successful, read lines
    if (inputFile.is_open()) {
        getline(inputFile, fileLine);
        numTestCases = stringToInt(fileLine);

        // Iterate through each wrestler and initialize instance
        for (i = 0; i < numTestCases; i++) {
            getline(inputFile, fileLine);
            binCapacity = stringToInt(fileLine);

            getline(inputFile, fileLine);
            numItems = stringToInt(fileLine);
            items.resize(numItems);

            getline(inputFile, fileLine);
            lineToArray(items, fileLine, numItems);

            for (int j = 0; j < numItems; j++) {
                cout << items[j] << " ";
            }
            cout << endl;

            cout << "Test Case " << (i + 1) << " ";

            firstFit(items, numItems, binCapacity);
            // firstFitDecreasing(items, numItems, binCapacity);
            // bestFit(items, numItems, binCapacity);
            cout << endl;

            items.clear();
        }

        inputFile.close(); // Close ifstream
        return 1; // Return 1 if successful
    }

    else {
        return 0; // Return 0 if unsuccessful
    }
    
}

// Converts string to integer
// Returns new integer
int stringToInt(string dataString) {
    int newInt = atoi(dataString.c_str());
    return newInt;
}

// Converts a passed string to a vector by separating integers from spaces
void lineToArray(vector<int> &vect, string dataString, int length) {
    int dataItr = 0;
    int vectorItr = 0;
    int dataValue = 0;
    string dataItem;

    // Iterate through string
    while ((dataItr <= dataString.length()) && (vectorItr < length)) {
        // When separator identified, convert value to integer and append to vector
        if ((dataItr == dataString.length()) || (dataString[dataItr] == ' ') && (dataString[dataItr + 1] != ' ')) {
            dataValue = atoi(dataItem.c_str()); // Convert value to integer

            // Add value to data array and increment vector iterator
            // vect.at(vectorItr) = dataValue;
            vect[vectorItr] = dataValue;
            // vect.push_back(dataValue);
            vectorItr++;
            
            dataValue = 0;
            dataItem = "";
        }
        else {
            dataItem += dataString[dataItr]; // Append character to string until separator reached
        }

        dataItr++;
    }
}

void firstFit(vector<int> vect,int length, int binSize) {
    int i, j, doesFit;
    vector<int> binVect;
    int numBins = 1;
    binVect.push_back(binSize);

    for (i = 0; i < vect.size(); i++) {
        doesFit = 0;
        for (j = 0; j < binVect.size(); j++) {
            if (vect[i] <= binVect[j]) {
                binVect[j] -= vect[i];
                doesFit = 1;
                break;
            }
        }

        if (doesFit == 0) {
            binVect.push_back(binSize);
            binVect[binVect.size() - 1] -= vect[i];
            numBins++;
        }
    }

    cout << "First Fit: " << numBins << " ";
}

void firstFitDecreasing(vector<int> &vect,int length, int binSize) {
    int numBins = 1;
    cout << "First Fit Decreasing: " << numBins << " ";
}

void bestFit(vector<int> &vect,int length, int binSize) {
    int numBins = 1;
    cout << "Best Fit: " << numBins << " ";
}