#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<string>
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
        listNode* prev;
        listNode(char ch){
            this->ch = ch;
            next = NULL;
            prev = NULL;
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

        void removeLast(){
            if(head == NULL){
                return;
            }
            if(head->next == NULL){
                delete head;
                head = NULL;
                tail = NULL;
                return;
            }
            queueNode* temp = head;
            while(temp->next->next != NULL){
                temp = temp->next;
            }
            queueNode* temp1 = temp->next;
            tail = temp;
            temp->next = NULL;
            delete temp1;
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
                tail->next->prev = tail;
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

        void deleteNode(){
            if(head == NULL){
                return;
            }
            else if(tail == NULL){
                return;
            }
            else if(head->next == NULL){
                delete head;
                head = NULL;
                tail = NULL;
                return;
            }
            else{    
                listNode* temp = tail;
                tail = tail->prev;
                if(tail != NULL){
                    tail->next = NULL;
                } 
                else{
                    head = NULL;
                }
                delete temp;
            }
        }
        void deleteList(){
            listNode* temp = head;
            while(temp != NULL){
                listNode* temp1 = temp;
                temp = temp->next;
                delete temp1;
            }
        }

        bool isEmpty(){
            return head == NULL;
        }
};

void clearScreen(){
    system("cls");
}

string letterSubstitution(AVL tree, string str){
    string temp = str;
    for(int i = 0; i < str.length(); i++){
        for(int j = 0; j < 26; j++){
            temp[i] = 'a' + j;
            if(tree.search(temp) != NULL){
                return temp;
            }
        }
        temp = str;
    }
    return "\0";
}

string letterOmmission(AVL tree, string str){
    string temp = str;
    string temp1 = "";
    for(int i = 0; i < str.length(); i++){
        temp1 = "";
        for(int j = 0; j < str.length(); j++){
            if(j != i){
                temp1 += str[j];
            }
        }
        if(tree.search(temp1) != NULL){
            return temp1;
        }
    }
    return "\0";
}

string letterInsertion(AVL tree, string str){
    string temp = str;
    string temp1 = "";
    for(int i = 0; i <= str.length(); i++){
        for(int j = 0; j < 26; j++){
            temp1 = "";
            for(int k = 0; k < str.length(); k++){
                if(k == i){
                    temp1 += 'a' + j;
                }
                temp1 += str[k];
            }
            if(tree.search(temp1) != NULL){
                return temp1;
            }
        }
    }
    return "\0";
}

string letterReversal(AVL tree, string str){
    string temp = str;
    string temp1 = "";
    for(int i = 0; i < str.length()-1; i++){
        temp1 = "";
        for(int j = 0; j < str.length(); j++){
            if(j == i){
                temp1 += str[j+1];
                temp1 += str[j];
                j++;
            }
            else{
                temp1 += str[j];
            }
        }
        if(tree.search(temp1) != NULL){
            return temp1;
        }
    }
    return "\0";
}

int main(){
    clearScreen();
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
//    cout << "TREE CONSTRUCTED SUCCESSFULLY" << endl;

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
    Queue queue;
    char ch;
    string str = "";
    while(1){
        ch = getch();
        if(ch == 27){
            list.deleteList();
            queue.deleteQueue();
            tree.deleteTree();
            break;
        }
        else if(ch == 32){
            //SPACE
            while(!queue.isEmpty()){
                str += queue.dequeue();
            }
//            cout << endl << str << endl;
//            getch();
            Node* temp = tree.search(str);
            if(temp == NULL){
                string correct1 = letterSubstitution(tree, str);
                cout << endl <<  correct1 << "\t\t" ;
                string correct2 = letterOmmission(tree, str);
                cout << correct2 << "\t\t";
                string correct3 = letterInsertion(tree, str);
                cout << correct3 << "\t\t";
                string correct4 = letterReversal(tree, str);
                cout << correct4 << endl;
                char choice = getch();
                if(choice == '1'){
                    while(list.tail != NULL && list.tail->ch != ' ' && list.isEmpty()==false){
                        list.deleteNode();
                    }
                    for(int i = 0; i < correct1.length(); i++){
                        list.insert(correct1[i]);
                    }
                }
                else if(choice == '2'){
                    while(list.tail != NULL && list.tail->ch != ' ' && !list.isEmpty()){
                        list.deleteNode();
                    }
                    for(int i = 0; i < correct2.length(); i++){
                        list.insert(correct2[i]);
                    }
                }
                else if(choice == '3'){
                    while(list.tail != NULL && list.tail->ch != ' ' && !list.isEmpty()){
                        list.deleteNode();
                    }
                    for(int i = 0; i < correct3.length(); i++){
                        list.insert(correct3[i]);
                    }
                }
                else if(choice == '4'){
                    while(list.tail != NULL && list.tail->ch != ' ' && !list.isEmpty()){
                        list.deleteNode();
                    }
                    for(int i = 0; i < correct4.length(); i++){
                        list.insert(correct4[i]);
                    }
                }
            }
            list.insert(' ');
            str="";
        }
        else if(ch == 19){                  //Ctrl + S
            fstream file;
            file.open("output.txt", ios::out);
            file << "";
            file.close();
            file.open("output.txt", ios::app);
            listNode* temp = list.head;
            while(temp != NULL){
                file << temp->ch;
                temp = temp->next;
            }
            file << endl;
            file.close();
        }
        else if(ch == 12){                  //Ctrl + L
            list.deleteList();
            fstream file;
            file.open("output.txt");
            string str;
            while(getline(file, str)){
                for(int i = 0; i < str.length(); i++){
                    list.insert(str[i]);
                }
                list.insert(' ');
            }
            file.close();
        }
        else if(ch == 8){                   //BACKSPACE
            if(list.tail->ch == ' '){
                list.deleteNode();
                clearScreen();
                list.display();
                listNode* temp = list.tail;
                while(temp->ch != ' ' && temp != list.head){
                    temp = temp->prev;
                }
                if(temp->ch == ' '){
                    temp = temp->next;
                }
                while(temp != NULL){
                    queue.enqueue(temp->ch);
                    temp = temp->next;
                }
            }
            else{
                if(!list.isEmpty())
                    list.deleteNode();  
                if(!queue.isEmpty())
                    queue.removeLast();
            }
        }
        else{
            list.insert(ch);
            queue.enqueue(ch);
        }
        clearScreen();
        list.display();
    }
}