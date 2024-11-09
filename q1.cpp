#include<iostream>
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
        }

        Node* search(string data){
            
        }


};


int main(){
}