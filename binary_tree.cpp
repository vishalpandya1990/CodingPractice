#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstdio>

using namespace std;

class BinaryTree {
  private:
    struct TreeNode{
        int key;
        TreeNode *left, *right;
        TreeNode(int key){
           this->key = key;
           left = right = NULL;
        };
    };
    const int UNDEFINED = INT_MIN;
    TreeNode *root;
    size_t treeSize;
    size_t treeHeight;
    bool exceptionLogEnabled;
    bool debugLogEnabled;
    void printExceptionLog(string exceptionMessage);
    void printDebugLog(string debugMessage);
  public:
    BinaryTree();
    int insertKey(int key);
    void doLevelOrderTraversal(void);
    void doDepthFirstTraversal(void);
    void doBreadthFirstTraversal(void);
    size_t getTreeHeight(void);
    size_t getTreeSize(void);
    void printTreeStats(void);
/*
    int deleteKey(int key);
    bool isEqualTo(BinaryTree &otherBinTree);
    int getMaxElement(void);
    int getMinElement(void);
    size_t getTreeDiameter(void);
    int printElementStore(void);
    void doInOrderTraversal(void);
    void doPreOrderTraversal(void);
    void doPostOrderTraversal(void);
*/
    void changeDebugLogPermission(bool enable);
    void changeExceptionLogPermission(bool enable);
};

BinaryTree::BinaryTree(void){
    treeHeight = treeSize = 0;
    root = NULL;
    debugLogEnabled = false;
    exceptionLogEnabled = true;
}
size_t BinaryTree::getTreeHeight(void) {
    return treeHeight;
}

size_t BinaryTree::getTreeSize(void) {
    return treeSize;
}

int BinaryTree::insertKey(int key) {
    TreeNode *newNode = new TreeNode(key);
    if(!newNode) {
           printExceptionLog("Memory allocation failed");
           return 1;
    }
    char insertMesssage[256] = {0};
    if(!root){
        root = newNode;
        treeSize++;
        snprintf(insertMesssage, 255, "Inserted node with key %d as root", key);
        printDebugLog(insertMesssage);
        return 0;
    }
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode *frontNode = q.front();
        q.pop();
        if(NULL == frontNode->left) {
            frontNode->left = newNode;
            treeSize++;
            if(NULL == frontNode->right) treeHeight++;
            snprintf(insertMesssage, 255, "Inserted node with key %d as left child of node with key %d", key, frontNode->key);
            printDebugLog(insertMesssage);
            return 0;
        } else if (NULL == frontNode->right) {
           frontNode->right = newNode;
           treeSize++;
           snprintf(insertMesssage, 255, "Inserted node with key %d as right child of node with key %d", key, frontNode->key);
           printDebugLog(insertMesssage);
           return 0;
        } else {
           q.push(frontNode->left);
           q.push(frontNode->right);
        }
    }
    return 1; //1 for error, 0 for success
}

void BinaryTree::doLevelOrderTraversal(void) {
   cout << "Level Order Traversal: ";
   if(NULL == root) { // equivalent to "treeSize == 0" check
      printExceptionLog("Tree is empty");
      return;
   }
   queue<TreeNode*> q;
   q.push(root);
   while(!q.empty()) {
      TreeNode *frontNode = q.front();
      q.pop();
      cout << frontNode->key << " ";
      if(frontNode->left) {
         q.push(frontNode->left);
      }
      if(frontNode->right) {
        q.push(frontNode->right);
      }
   }
   cout << endl;
}

void BinaryTree::doDepthFirstTraversal(void) {
   cout << "Depth First Traversal: ";
   if(NULL == root) { // equivalent to "treeSize == 0" check
      printExceptionLog("Tree is empty");
      return;
   }
   stack<TreeNode*> q;
   q.push(root);
   while(!q.empty()) {
      TreeNode *frontNode = q.top();
      q.pop();
      cout << frontNode->key << " ";
      if(frontNode->right) {
        q.push(frontNode->right);
      }
      if(frontNode->left) {
         q.push(frontNode->left);
      }
   }
   cout << endl;
}

void BinaryTree::doBreadthFirstTraversal(void) {
    doLevelOrderTraversal();
}

void BinaryTree::printExceptionLog(string exceptionMessage) {
   if(exceptionLogEnabled){
     cout << exceptionMessage << endl;
   }
}

void BinaryTree::printDebugLog(string debugMessage) {
   if(debugLogEnabled){
     cout << debugMessage << endl;
   }
}

void BinaryTree::changeDebugLogPermission(bool enable) {
   debugLogEnabled = enable;
}

void BinaryTree::changeExceptionLogPermission(bool enable) {
   exceptionLogEnabled = enable;
}
void BinaryTree::printTreeStats(void) {
    cout << "Tree Parameters: Height = " << treeHeight  << ", Size = " << treeSize << endl;
}

int main() {
 BinaryTree t;
 t.changeDebugLogPermission(true);
 t.doLevelOrderTraversal();
 t.insertKey(2);
 t.insertKey(1);
 t.insertKey(3);
 t.insertKey(4);
 t.doLevelOrderTraversal();
 t.doDepthFirstTraversal();
 t.printTreeStats();
 return 0;
}
