#ifndef NODE_H
#define NODE_H
#include "imap.h"
#include <vector>
using std::vector;

class Node
{

public:
    // Constructor taking initial value:
    Node(double value = 0);

    vector<Node> children;
    double data; //Node value
    State atualState; // atual state

    // Insert node in front:
    void insert(Node newNode );
    int returnChildren();
};

#endif // NODE_H
