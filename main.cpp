#include "readMips.h"

int main(int argc, char* argv[]) {
    if (argc != 3) { 
        cerr << "Usage: " << argv[0] << " [input text filename] [output text filename] " << endl;
        exit(1);
    }

    // Open the file to check for labels and directives
    ifstream findLabels(argv[1]);

    if (!findLabels) {
        cerr << "Error: could not open input file: " << argv[1] << endl;
        exit(1);
    }

    string line;
    // Store these labels in labelNames vector, and the corresponding line number in labelNum
    vector<string> labelNames;
    vector<int> labelNum;
    int l = 0;
    while (isspace(line[l])) {
        int pos = line.find(line[l]);
        line = line.substr(pos + 1);
    }
    int i = 1; // keep track of number of lines
    int j = 0; // keep track of number of directives
    while (getline(findLabels, line)) {
        stringstream ss(line);
        if (line.empty() || (line.find_first_not_of(' ') == std::string::npos)) {
            continue;
        }
        while (ss.good()) {
            string substr;
            getline(ss, substr, ' ');
            if (substr.find('#') != std::string::npos) {
                if (substr.front() == '#') {
                    i--;
                    j++;
                }
                break;
            }
            if (substr.find(',') != std::string::npos) {
                substr.pop_back();
            }
            if (substr.find(':') != std::string::npos) {
                substr.pop_back();
                labelNames.push_back(substr);
                labelNum.push_back(i);
                i--; // dont want to count labels as lines
            }
            if (substr.find('.') != std::string::npos) {
                i--; // dont want to count directives as lines
                j++; // increase directives count
                break;
            }
        }
        i++; // increase line number
    }
    findLabels.close();

    // Open file again to create instructions for each line now
    ifstream infile(argv[1]);

    if (!infile) {
        cerr << "Error: could not open input file: " << argv[1] << endl;
        exit(1);
    }

    // have lineNum start with 1 - the number of directives
    int lineNum = 1 - j;
    vector<int> asmValues;
    while (getline(infile, line)) {
        // grab one line from the file and initialize an object 
        readMips object(line, lineNum, labelNames, labelNum);
        // call assemble method to translate into binary
        int value = object.assemble();

        // if the value returned does not equal 0, push it into a vector that will contains each 
        // decimal value of the instruction
        if (value != 0) {
            asmValues.push_back(value); 
        }
        
        lineNum++; // increase line count for next object
    }

    infile.close();

    ofstream outfile(argv[2], ios::binary);

    // Display an error message if the output file can't be opened
    if (!outfile) {
        cerr << "Unable to open output file: " << argv[2] << endl;
        exit(1);
    }

    // Push the values of the instructions into the file
    for (size_t i = 0; i < asmValues.size(); i++) {
        int inst = asmValues[i];
        outfile.write((char *) &inst, sizeof(int)); //Write to file as true binary
        // string binaryInstruction = bitset<32>(instructionValue).to_string();
        // outfile << binaryInstruction << endl;
    }
    
    outfile.close();
};