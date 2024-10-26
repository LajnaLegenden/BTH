#include "SymbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Internal function not exposed in header
static unsigned int string_hash(const char* key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key++;
    }
    return hash_value;
}

Record* create_record(const char* id, const char* type) {
    Record* record = (Record*)malloc(sizeof(Record));
    record->id = strdup(id);
    record->type = strdup(type);
    return record;
}


Scope* create_scope(Scope* parent) {
    auto* scope = (Scope*)malloc(sizeof(Scope));
    scope->parent = parent;
    scope->children = (Scope**)malloc(scope->num_children * sizeof(Scope*));
        scope->num_children = 0;
    scope->capacity_children = 10;
    scope->table = (SymbolTableEntry**)calloc(101, sizeof(SymbolTableEntry*));
    scope->table_size = 101;
    scope->next_child = 0;
    return scope;
}

void put(Scope* scope, const char* key, Record* record) {
    unsigned int index = string_hash(key) % scope->table_size;

    auto* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    entry->key = strdup(key);
    entry->record = record;
    entry->next = scope->table[index];
    scope->table[index] = entry;
}

Record* lookup(Scope* scope, const char* key) {
    while (scope != nullptr) {
        unsigned int index = string_hash(key) % scope->table_size;
        SymbolTableEntry* entry = scope->table[index];

        while (entry != nullptr) {
            if (strcmp(entry->key, key) == 0) {
                return entry->record;
            }
            entry = entry->next;
        }

        scope = scope->parent;
    }
    return NULL;
}


Scope* next_child(Scope* scope) {
    if (scope->next_child >= scope->num_children) {
        if (scope->num_children >= scope->capacity_children) {
            size_t new_capacity = scope->capacity_children * 2;
            auto* new_children = static_cast<Scope*>(malloc(new_capacity * sizeof(Scope)));
            if (new_children == nullptr) {
                // Handle allocation failure
                return nullptr;
            }
            memcpy(new_children, scope->children, scope->num_children * sizeof(Scope));
            free(scope->children);
            scope->children = &new_children;
            scope->capacity_children = new_capacity;
        }
        Scope* new_child = create_scope(scope);
        if (new_child == nullptr) {
            // Handle allocation failure
            return nullptr;
        }
        memcpy(&(scope->children[scope->num_children]), new_child, sizeof(Scope));
        free(new_child);
        scope->num_children++;
    }
    return scope->children[scope->next_child++];
}


void reset_scope(Scope* scope) {
    scope->next_child = 0;
    for (int i = 0; i < scope->num_children; i++) {
        reset_scope((scope->children[i]));
    }
}

void free_scope(Scope* scope) {
    for (int i = 0; i < scope->table_size; i++) {
        SymbolTableEntry* entry = scope->table[i];
        while (entry != NULL) {
            SymbolTableEntry* next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    for (int i = 0; i < scope->num_children; i++) {
        free_scope((scope->children[i]));
    }
    free(scope->children);
    free(scope->table);
    free(scope);
}
