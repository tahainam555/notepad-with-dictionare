#include<iostream>
#include<fstream>
using namespace std;

class Node{
    public:
        string data;
        Node* left;
        Node* right;
        int height;

        Node(string data){
            this->data = data;
            left = NULL;
            right = NULL;
            height = 0;
        }

};

class AVL{
    public:
        Node* root;
        AVL(){
            root = NULL;
        }
        void insert(string data){
            root = insert(root, data);
        }
        Node* insert(Node* root, string data){
            if(root == NULL){
                return new Node(data);
            }
            if(data < root->data){
                root->left = insert(root->left, data);
            }
            else if(data > root->data){
                root->right = insert(root->right, data);
            }
            root->height = max(height(root->left), height(root->right))+1;
            return check(root);
        }

        Node* search(string data){
            return search(root, data);
        }

        Node* search(Node* root, string data){
            if(root == NULL){
                return NULL;
            }
            if(root->data == data){
                return root;
            }
            else if(data > root->data){
                return search(root->right, data);
            }
            else{
                return search(root->left, data);
            }
        }

        Node* RotateRight(Node* k1){
            Node* k2 = k1->left;
            k1->left = k2->right;
            k2->right = k1;
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            return k2;
        }

        Node* RotatLeft(Node* k1){
            Node* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            return k2;
        }

        Node* RotateLeftRight(Node* k1){
            k1->left = RotatLeft(k1->left);
            return RotateRight(k1);
        }

        Node* RotateRightLeft(Node* k1){
            k1->right = RotateRight(k1->right);
            return RotatLeft(k1);
        }

        int height(Node* root){
            if(root == NULL){
                return -1;
            }
            return root->height;
        }

        Node* check(Node* root){
            if(root == NULL){
                return NULL;
            }
            if(height(root->left) - height(root->right) > 1){
                if(height(root->left->left) >= height(root->left->right)){
                    root = RotateRight(root);
                }
                else{
                    root = RotateLeftRight(root);
                }
            }
            else if(height(root->right) - height(root->left) > 1){
                if(height(root->right->right) >= height(root->right->left)){
                    root = RotatLeft(root);
                }
                else{
                    root = RotateRightLeft(root);
                }
            }
            return root;
        }

        void preOrder(){
            preOrder(root);
        }

        void preOrder(Node* root){
            if(root == NULL){
                return;
            }
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }

        void deleteTree(){
            deleteTree(root);
        }

        void deleteTree(Node* root){
            if(root == NULL){
                return;
            }
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }

};


int main(){
    AVL tree;
    fstream file;
    file.open("dictionary.txt");
    string word;
    while(file >> word){
        tree.insert(word);
    }
    file.close();
    cout << "TREE CONSTRUCTED SUCCESSFULLY" << endl;

    cout << "PreOrder Traversal of AVL Tree: " << endl;
    tree.preOrder();
}