#include "node.h"


// Constructor taking initial value:
Node::Node(double value)
{
    data = value;
}

// Insert new node as a child:
void Node::insert(Node newNode )
{
    children.push_back(newNode);
}

// retorna a quantidade de nós filhos deste nó
int Node::returnChildren()
{
    return children.size();
}
