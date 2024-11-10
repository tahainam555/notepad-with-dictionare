#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
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

class listNode{
    public:
        char ch;
        listNode* next;
        listNode(char ch){
            this->ch = ch;
            next = NULL;
        }
};

class queueNode{
    public:
        char data;
        queueNode* next;
        queueNode(char data){
            this->data = data;
            next = NULL;
        }
};

class Queue{
    public:
        queueNode* head;
        queueNode* tail;
        Queue(){
            head = NULL;
            tail = NULL;
        }

        void enqueue(char data){
            if(head == NULL){
                head = new queueNode(data);
                tail = head;
            }
            else{
                tail->next = new queueNode(data);
                tail = tail->next;
            }
        }

        char dequeue(){
            if(head == NULL){
                return '\0';
            }
            queueNode* temp = head;
            head = head->next;
            char data = temp->data;
            delete temp;
            return data;
        }

        bool isEmpty(){
            return head == NULL;
        }

        void display(){
            queueNode* temp = head;
            while(temp != NULL){
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        void deleteQueue(){
            queueNode* temp = head;
            while(temp != NULL){
                queueNode* temp1 = temp;
                temp = temp->next;
                delete temp1;
            }
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

class List{
    public:
        listNode* head;
        listNode* tail;
        List(){
            head = NULL;
        }

        void insert(char ch){
            if(head == NULL){
                head = new listNode(ch);
                tail = head;
            }
            else{
                tail->next = new listNode(ch);
                tail = tail->next;
            }
        }

        void display(){
            listNode* temp = head;
            while(temp != NULL){
                cout << temp->ch ;
                temp = temp->next;
            }
            cout << endl;
        }

        void deleteList(){
            listNode* temp = head;
            while(temp != NULL){
                listNode* temp1 = temp;
                temp = temp->next;
                delete temp1;
            }
        }

};


int main(){
    AVL tree;
    fstream file;
    file.open("dictionary.txt");
    string word;
    while(file >> word){
//        if(word[0]<=90 && word[0]>=65){
//            word[0] = word[0] + 32;
//        }
        tree.insert(word);
    }
    file.close();
    cout << "TREE CONSTRUCTED SUCCESSFULLY" << endl;

/*
    file.open("dictionary.txt");
    while(file >> word){
        for(int i = 0; i < word.length(); i++){
            list.insert(word[i]);
        }
        list.insert(' ');
    }
    file.close();
    cout << "LIST CONSTRUCTED SUCCESSFULLY" << endl;
*/    
    List list;
    char ch;
    string str = "";
    while(1){
        ch = getch();
        if(ch == 27){
            break;
        }
        else if(ch == 32){
            Node* temp = tree.search(str);
            if(temp != NULL){
                cout << "FOUND" << endl;
            }
            else{
                cout << "NOT FOUND" << endl;
            }
            str = "";
        }
        else if(ch == 19){
            //SAVE IN FILE
        }
        else if(ch == 12){
            //LOAD FROM FILE
        }
        else if(ch == 8){
            //BACKSPACE    
        }
        else{
            str += ch;
            list.insert(ch);
        }
    }
    list.display();
    cout << "LIST CONSTRUCTED SUCCESSFULLY" << endl;


}