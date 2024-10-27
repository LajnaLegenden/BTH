#ifndef NODE_H
#define NODE_H

#include <BBlock.h>
#include <TempGen.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;


class Node
{
public:
    int id, lineno;
    string type, value;
    list<Node *> children;
    Node(string t, string v, int l) : id(0), type(t), value(v), lineno(l)
    {
    }
    virtual ~Node() {} // Add virtual destructor
    Node() : id(0), lineno(0)
    {
        type = "uninitialised";
        value = "uninitialised";
    } // Bison needs this.


    void print_tree(int depth = 0)
    {
        for (int i = 0; i < depth; i++)
            cout << "  ";
        cout << type << ":" << value << '\n'; //<< " @line: "<< lineno << endl;
        for (auto i = children.begin(); i != children.end(); i++)
            (*i)->print_tree(depth + 1);
    }

    void generate_tree()
    {
        std::ofstream outStream;
        char *filename = "tree.dot";
        outStream.open(filename);

        int count = 0;
        outStream << "digraph {" << '\n';
        generate_tree_content(count, &outStream);
        outStream << "}" << '\n';
        outStream.close();

        printf("\nBuilt a parse-tree at %s. Use 'make tree' to generate the pdf version.", filename);
    }

    void generate_tree_content(int &count, ofstream *outStream)
    {
        id = count++;
        *outStream << "n" << id << " [label=\"" << type << ":" << value << "\"];" << '\n';

        for (auto i = children.begin(); i != children.end(); i++)
        {
            (*i)->generate_tree_content(count, outStream);
            *outStream << "n" << id << " -> n" << (*i)->id << '\n';
        }
    }
    // Provide a default implementation for genIR
    virtual std::string genIR(BBlock *currentBlock)
    {
        // Default implementation (can be empty)
        return "";
    }
};

;

class SubExpression : public Node
{
public:
    SubExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        auto it = children.begin();
        Node* lhs_node = *it++;
        Node* rhs_node = *it;

        std::string lhs_name = lhs_node->genIR(currentBlock);
        std::string rhs_name = rhs_node->genIR(currentBlock);
        Tac in("-", lhs_name, rhs_name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};

class AddExpression : public Node
{
public:
    AddExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        auto it = children.begin();
        Node* lhs_node = *it++;
        Node* rhs_node = *it;

        std::string lhs_name = lhs_node->genIR(currentBlock);
        std::string rhs_name = rhs_node->genIR(currentBlock);
        Tac in("+", lhs_name, rhs_name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};

class MulExpression : public Node
{
public:
    MulExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        auto it = children.begin();
        Node* lhs_node = *it++;
        Node* rhs_node = *it;

        std::string lhs_name = lhs_node->genIR(currentBlock);
        std::string rhs_name = rhs_node->genIR(currentBlock);
        Tac in("*", lhs_name, rhs_name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};

class DivExpression : public Node
{
public:
    DivExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        auto it = children.begin();
        Node* lhs_node = *it++;
        Node* rhs_node = *it;

        std::string lhs_name = lhs_node->genIR(currentBlock);
        std::string rhs_name = rhs_node->genIR(currentBlock);
        Tac in("/", lhs_name, rhs_name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};

class IdetifierExpression : public Node
{
public:
    IdetifierExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        Tac in(name, name, name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};

class NumberExpression : public Node
{
public:
    NumberExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        Tac in(value, name, name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};

class BooleanExpression : public Node
{
public:
    BooleanExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        Tac in(value, name, name, name);
        currentBlock->tacInstructions.push_back(in);

        return name;
    }
};
class IdentifierExpression : public Node
{
public:
    IdentifierExpression(const std::string &_t, const std::string &_v, const int _l) : Node(_t, _v, _l)
    {
    }
    std::string genIR(BBlock *currentBlock) override
    {
        std::string name = TempGenerator::genVarName(); // Generate a unique name
        Tac in(name, name, name, name);
        currentBlock->tacInstructions.push_back(in);
        return name;
    }
};


class IfStatement : public Node {
public:
    IfStatement(const std::string& _t, const std::string& _v, const int _l)
        : Node(_t, _v, _l) {}

