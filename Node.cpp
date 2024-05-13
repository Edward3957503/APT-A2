#include "Node.h"

// Constructor definition
Node::Node() : data(nullptr), next(nullptr) {}

Node::~Node(){
    delete data; // Make sure to delete the allocated Stock object to avoid memory leaks
};