#include "BBlock.h"
#include "Node.h"
#include "StringUtils.h"
#include "SymbolTable.h"
#include "TempGen.h"
#include <TempGen.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// Forward declarations for mutual recursion
BBlock* processNode(const Node* node, BBlock* currentBlock);
BBlock* handleIfStatement(const Node* node, BBlock* currentBlock);
BBlock* handleWhileStatement(const Node* node, BBlock* currentBlock);
string handleExpression(const Node* node, BBlock* currentBlock);

/**
 * Determines if a node represents an expression in the AST
 * @param node The AST node to check
 * @return true if the node is any type of expression
 */
bool isExpressionNode(const Node* node) {
    return (node->type == "AddExpression" ||      // Addition operation
            node->type == "SubExpression" ||      // Subtraction operation
            node->type == "MulExpression" ||      // Multiplication operation
            node->type == "DivExpression" ||      // Division operation
            node->type == "NumberExpression" ||   // Literal numbers
            node->type == "IdentifierExpression" ||// Variables
            node->type == "BooleanExpression" ||
            node->type == "Expression"
            );   // Boolean literals
}

/**
 * Determines if a node represents a control flow statement
 * @param node The AST node to check
 * @return true if the node is a control flow statement
 */
bool isControlFlowNode(const Node* node) {
    return (node->type == "IfStatement" || node->type == "WhileStatement");
}

/**
 * Main entry point for IR generation
 * Creates the initial basic block and starts AST traversal
 * @param treeRoot Root node of the AST
 * @return Entry block of the generated IR
 */
BBlock* generateIR(const Node* treeRoot) {
    // Create the entry point basic block
    auto entryBlock = new BBlock("entry");

    // Start processing from the root node
    BBlock* resultBlock = processNode(treeRoot, entryBlock);

    return entryBlock;
}

/**
 * Main recursive function for processing AST nodes
 * Routes each node to its appropriate handler based on type
 * @param node Current AST node being processed
 * @param currentBlock Current basic block being populated
 * @return The next block to be processed
 */
BBlock* processNode(const Node* node, BBlock* currentBlock) {
    if (!node) return currentBlock;  // Handle null nodes gracefully
    cout << "Processing node: " << node->value <<" with type: "<< node->type << '\n';
    if (isExpressionNode(node)) {
        // Expression nodes add instructions to the current block
        handleExpression(node, currentBlock);
        return currentBlock;
    }
    else if (isControlFlowNode(node)) {
        // Control flow nodes create new blocks and modify the CFG
        if (node->type == "IfStatement") {
            return handleIfStatement(node, currentBlock);
        }
        else if (node->type == "WhileStatement") {
            return handleWhileStatement(node, currentBlock);
        }
    }

    // For other node types, process all children sequentially
    for (const Node* child : node->children) {
        currentBlock = processNode(child, currentBlock);
    }

    return currentBlock;
}

/**
 * Processes expression nodes and generates TAC instructions
 * @param node Expression node to process
 * @param currentBlock Block to add the generated instructions
 * @return Name/identifier holding the expression's result
 */
string handleExpression(const Node* node, BBlock* currentBlock) {
    // Handle leaf nodes (literals and identifiers)
    if (node->type == "NumberExpression" ||
        node->type == "IdentifierExpression" ||
        node->type == "BooleanExpression") {
        return node->value;
    }

    // Generate a new temporary variable for this expression
    string tempName = TempGenerator::genVarName();

    // Recursively process left and right operands
    string lhs = handleExpression(node->children.front(), currentBlock);
    string rhs = handleExpression(node->children.back(), currentBlock);

    // Determine the operation type
    string op;
    if (node->type == "AddExpression") op = "+";
    else if (node->type == "SubExpression") op = "-";
    else if (node->type == "MulExpression") op = "*";
    else if (node->type == "DivExpression") op = "/";

    // Create and add the TAC instruction to current block
    const Tac instruction(op, lhs, rhs, tempName);
    currentBlock->tacInstructions.push_back(instruction);

    return tempName;  // Return the name holding the result
}

/**
 * Handles if statements by creating the necessary basic blocks and control flow
 * @param node If statement node
 * @param currentBlock Current block being processed
 * @return Join block where control flow converges
 */
BBlock* handleIfStatement(const Node* node, BBlock* currentBlock) {
    // Create the required blocks for if statement
    BBlock* trueBlock = new BBlock("if_true");    // Block for then branch
    BBlock* falseBlock = new BBlock("if_false");  // Block for else branch
    BBlock* joinBlock = new BBlock("if_join");    // Block where paths converge

    // Process the condition expression
    auto it = node->children.begin();
    string condition = handleExpression(*it, currentBlock);

    // Set up the control flow
    currentBlock->condition = condition;
    currentBlock->trueBlock = trueBlock;     // Branch if condition is true
    currentBlock->falseBlock = falseBlock;   // Branch if condition is false

    // Process the true branch
    ++it;
    if (it != node->children.end()) {
        processNode(*it, trueBlock);
    }
    trueBlock->trueBlock = joinBlock;  // True branch flows to join

    // Process the false branch if it exists
    ++it;
    if (it != node->children.end()) {
        processNode(*it, falseBlock);
    }
    falseBlock->trueBlock = joinBlock;  // False branch flows to join

    return joinBlock;  // Return the convergence point
}

/**
 * Handles while loops by creating the necessary basic blocks and control flow
 * @param node While statement node
 * @param currentBlock Current block being processed
 * @return Exit block for after the loop
 */
BBlock* handleWhileStatement(const Node* node, BBlock* currentBlock) {
    // Create the required blocks for while loop
    BBlock* conditionBlock = new BBlock("while_condition"); // Block for loop condition
    BBlock* bodyBlock = new BBlock("while_body");          // Block for loop body
    BBlock* exitBlock = new BBlock("while_exit");          // Block for after loop

    // Link entry to condition checking
    currentBlock->trueBlock = conditionBlock;

    // Process the loop condition
    auto it = node->children.begin();
    string condition = handleExpression(*it, conditionBlock);

    // Set up the loop control flow
    conditionBlock->condition = condition;
    conditionBlock->trueBlock = bodyBlock;    // If condition true, enter body
    conditionBlock->falseBlock = exitBlock;   // If condition false, exit loop

    // Process the loop body
    ++it;
    if (it != node->children.end()) {
        processNode(*it, bodyBlock);
    }
    bodyBlock->trueBlock = conditionBlock;  // Body flows back to condition

    return exitBlock;  // Return the block for after the loop
}

/**
 * Generates unique temporary variable names
 * @return A new unique temporary variable name
 */
int tempCounter = 0;
string generateTempName() {
    return "t" + to_string(tempCounter++);
}