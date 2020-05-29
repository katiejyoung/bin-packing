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
void firstFit(vector<int> vect, int length, int binSize);
void firstFitDecreasing(vector<int> &vect, int length, int binSize);
void bestFit(vector<int> &vect, int length, int binSize);
void mergeSort(vector<int> &vect, int left, int right);
void merge(vector<int> &vect, int left, int right, int middle);

int main() {
    cout << "----- Bin Packing Algorithms -----" << endl;
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
    vector<int> itemsSorted;
    int numTestCases, binCapacity, numItems, itemWeight, i, j;

    ifstream inputFile(dataFile.c_str()); // Open passed file

    // If open successful, read lines
    if (inputFile.is_open()) {
        getline(inputFile, fileLine);
        numTestCases = stringToInt(fileLine);

        // Iterate through each test case to find bin capacity, number of items and item weights
        for (i = 0; i < numTestCases; i++) {
            getline(inputFile, fileLine);
            binCapacity = stringToInt(fileLine);

            getline(inputFile, fileLine);
            numItems = stringToInt(fileLine);
            items.resize(numItems);

            getline(inputFile, fileLine);
            lineToArray(items, fileLine, numItems);

            // Output test case index
            cout << "Test Case " << (i + 1) << " ";

            // Call appropriate functions for bin placement
            firstFit(items, numItems, binCapacity);
            itemsSorted = items; // Save items vector values to itemsSorted for sorting
            firstFitDecreasing(itemsSorted, numItems, binCapacity);
            bestFit(items, numItems, binCapacity);

            cout << endl;

            items.clear(); // Clear vector
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
            vect[vectorItr] = dataValue;
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

// Places items in bins using first-fit principle
void firstFit(vector<int> vect,int length, int binSize) {
    int i, j, doesFit;
    vector<int> binVect;
    int numBins = 1;
    binVect.push_back(binSize); // Apply bin capacity amount to first bin

    // Iterate through items vector
    for (i = 0; i < vect.size(); i++) {
        doesFit = 0; // Reset boolean variable

        // Iterate through bins vector
        for (j = 0; j < binVect.size(); j++) {
            // Add to bin if item weight is smaller than remaining capacity
            if (vect[i] <= binVect[j]) { 
                binVect[j] -= vect[i];
                doesFit = 1; // Update boolean variable
                break;
            }
        }

        // If item did not fit in existing bin, create a new one
        if (doesFit == 0) {
            binVect.push_back(binSize);
            binVect[binVect.size() - 1] -= vect[i]; // Decrease current item from bin capacity
            numBins++; // Increment bin counter
        }
    }

    // Output results
    cout << "First Fit: " << numBins << " ";
}

// Sorts items using merge-sort, then places them in bins using first-fit principle
void firstFitDecreasing(vector<int> &vect, int length, int binSize) {
    int i, j, doesFit;
    vector<int> binVect;
    int numBins = 1;
    binVect.push_back(binSize); // Apply bin capacity amount to first bin

    // Sort items into increasing order
    mergeSort(vect, 0, (length - 1));

    // Create temporary vector to reverse vect into decreasing order
    vector<int> reverse(vect.rbegin(),vect.rend());
    vect.swap(reverse);

    // Iterate through items vector
    for (i = 0; i < vect.size(); i++) {
        doesFit = 0; // Reset boolean variable

        // Iterate through bins vector
        for (j = 0; j < binVect.size(); j++) {
            // Add to bin if item weight is smaller than remaining capacity
            if (vect[i] <= binVect[j]) {
                binVect[j] -= vect[i];
                doesFit = 1; // Update boolean variable
                break;
            }
        }

        // If item did not fit in existing bin, create a new one
        if (doesFit == 0) {
            binVect.push_back(binSize);
            binVect[binVect.size() - 1] -= vect[i]; // Decrease current item from bin capacity
            numBins++; // Increment bin counter
        }
    }

    // Output results
    cout << "First Fit Decreasing: " << numBins << " ";
}

// Places items in bins using best-fit logic
void bestFit(vector<int> &vect,int length, int binSize) {
    int i, j, doesFit, leastRoomVal, leastRoomIdx;
    vector<int> binVect;
    int numBins = 1;
    binVect.push_back(binSize); // Apply bin capacity amount to first bin

    // Iterate through items vector
    for (i = 0; i < vect.size(); i++) {
        doesFit = 0; // Reset boolean variable
        leastRoomVal = 10000; // Reset least-remaining-capacity tracker
        leastRoomIdx = 0; // Reset tracker for least-remaining-capacity index

        // Iterate through bins vector
        for (j = 0; j < binVect.size(); j++) {
            // Compare leastRoomVal to difference between item and current bin capacity
            // If leastRoomVal is larger, update variables
            if ((leastRoomVal > (binVect[j] - vect[i])) && ((binVect[j] - vect[i]) >= 0)) {
                leastRoomVal = binVect[j] - vect[i];
                leastRoomIdx = j;
                doesFit = 1; // Update boolean variable
            }
        }

        // If item did not fit in existing bin, create a new one
        if (doesFit == 0) {
            binVect.push_back(binSize);
            binVect[binVect.size() - 1] -= vect[i]; // Decrease current item from bin capacity
            numBins++; // Increment bin counter
        }
        else { // If item did fit in existing bin, decrease item weight from bin at saved index
            binVect[leastRoomIdx] -= vect[i];
        }
    }

    // Output results
    cout << "Best Fit: " << numBins << " ";
}

// Sorting function that calls itself recursively before merging the left/right sides of array
void mergeSort(vector<int> &vect, int left, int right) {
    if (left < right) {
        int middle = (left + right)/2;

        mergeSort(vect, left, middle); // Sort left-side array
        mergeSort(vect, (middle + 1), right); // Sort right-side array

        merge(vect, left, right, middle); // Merge two sides
    }
}

// Sorting function that merges two array sides
void merge(vector<int> &vect, int left, int right, int middle) {
    vector<int> vectorLeft;
    vector<int> vectorRight;
    int vectorLeftSize = middle - left + 1;
    int vectorRightSize = right - middle;
    int i;
    int j = 0;
    int k = left;

    vectorLeft.resize(vectorLeftSize);
    vectorRight.resize(vectorRightSize);

    // Save appropriate values to vectorLeft and Vector right for sorting
    for (i = 0; i < vectorLeftSize; i++) {
        vectorLeft[i] = vect[left + i];
    }
    for (i = 0; i < vectorRightSize; i++) {
        vectorRight[i] = vect[middle + i + 1];
    }

    // Sort L/R vectors
    i = 0;
    while ((i < vectorLeftSize) && (j < vectorRightSize)) {
        if (vectorLeft[i] <= vectorRight[j]) {
            vect[k] = vectorLeft[i];
            i++;
        }
        else {
            vect[k] = vectorRight[j];
            j++;
        }
        k++;
    }

    // If one end case (above) reached before the other, sort remaining values
    while (i < vectorLeftSize) {
        vect[k] = vectorLeft[i];
        i++;
        k++;
    }
    while (j < vectorRightSize) {
        vect[k] = vectorRight[j];
        j++;
        k++;
    }
}