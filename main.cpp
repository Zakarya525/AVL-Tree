#include <iostream>
#include <time.h>
using namespace::std;

class Node{
	public:
		double data;
		int key;
		int height;
		
		Node* leftChild;
		Node* rightChild;

		Node(int key, double data){
			this->key = key;
			this->data = data;
			this->height = 0;
			leftChild = NULL;
			rightChild = NULL;
			
		}
		void diplay(){
			cout<<"Key "<<key<<" Height "<<height<<endl;
		}
	};
	
	class AVLTree{
		public:
			Node* root;
			bool check;
		
			AVLTree(){
				root = NULL;
				check = true;
			}
		
		int avlHeight(Node* current){
			if(current == NULL){
				return -1;
			}
			return(1 + max(avlHeight(current->leftChild), avlHeight(current->rightChild)));
		}
		
		int BF(Node* current){
			int heightLeft, heightRight;
			if(current == NULL){
				return 0;
			}
			else{
				if(current->leftChild == NULL){
					heightLeft = 0;
				}
				else{
					heightLeft = 1 + current->leftChild->height;
				}
				
				if(current->rightChild == NULL){
					heightRight = 0;
				}
				else{
					heightRight = 1 + current->rightChild->height;
				}
			}
			
			return (heightLeft - heightRight);
		}
	
		
		Node* rightRotation(Node* x){	//clockwise rotation (when height is max on the left sub-tree)
			Node* y;
			y = x->leftChild;
			x->leftChild = y->rightChild;
			y->rightChild = x;
			
			x->height = avlHeight(x);
			y->height = avlHeight(y);
			
			return y;
		}
		
		Node* leftRotation(Node* x){	//anti-clockwise (when height is max on the right sub-tree)
			Node* y;
			y = x->rightChild;
			x->rightChild = y->leftChild;
			y->leftChild = x;
			
			x->height = avlHeight(x);
			y->height = avlHeight(y);
			
			return y;
			
			
		}
		
		Node* rightLeft(Node* T){
			T->rightChild = rightRotation(T->rightChild);
			T = leftRotation(T);
		}
		
		
		Node* leftRight(Node* T){
			T->leftChild = leftRotation(T->leftChild);
			T = rightRotation(T);
		}
		
		Node* balance(Node* currentRoot, int key){
			
			
			int balancing_factor = BF(currentRoot);
			
			if(balancing_factor == -2){	
				if(key > currentRoot->rightChild->key){
					currentRoot = leftRotation(currentRoot);
					cout<<"Left rotation done for "<<currentRoot->key<<endl;
				}
				else{
					currentRoot = rightLeft(currentRoot);
					cout<<"RightLeft rotation done for "<<currentRoot->key<<endl;
				}
			}
			
			else if(balancing_factor == 2){
				
				if(key < currentRoot->leftChild->key){
					currentRoot = rightRotation(currentRoot);
					cout<<"Right rotation done for "<<currentRoot->key<<endl;
				}
				else{
					
					currentRoot = leftRight(currentRoot);
					cout<<"LeftRight rotation done for "<<currentRoot->key<<endl;
					}
			}
			return currentRoot;
		}	
						
			
					
	
		Node* avlInsert(Node* currentRoot, int key, double data){
			if(currentRoot == NULL){
				
				currentRoot = new Node(key, data);
				return currentRoot;
			
			}
			
			if(key > currentRoot->key){
			
					currentRoot->rightChild = avlInsert(currentRoot->rightChild, key, data); //go right
					currentRoot = balance(currentRoot, key); //balance() will balance the tree.
				}
				
			else if(key < currentRoot->key){
					currentRoot->leftChild = avlInsert(currentRoot->leftChild, key, data);	//go left
					currentRoot = balance(currentRoot, key);
				} 
		
			currentRoot->height = avlHeight(currentRoot);	//update the height
			
			return currentRoot;
		}
			
		
		void inOrderTraverse(Node* localRoot){
				if(localRoot != NULL){
					inOrderTraverse(localRoot->leftChild);
					localRoot->diplay();
					inOrderTraverse(localRoot->rightChild);
					
				} 
				
			}
	
		
		Node* maximum(Node* current){
			
			while(current->rightChild != NULL){
				current = current->rightChild;
			}
			return current;
		}
		
		Node* minimum(Node* current){
			
			while(current->leftChild != NULL){
				current = current->leftChild;
			}
			return current;
		}
				
		Node* deleteNode(Node *root, int key){		//recursively delete function  
			
			if(root == NULL) 
				return NULL; 
			
			else if(key < root->key) 
				root->leftChild = deleteNode(root->leftChild, key);	//go left
			
			else if (key > root->key) 
				root->rightChild = deleteNode(root->rightChild, key);	//go right
			
			else {
				if(root->leftChild == NULL and root->rightChild == NULL){
					
					if(check){
						cout<<"Node with no child deleted"<<endl;
					}
					return NULL;
				}
				
			    else if(root->leftChild == NULL) {
					Node *current = root->rightChild;
					if(check){
						cout<<"Node with one right child deleted"<<endl;
					}
					return current;
				
				}
				
				else if(root->rightChild == NULL) {
					Node *current = root->leftChild;
					if(check){
						cout<<"Node with one left child deleted"<<endl;
					}
					return current;
				
				}
				
				else { 
					check = false;
					if(check == false){
						cout<<"Node with two child deleted"<<endl;
					}
					
					if(root->leftChild->height > root->rightChild->height)
					{
						Node* current = maximum(root->leftChild); 
						root->key = current->key;
						root->leftChild = deleteNode(root->leftChild, current->key);
					}
					else
					{
						Node* current = minimum(root->rightChild); 
						root->key = current->key;
						root->rightChild = deleteNode(root->rightChild, current->key);
					}
					
				}
			}
			
			root->height = avlHeight(root); //to update the height
			root = balance(root, key);		//to balance the tree from deleted node to root recursively if any..
			
			return root;
	}
	
	Node* pupolateTree(Node* root, int N){
		
			srand(time(NULL));	//to get rid of the same generation of values
			for(int i = 0; i < N; i++){
				int key = rand()%1000;
				root = avlInsert(root, key, 78.7);
				cout<<"Node with "<<key<<" successfully inserted."<<endl;
			}
		return root;	
		}

}; 

int main(int argc, char** argv) {
	AVLTree* tree = new AVLTree();
	//checking
	cout<<"Enter the node, you wanna insert, limit: ";
	int n;
	cin>>n;
	tree->pupolateTree(tree->root, n); //to fill tree with 20 nodes
	
	tree->inOrderTraverse(tree->root);
	tree->deleteNode(tree->root, 51);
	cout<<endl;
	tree->inOrderTraverse(tree->root);
	
		
	return 0;
}




