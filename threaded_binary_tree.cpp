#include <iostream>
using namespace std;

struct Node {
   struct Node *left, *right;
   int data;
   bool leftThread;
   bool rightThread;
};
class Tree{
	public:
 Node* insert( Node* root, int key)
{
   Node* current = root;
   Node* parent = NULL;
   while (current != NULL) {
       if (key == (current->data)) {
           cout<<"Duplicate value !"<<endl;
           return root;
       }

       parent = current;  

       if (key < current->data) {
           if (current->leftThread == false)
               current = current->left;
           else
               break;
       }

       else {
           if (current->rightThread == false)
               current = current->right;
           else
               break;
       }
   }

   Node* temp = new Node;
   temp->data = key;
   temp->leftThread = true;
   temp->rightThread = true;

   if (parent == NULL) {
       root = temp;
       temp->left = NULL;
       temp->right = NULL;
   }
   else if (key < (parent->data)) {
       temp->left = parent->left;
       temp->right = parent;
       parent->leftThread = false;
       parent->left = temp;
   }
   else {
       temp->left = parent;
       temp->right = parent->right;
       parent->rightThread = false;
       parent->right = temp;
   }

   return root;
}
void searchValue(Node* root,int key){
	if (root == NULL)
       cout<<endl<<"Tree is empty"<<endl;

   Node* current = root;
   while (current->leftThread == false)
       current = current->left;

   while (current != NULL) {
       if (current->data==key)
	   {
		cout<<endl<<"Value Found !"<<endl;
		return;
	   }
	   
       current = inorderSuccessor(current);
   }
   cout<<endl<<"Value Not Found !"<<endl;
}
 Node* inSucc( Node* current)
{
   if (current->rightThread == true)
       return current->right;

   current = current->right;
   while (current->leftThread == false)
       current = current->left;

   return current;
}

 Node* inorderSuccessor( Node* current)
{
   if (current->rightThread == true)
       return current->right;

   current = current->right;
   while (current->leftThread == false)
       current = current->left;
   return current;
}

void inorder( Node* root)
{
   if (root == NULL)
       cout<<endl<<"Tree is empty"<<endl;

   Node* current = root;
   while (current->leftThread == false)
       current = current->left;

   while (current != NULL) {
       cout<<" "<<current->data;
       current = inorderSuccessor(current);
   }
}

 Node* inPred( Node* current)
{
   if (current->leftThread == true)
       return current->left;

   current = current->left;
   while (current->rightThread == false)
       current = current->right;
   return current;
}

 Node* case1(struct Node* root, struct Node* parent,struct Node* current)
{
   if (parent == NULL)
       root = NULL;

   else if (current == parent->left) {
       parent->leftThread = true;
       parent->left = current->left;
   }

   else {
       parent->rightThread = true;
       parent->right = current->right;
   }

   free(current);
   return root;
}

 Node* case2 (Node* root, Node* parent, Node* current)               
{
   Node* child;
   if (current->leftThread == false)
       child = current->left;

   else
       child = current->right;

   if (parent  == NULL)
       root = child;

   else if (current == parent ->left)
       parent ->left = child;

   else
       parent ->right = child;

   Node* s = inSucc(current);
   Node* p = inPred(current);

   if (current->leftThread == false)
       p->right = s;

   else {
       if (current->rightThread == false)
           s->left = p;
   }
   free(current);
   return root;
}

 Node* case3(Node* root, Node* parent,  Node* current)
{
   Node* parsucc = current;
   Node* succ = current->right;

   while (succ->leftThread==false) {
       parsucc = succ;
       succ = succ->left;
   }

   current->data = succ->data;

   if (succ->leftThread == true && succ->rightThread == true)
       root = case1(root, parsucc, succ);
   else
       root = case2(root, parsucc, succ);

   return root;
}

 Node* dThreadedBST( Node* root, int value)
{
   Node *parent  = NULL, *current = root;
   int found = 0;
   while (current != NULL) {
       if (value == current->data) {
           found = 1;
           break;
       }
       parent  = current;
       if (value < current->data) {
           if (current->leftThread == false)
               current = current->left;
           else
               break;
       }
       else {
           if (current->rightThread == false)
               current = current->right;
           else
               break;
       }
   }

   if (found == 0)
       cout<<endl<<"The value not present in tree"<<endl;

   else if (current->leftThread == false && current->rightThread == false)
       root = case3(root, parent , current);

   else if (current->leftThread == false)
       root = case2(root, parent , current);

   else if (current->rightThread == false)
       root = case2(root, parent , current);

   else
       root = case1(root, parent , current);

   return root;
}
int findMin(Node* root) {
    while (root!=NULL && root->leftThread!=true) {
        root = root->left;
    }
    return root->data;
}

int findMax(Node* root) {
    while (root!=NULL && root->rightThread!=true) {
        root = root->right;
    }
    return root->data;
}
};
int main()
{
   Tree t;
   Node* root=NULL;
   int choice;
   while (true)
   {
	cout <<endl<< "Menu:" << endl;
        cout << "1. Insert a value" << endl;
        cout << "2. Delete a value" << endl;
        cout << "3. Display tree (In order traversal)" << endl;
        cout << "4. Update a value" << endl;
        cout << "5. Search a value" << endl;
        cout << "6. Find max" << endl;
        cout << "7. Find min" << endl;
        cout << "8. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
		if (choice==1)
		{
			int key;
			cout<<endl<<"Enter Value: ";
			cin>>key;
			root=t.insert(root,key);
		}
		else if (choice==2)
		{
			int key;
			cout<<endl<<"Enter Value: ";
			cin>>key;
			root=t.dThreadedBST(root,key);
		}
		else if (choice==3)
		{
			t.inorder(root);
		}
		else if (choice==4)
		{
			int key;
			cout<<endl<<"Enter Value to Replace: ";
			cin>>key;
			root=t.dThreadedBST(root,key);
			cout<<endl<<"Enter New Value: ";
			cin>>key;
			root=t.insert(root,key);
			cout<<endl<<"Value has been Updated !"<<endl;
		}
		else if (choice==5)
		{
			int key;
			cout<<endl<<"Enter Value to Search: ";
			cin>>key;
			t.searchValue(root,key);
		}
		else if (choice==6)
		{
			cout<<endl<<"Max: "<<t.findMax(root)<<endl;
		}
		else if (choice==7)
		{
			cout<<endl<<"Min: "<<t.findMin(root)<<endl;
		}
		
		else  if (choice==8)
		{
			break;
		}
		else{
			cout<<endl<<"Invalid Input !"<<endl;
		}
   }
}
