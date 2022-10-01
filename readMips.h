#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class readMips {

    private:
        //data fields for readMips object; each line within the file gets its own object
        
        //the string of the mips line instruction
        string instruction;

        //the line number of the line object within the file        
        int currLineNumber;
        
        //vector containing the names of the labels
        vector<string> labelName;

        //vector containing the corresponding label line numbers
        vector<int> labelLine;
        
        //label names and label line numbers have matching indices within the two vectors above.

    public:
        //Constructor
        readMips(string line, int fileLine, vector<string> label, vector<int> lineNum);
        
        //Destructor
        ~readMips();
        
        //gets the instruction from object's data field
        string getInstruction();

        //gets the current line number within the file
        int getCurrLineNumber();

        //retrieves line index of label within label vector
        int getLabelIndex(string Labelname);

        //Gets the line number of the label
        int getLabelLine(int index);

        //access the map for the operation code value corresponding to the key string
        int operationCode(string firstMipsInstruction);

        //access the map for the jump code value corresponding to the key string
        int jumpCode(string jump);

        //access the map for the function code value corresponding to the key string
        int functionCode(string firstMipsInstruction);

        //access the map for the register code value corresponding to the key string
        int registerCode(string registerName);

        //contains different cases of instructions to assign it to its corresponding binary value
        int assemble();

        //method for assembling the mips add instruction and returns the decimal rep. of the binary
        int addInstruction(vector<string>);

        //method for assembling the mips addi instruction and returns the decimal rep. of the binary
        int addiInstruction(vector<string>);

        //method for assembling the mips sub instruction and returns the decimal rep. of the binary
        int subInstruction(vector<string>);

        //method for assembling the mips mult instruction and returns the decimal rep. of the binary
        int multInstruction(vector<string>);

        //method for assembling the mips div instruction and returns the decimal rep. of the binary
        int divInstruction(vector<string>);

        //method for assembling the mips mflo instruction and returns the decimal rep. of the binary
        int mfloInstruction(vector<string>);

        //method for assembling the mips mfhi instruction and returns the decimal rep. of the binary
        int mfhiInstruction(vector<string>);

        //method for assembling the mips sll instruction and returns the decimal rep. of the binary
        int sllInstruction(vector<string>);

        //method for assembling the mips srl instruction and returns the decimal rep. of the binary
        int srlInstruction(vector<string>);

        //method for assembling the mips lw instruction and returns the decimal rep. of the binary
        int lwInstruction(vector<string>);

        //method for assembling the mips sw instruction and returns the decimal rep. of the binary
        int swInstruction(vector<string>);

        //method for assembling the mips slt instruction and returns the decimal rep. of the binary
        int sltInstruction(vector<string>);

        //method for assembling the mips beq instruction and returns the decimal rep. of the binary
        int beqInstruction(vector<string>);

        //method for assembling the mips bne instruction and returns the decimal rep. of the binary
        int bneInstruction(vector<string>);

        //method for assembling the mips j instruction and returns the decimal rep. of the binary
        int jInstruction(vector<string>);

        //method for assembling the mips jal instruction and returns the decimal rep. of the binary
        int jalInstruction(vector<string>);

        //method for assembling the mips jr instruction and returns the decimal rep. of the binary
        int jrInstruction(vector<string>);

        //method for assembling the mips jalr instruction and returns the decimal rep. of the binary
        int jalrInstruction(vector<string>);

        //method for assembling the mips syscall instruction and returns the decimal rep. of the binary
        int syscallInstruction(vector<string>); 
};