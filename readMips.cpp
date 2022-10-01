#include "readMips.h"

// Constructor for object
readMips::readMips(string mipsLine, int mipsLineNumb, vector<string> vectorLabelName, vector<int> vectorLineNum) {
    instruction = mipsLine;
    currLineNumber = mipsLineNumb;
    labelName = vectorLabelName;
    labelLine = vectorLineNum;
}

// Destructor just in case
readMips::~readMips() {}

// Get the instruction line from object
string readMips::getInstruction() {
    return instruction;
}

// Get instructions current line number
int readMips::getCurrLineNumber() {
    return currLineNumber;
}

// get the index of a label in the file
int readMips::getLabelIndex(string label) {
    int index;
    
    for (int i = 0; i < labelName.size(); i++) {
        if (labelName[i] == label) {
            index = i;
        }
    }
    return index;
}

// get the value of the line that the label was found
int readMips::getLabelLine(int index) {
    int lineNum = labelLine[index];
    return lineNum;
}

// Contains if statements for each instructions; calls the method of each instruction
// Deals with the whitespace and comments as well
int readMips::assemble() {
    int binaryInstruction;
    string line = getInstruction();
    vector<string> mipsInstrLine;
    
    int l = 0;
    while (isspace(line[l])) {
        int pos = line.find(line[l]);
        line = line.substr(pos + 1);
    }

    stringstream ss(line);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ' ');
        if (substr.find('#') != std::string::npos) {
            return 0;
        }
        if (substr.find(':') != std::string::npos) {
            return 0;
        }
        if (substr.find('.') != std::string::npos) {
            return 0;
        }
        if (substr.find(',') != std::string::npos) {
            substr.pop_back();
        }
    mipsInstrLine.push_back(substr);
    }

    if (mipsInstrLine[0] == "addi") {
        int binaryInstruction = readMips::addiInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "add") {
        int binaryInstruction = readMips::addInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "sub") {
        int binaryInstruction = readMips::subInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "mult") {
        int binaryInstruction = readMips::multInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "div") {
        int binaryInstruction = readMips::divInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "mflo") {
        int binaryInstruction = readMips::mfloInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "mfhi") {
        int binaryInstruction = readMips::mfhiInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "sll") {
        int binaryInstruction = readMips::sllInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "srl") {
        int binaryInstruction = readMips::srlInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "lw") {
        int binaryInstruction = readMips::lwInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "sw") {
        int binaryInstruction = readMips::swInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "slt") {
        int binaryInstruction = readMips::sltInstruction(mipsInstrLine);
        return binaryInstruction;
    }
    
    if (mipsInstrLine[0] == "beq") {
        int binaryInstruction = readMips::beqInstruction(mipsInstrLine);
        return binaryInstruction;
    }
   
    if (mipsInstrLine[0] == "bne") {
        int binaryInstruction = readMips::bneInstruction(mipsInstrLine);
        return binaryInstruction;
    }
    
    if (mipsInstrLine[0] == "j") {
        int binaryInstruction = readMips::jInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "jal") {
        int binaryInstruction = readMips::jalInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "jr") {
        int binaryInstruction = readMips::jrInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "jalr") {
        int binaryInstruction = readMips::jalrInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    if (mipsInstrLine[0] == "syscall") {
        int binaryInstruction = readMips::syscallInstruction(mipsInstrLine);
        return binaryInstruction;
    }

    else {
        return 0;
    }
    return -1;
}

// addi
int readMips::addiInstruction(vector<string> mipsLine) {
    int value;
    int opcode = readMips::operationCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[2]);
    int rt = readMips::registerCode(mipsLine[1]);
    int immediate = atoi(mipsLine[3].c_str());

    if (immediate < 0) {
        rt++;
    }

    opcode = opcode << 26;
    rs = rs << 21;
    rt = rt << 16;
    
    value = opcode + rs + rt + immediate;
    return value;
}