    std::string genIR(BBlock* currentBlock) override {
        BBlock* trueBlock = new BBlock("if_true_" + TempGenerator::genLabel());
        BBlock* falseBlock = new BBlock("if_false_" + TempGenerator::genLabel());
        BBlock* joinBlock = new BBlock("if_join_" + TempGenerator::genLabel());

        // Get condition from first child
        auto it = children.begin();
        std::string condition = (*it)->genIR(currentBlock);

        // Link blocks
        currentBlock->condition = condition;
        currentBlock->trueBlock = trueBlock;
        currentBlock->falseBlock = falseBlock;

        // Process true branch
        ++it;
        if (it != children.end()) {
            (*it)->genIR(trueBlock);
        }
        trueBlock->trueBlock = joinBlock;

        // Process false branch if it exists (for if-else)
        ++it;
        if (it != children.end()) {
            (*it)->genIR(falseBlock);
        }
        falseBlock->trueBlock = joinBlock;

        return joinBlock->name;
    }
};

class WhileStatement : public Node {
public:
    WhileStatement(const std::string& _t, const std::string& _v, const int _l)
        : Node(_t, _v, _l) {}

    std::string genIR(BBlock* currentBlock) override {
        BBlock* condBlock = new BBlock("while_cond_" + TempGenerator::genLabel());
        BBlock* bodyBlock = new BBlock("while_body_" + TempGenerator::genLabel());
        BBlock* exitBlock = new BBlock("while_exit_" + TempGenerator::genLabel());

        currentBlock->trueBlock = condBlock;

        // Process condition
        auto it = children.begin();
        std::string condition = (*it)->genIR(condBlock);
        condBlock->condition = condition;
        condBlock->trueBlock = bodyBlock;
        condBlock->falseBlock = exitBlock;

        // Process body
        ++it;
        if (it != children.end()) {
            (*it)->genIR(bodyBlock);
        }
        bodyBlock->trueBlock = condBlock;  // Loop back

        return exitBlock->name;
    }
};

class AssignmentStatement : public Node {
public:
    AssignmentStatement(const std::string& _t, const std::string& _v, const int _l)
        : Node(_t, _v, _l) {}

    std::string genIR(BBlock* currentBlock) override {
        auto it = children.begin();
        std::string lhs = (*it)->genIR(currentBlock);  // Identifier
        ++it;
        std::string rhs = (*it)->genIR(currentBlock);  // Expression

        Tac in("=", rhs, "", lhs);
        currentBlock->tacInstructions.push_back(in);
        return lhs;
    }
};

class PrintStatement : public Node {
public:
    PrintStatement(const std::string& _t, const std::string& _v, const int _l)
        : Node(_t, _v, _l) {}

    std::string genIR(BBlock* currentBlock) override {
        auto it = children.begin();
        std::string expr = (*it)->genIR(currentBlock);

        Tac in("print", expr, "", "");
        currentBlock->tacInstructions.push_back(in);
        return "";
    }
};

class MethodCallExpression : public Node {
public:
    MethodCallExpression(const std::string& _t, const std::string& _v, const int _l)
        : Node(_t, _v, _l) {}

    std::string genIR(BBlock* currentBlock) override {
        std::string result = TempGenerator::genVarName();

        // Handle method call parameters
        for (auto it = children.begin(); it != children.end(); ++it) {
            std::string param = (*it)->genIR(currentBlock);
            Tac paramInstr("param", param, "", "");
            currentBlock->tacInstructions.push_back(paramInstr);
        }

        // Create call instruction
        Tac callInstr("call", value, std::to_string(children.size()), result);
        currentBlock->tacInstructions.push_back(callInstr);

        return result;
    }
};

class BlockStatement : public Node {
public:
    BlockStatement(const std::string& _t, const std::string& _v, const int _l)
        : Node(_t, _v, _l) {}

    std::string genIR(BBlock* currentBlock) override {
        // Process each statement in the block sequentially
        for (auto stmt : children) {
            stmt->genIR(currentBlock);
        }
        return "";
    }
};

#endif