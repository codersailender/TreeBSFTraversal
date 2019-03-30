//
//  main.cpp
//  TreeBSFTraversal
//
//  Created by Sailender Singh on 28/03/19.


#include <iostream>
using namespace std;

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    Node() {
        key = 0;
        left = NULL;
        right = NULL;
    }
};

struct Node* root = NULL;

class Queue {
    struct QNode {
        struct Node* data;
        struct QNode* next;
        struct QNode* end;
        QNode() {
            data = NULL;
            next = NULL;
            end = NULL;
        }
    };
    
    struct QNode* root = NULL;
    int Qlen = 0;
    
    QNode* getNode(Node* data) {
        struct QNode* qnode = new QNode();
        qnode->data  = data;
        return qnode;
    }
    
public:
    void push(Node *node) {
        QNode* qnode = getNode(node);
        if (root==NULL) {
            root = qnode;
        } else {
            root->end->next = qnode;
        }
        root->end = qnode;
        Qlen++;
    }
    
    Node* pop() {
        if (isEmpty()) {
            return NULL;
        }
        
        QNode* temp = root;
        root = temp->next;
        if (Qlen>1) {
            root->end = temp->end;
        }
        Qlen--;
        return temp->data;
    }
    
    bool isEmpty() {
        return (root==NULL || Qlen==0);
    }
    
    int getLength() {
        return Qlen;
    }
    
};

void deleteTree(Node* node) {
    if (node==NULL) {
        return;
    }
    
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void inOrder(Node* node) {
    if (node==NULL) {
        return;
    }
    
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

//by default inserting in BST
Node* getNode(int key) {
    struct Node* node = new Node();
    node->key = key;
    return node;
}

Node* insertNode(int key, Node* node) {
    
    if (node==NULL) {
        node = getNode(key);
    } else {
        if (node->key > key) {
            node->left = insertNode(key, node->left);
        } else {
            node->right = insertNode(key, node->right);
        }
    }
    
    return node;
}

void doBFSTraversal(Node *root) {
    Queue *q = new Queue();
    q->push(root);
    
    while (!q->isEmpty()) {
        Node* n = q->pop();
        cout << n->key << " ";
        
        if (n->left != NULL) {
            q->push(n->left);
        }
        
        if (n->right != NULL) {
            q->push(n->right);
        }
    }
}

int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        
        int leftHt = getHeight(node->left);
        int rightHt = getHeight(node->right);
        
        int maxHt = leftHt > rightHt ? leftHt : rightHt;
        return (maxHt + 1);
    }
}

bool isBST(Node* node) {
    if (node == NULL) {
        return true;
    }
    if (node -> left != NULL && node -> left ->key > node -> key) {
        return false;
    }
    
    if (node -> right != NULL && node -> right -> key < node -> key ) {
        return false;
    }
    
    if (!isBST(node -> left) || !isBST(node -> right)) {
        return false;
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
   //34 55 2 45 67 983 12 556 7 5
    cout << "Enter no of elements";
    int N;
    cin >> N;
    for (int i=0; i<N; i++) {
        int key;
        cin >> key;
        root = insertNode(key, root);
    }
    
    cout << endl << endl;
    inOrder(root);
    
    cout << endl<<"BFS traversal "<< endl;
    doBFSTraversal(root);
    
    cout << endl <<"Tree height: "<< getHeight(root) << endl;
    
    cout << " Is BST: " << isBST(root) << endl;
    return 0;
}