// add
int readMips::addInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[2]);
    int rt = readMips::registerCode(mipsLine[3]);
    int rd = readMips::registerCode(mipsLine[1]);
    rs = rs << 21;
    rt = rt << 16;
    rd = rd << 11;

    value = opcode + rs + rt + rd + shift + funcCode;
    return value;
}

// sub
int readMips::subInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[2]);
    int rt = readMips::registerCode(mipsLine[3]);
    int rd = readMips::registerCode(mipsLine[1]);
    rs = rs << 21;
    rt = rt << 16;
    rd = rd << 11;

    value = opcode + rs + rt + rd + shift + funcCode;
    return value;
}

// mult
int readMips::multInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[1]);
    int rt = readMips::registerCode(mipsLine[2]);
    opcode = opcode << 26;
    shift = shift << 6;
    rs = rs << 21;
    rt = rt << 16;

    value = opcode + rs + rt + shift + funcCode;
    return value;
}

// div
int readMips::divInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[1]);
    int rt = readMips::registerCode(mipsLine[2]);
    shift = shift << 6;
    rs = rs << 21;
    rt = rt << 16;

    value = opcode + rs + rt + shift + funcCode;
    return value;
}

// mflo
int readMips::mfloInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int lo = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[1]);
    rs = rs << 11;
    
    value = opcode + lo + rs+ shift + funcCode;
    return value;
}

// mfhi
int readMips::mfhiInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int lo = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[1]);
    rs = rs << 11;
    
    value = opcode + lo + rs+ shift + funcCode;
    return value;
}

// sll
int readMips::sllInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int extra = 0;
    int rd = readMips::registerCode(mipsLine[1]);
    int rt = readMips::registerCode(mipsLine[2]);
    int funcCode = readMips::functionCode(mipsLine[0]);
    stringstream x(mipsLine[3]);
    int shift;
    x >> shift;
    shift = shift << 6;
    rd = rd << 11;
    rt = rt << 16;
    
    value = opcode + rt + rd + shift + funcCode;
    return value;
}

// srl
int readMips::srlInstruction(vector<string> mipsLine) {
    int value;
    int opcode = 0;
    int extra = 0;
    int rd = readMips::registerCode(mipsLine[1]);
    int rt = readMips::registerCode(mipsLine[2]);
    int funcCode = readMips::functionCode(mipsLine[0]);
    stringstream x(mipsLine[3]);
    int shift;
    x >> shift;
    shift = shift << 6;
    rd = rd << 11;
    rt = rt << 16;
    
    value = opcode + rt + rd + shift + funcCode;
    return value;
}

// lw
int readMips::lwInstruction(vector<string> mipsLine) {
    int value;
    string targetReg = mipsLine[2];
    int pos = targetReg.find("(");
    string outer = targetReg.substr(0, pos);
    int offset = atoi(outer.c_str());

    string base;
    pos = targetReg.find("(");
    base = targetReg.substr(pos + 1);
    base.pop_back();

    int opcode = readMips::operationCode(mipsLine[0]);
    int baseReg = readMips::registerCode(base);
    int rt = readMips::registerCode(mipsLine[1]);
    
    opcode = opcode << 26;
    baseReg = baseReg << 21;
    rt = rt << 16;

    value = opcode + baseReg + rt + offset;
    return value;
}


// sw
int readMips::swInstruction(vector<string> mipsLine) {
    int value;
    string targetReg = mipsLine[2];
    int pos = targetReg.find("(");
    string outer = targetReg.substr(0, pos);
    int offset = atoi(outer.c_str());

    string base;
    pos = targetReg.find("(");
    base = targetReg.substr(pos + 1);
    base.pop_back();

    int opcode = readMips::operationCode(mipsLine[0]);
    int baseReg = readMips::registerCode(base);
    int rt = readMips::registerCode(mipsLine[1]);
    opcode = opcode << 26;
    baseReg = baseReg << 21;
    rt = rt << 16;

    value = opcode + baseReg + rt + offset;
    return value;
}

