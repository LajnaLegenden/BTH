//
// Created by lajna on 2024-10-26.
//

#ifndef VIZ_H
#define VIZ_H


#include <sstream>
#include <string>
#include <queue>
#include "SymbolTable.h" // Your existing header

class Viz {
private:
    // Helper method to escape strings for DOT
    static string escapeDot(const string& str) {
        string result = str;
        size_t pos = 0;
        while ((pos = result.find("\"", pos)) != string::npos) {
            result.replace(pos, 1, "\\\"");
            pos += 2;
        }
        return result;
    }

    // Generate a unique ID for each node
    static string getNodeId(const Scope* scope) {
        stringstream ss;
        ss << "scope_" << reinterpret_cast<size_t>(scope);
        return ss.str();
    }

    // Generate the symbol table entries for a scope
    static string generateSymbolTableHtml(const vector<SymbolTableEntry>& entries) {
        stringstream ss;
        ss << "<table border='0' cellborder='1' cellspacing='0'>\n";
        ss << "  <tr><td colspan='2'><b>Symbol Table</b></td></tr>\n";
        ss << "  <tr><td><b>ID</b></td><td><b>Type</b></td></tr>\n";

        for (const auto& entry : entries) {
            ss << "  <tr><td>" << escapeDot(entry.id) << "</td>";
            ss << "<td>" << escapeDot(entry.type) << "</td></tr>\n";
        }
        ss << "</table>";
        return ss.str();
    }

public:
    static string generateDot(const Scope* root) {
        if (!root) return "";

        stringstream dot;
        // Start DOT file
        dot << "digraph SymbolTable {\n";
        dot << "  node [shape=none];\n";
        dot << "  edge [color=\"#666666\"];\n";
        dot << "  rankdir=TB;\n\n";

        // Use BFS to traverse the scope tree
        queue<const Scope*> scopeQueue;
        scopeQueue.push(root);

        while (!scopeQueue.empty()) {
            const Scope* currentScope = scopeQueue.front();
            scopeQueue.pop();

            // Add node for current scope
            string nodeId = getNodeId(currentScope);
            dot << "  " << nodeId << " [label=<\n";
            dot << "    <table border='0' cellborder='1' cellspacing='0'>\n";
            dot << "      <tr><td bgcolor=\"#E0E0E0\"><b>Scope: "
                << escapeDot(currentScope->id) << "</b></td></tr>\n";
            dot << "      <tr><td>\n";
            dot << generateSymbolTableHtml(currentScope->table);
            dot << "      </td></tr>\n";
            dot << "    </table>\n";
            dot << "  >];\n\n";

            // Add edges for parent-child relationships
            if (currentScope->parent) {
                dot << "  " << getNodeId(currentScope->parent) << " -> "
                    << nodeId << " [label=\"child\"];\n";
            }

            // Add children to queue
            for (const auto& child : currentScope->children) {
                scopeQueue.push(child);
            }
        }

        // End DOT file
        dot << "}\n";
        return dot.str();
    }

    // Utility method to save to file
    static bool saveToFile(const Scope* root, const string& filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) return false;

        outFile << generateDot(root);
        outFile.close();
        return true;
    }
};



#endif //VIZ_H
