//
// Created by lajna on 2024-10-27.
//

#ifndef TEMPGEN_H
#define TEMPGEN_H


class TempGenerator {
private:
    inline static int varCounter = 0;      // Inline variable
    inline static int labelCounter = 0;    // Inline variable
    inline static int arrayCounter = 0;    // Inline variable

public:
    static std::string genVarName() {
        return "t" + std::to_string(varCounter++);
    }

    static std::string genLabel() {
        return "L" + std::to_string(labelCounter++);
    }

    static std::string genArrayName() {
        return "arr" + std::to_string(arrayCounter++);
    }

    static void reset() {
        varCounter = 0;
        labelCounter = 0;
        arrayCounter = 0;
    }
};



#endif //TEMPGEN_H