// slt
int readMips::sltInstruction(vector<string> mipsLine) {
    int value;
    int shift = 0;
    int opcode = 0;
    int rd = readMips::registerCode(mipsLine[1]);
    int rs = readMips::registerCode(mipsLine[2]);
    int rt = readMips::registerCode(mipsLine[3]);
    int funcCode = readMips::functionCode(mipsLine[0]);
    rs = rs << 21;
    rt = rt << 16;
    rd = rd << 11;

    value = opcode + rs + rt + rd + shift + funcCode;
    return value;
}

// beq
int readMips::beqInstruction(vector<string> mipsLine) {
    int value;
    int opCode = readMips::operationCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[1]);
    int rt = readMips::registerCode(mipsLine[2]);

    int currLine = readMips::getCurrLineNumber();
    int labelIndex = readMips::getLabelIndex(mipsLine[3]);
    int lineNum = readMips::getLabelLine(labelIndex) + labelIndex;
    int offset = lineNum - currLine;

    if (lineNum < currLine) {
        rt++;
        opCode = opCode << 26;
        rs = rs << 21;
        rt = rt << 16;
        value = opCode + rs + rt + offset;
        return value;
    }

    opCode = opCode << 26;
    rs = rs << 21;
    rt = rt << 16;

    value = opCode + rs + rt + offset - 1;
    return value;
}

// bne
int readMips::bneInstruction(vector<string> mipsLine) {
    int value;
    int opCode = readMips::operationCode(mipsLine[0]);
    int rs = readMips::registerCode(mipsLine[1]);
    int rt = readMips::registerCode(mipsLine[2]);

    int currLine = readMips::getCurrLineNumber();
    int labelIndex = readMips::getLabelIndex(mipsLine[3]);
    int lineNum = readMips::getLabelLine(labelIndex) + labelIndex;
    int offset = lineNum - currLine;

    if (lineNum < currLine) {
        rt++;
        opCode = opCode << 26;
        rs = rs << 21;
        rt = rt << 16;
        value = opCode + rs + rt + offset;
        return value;
    }

    opCode = opCode << 26;
    rs = rs << 21;
    rt = rt << 16;

    value = opCode + rs + rt + offset - 1;
    return value;
}

// j
int readMips::jInstruction(vector<string> mipsLine) {
    int value;
    string name = mipsLine[1];
    int index = readMips::getLabelIndex(name);
    int lineNum = readMips::getLabelLine(index);

    int jcode = readMips::jumpCode(mipsLine[0]);

    jcode = jcode << 26;

    value = jcode + lineNum - 1;
    return value;
}

// jal
int readMips::jalInstruction(vector<string> mipsLine) {
    int value;
    string name = mipsLine[1];
    int index = readMips::getLabelIndex(name);
    int lineNum = readMips::getLabelLine(index);
    int jcode = readMips::jumpCode(mipsLine[0]);

    jcode = jcode << 26;

    value = jcode + lineNum - 1;
    return value;
}

// jr
int readMips::jrInstruction(vector<string> mipsLine) {
    int value;
    int opCode = 0;
    int shift = 0;
    int rs = readMips::registerCode(mipsLine[1]);
    int funcCode = readMips::functionCode(mipsLine[0]);

    rs = rs << 21;
    
    value = opCode + rs + shift + funcCode;
    return value;
}

// jalr
int readMips::jalrInstruction(vector<string> mipsLine) {
    int value;
    int opCode = 0;
    int shift = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    int rd = readMips::registerCode(mipsLine[1]);
    int rs = readMips::registerCode(mipsLine[2]);

    rd = rd << 11;
    rs = rs << 21;

    value = opCode + rs + shift + rd + shift + funcCode;
    return value;
}

// syscall
int readMips::syscallInstruction(vector<string> mipsLine) {
    int value;
    int opCode = 0;
    int code = 0;
    int funcCode = readMips::functionCode(mipsLine[0]);
    value = opCode + code + funcCode;
    return value;
}

// map containing operationCodes
int readMips::operationCode(string operation) {
    int opCode;
    unordered_map<string, int> operationCode;
    operationCode["addi"] = 8;
    operationCode["lw"] = 35;
    operationCode["sw"] = 43;
    operationCode["beq"] = 4;
    operationCode["bne"] = 5;
    opCode = operationCode[operation];
    return opCode;
}
int readMips::jumpCode(string jump) {
    int jCode;
    unordered_map<string, int> jumpCode;
    jumpCode["j"] = 2;
    jumpCode["jal"] = 3;
    jCode = jumpCode[jump];
    return jCode;
}

// map containing functionCodes
int readMips::functionCode(string function) {
    int funcCode;
    unordered_map<string, int> functionCode;
    functionCode["add"] = 32;
    functionCode["sub"] = 34;
    functionCode["mult"] = 24;
    functionCode["div"] = 26;
    functionCode["mflo"] = 18;
    functionCode["mfhi"] = 16;
    functionCode["sll"] = 0;
    functionCode["srl"] = 2;
    functionCode["slt"] = 42;
    functionCode["jr"] = 8;
    functionCode["jalr"] = 9;
    functionCode["syscall"] = 12;
    funcCode = functionCode[function];
    return funcCode;
}

// map containing registerCodes
int readMips::registerCode(string regist) {
    int regCode;
    unordered_map<string, int> registerCode;
    registerCode["zero"] = 0;
    registerCode["$0"] = 0;
    registerCode["$at"] = 1;
    registerCode["$1"] = 1;
    registerCode["$v0"] = 2;
    registerCode["$2"] = 2;
    registerCode["$v1"] = 3;
    registerCode["$3"] = 3;
    registerCode["$a0"] = 4;
    registerCode["$4"] = 4;
    registerCode["$a1"] = 5;
    registerCode["$5"] = 5;
    registerCode["$a2"] = 6;
    registerCode["$6"] = 6;
    registerCode["$a3"] = 7;
    registerCode["$7"] = 7;
    registerCode["$t0"] = 8;
    registerCode["$8"] = 8;
    registerCode["$t1"] = 9;
    registerCode["$9"] = 9;
    registerCode["$t2"] = 10;
    registerCode["$10"] = 10;
    registerCode["$t3"] = 11;
    registerCode["$11"] = 11;
    registerCode["$t4"] = 12;
    registerCode["$12"] = 12;
    registerCode["$t5"] = 13;
    registerCode["$13"] = 13;
    registerCode["$t6"] = 14;
    registerCode["$14"] = 14;
    registerCode["$t7"] = 15;
    registerCode["$15"] = 15;
    registerCode["$s0"] = 16;
    registerCode["$16"] = 16;
    registerCode["$s1"] = 17;
    registerCode["$17"] = 17;
    registerCode["$s2"] = 18;
    registerCode["$18"] = 18;
    registerCode["$s3"] = 19;
    registerCode["$19"] = 19;
    registerCode["$s4"] = 20;
    registerCode["$20"] = 20;
    registerCode["$s5"] = 21;
    registerCode["$21"] = 21;
    registerCode["$s6"] = 22;
    registerCode["$22"] = 22;
    registerCode["$s7"] = 23;
    registerCode["$23"] = 23;
    registerCode["$t8"] = 24;
    registerCode["$24"] = 24;
    registerCode["$t9"] = 25;
    registerCode["$25"] = 25;
    registerCode["$k0"] = 26;
    registerCode["$26"] = 26;
    registerCode["$k1"] = 27;
    registerCode["$27"] = 27;
    registerCode["$gp"] = 28;
    registerCode["$28"] = 28;
    registerCode["$sp"] = 29;
    registerCode["$29"] = 29;
    registerCode["$fp"] = 30;
    registerCode["$30"] = 30;
    registerCode["$ra"] = 31;
    registerCode["$31"] = 31;
    regCode = registerCode[regist];
    return regCode;
}