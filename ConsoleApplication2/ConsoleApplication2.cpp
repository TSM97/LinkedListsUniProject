#include <iostream>
using namespace std;
#include <vector>
#include <list>
#define COUNT 10

int c,i,w1,w2 = 0;
int all = 0;
 int deletP=0;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	bool deleted = false;
};


int findMax(Node* root)
{
	if (root == NULL)
		return INT_MIN;

	int res=0;
	int lres = findMax(root->left);
	int rres = findMax(root->right);

	if (!root->deleted) {
		res = root->data;
	}
		if (lres > res)
			res = lres;
		if (rres > res)
			res = rres;
	
	return res;
}

int findMin(Node* root)
{
	if (root == NULL)
		return INT_MAX;
	int res= INT_MAX;
	int lres = findMin(root->left);
	int rres = findMin(root->right);

	if (!root->deleted) {
		res = root->data;
	}
	if (lres < res)
		res = lres;
	if (rres < res)
		res = rres;

	return res;
}

int findHeight(Node* root)
{
	int h = 0;
	if (root != NULL)
	{
		int lHeight = findHeight(root->left);
		int rHeight = findHeight(root->right);
		int maxHeight = max(lHeight, rHeight);
		h = maxHeight + 1;
	}
	return h;
}


void print2DUtil(Node* root, int space)
{
	if (root == NULL)
		return;

	space += COUNT;

	print2DUtil(root->right, space);

	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	if (root->deleted == false) {
		cout << root->data << "\n";
	}
	else {
		cout << root->data << "X"<< "\n";

	}

	print2DUtil(root->left, space);
}

void print2D(Node* root)
{
	// Pass initial space count as 0 
	print2DUtil(root, 0);
}


bool Search(Node* root, int data) {
	if (root == NULL)return false;
	else if (root->data == data && root->deleted == false)return true;
	else if (data <= root->data)return Search(root->left, data);
	else return Search(root->right, data);
}

void searchKey(Node*& curr, int key, Node*& parent)
{
	while (curr != NULL && curr->data != key)
	{
		parent = curr;

		if (key < curr->data) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
}



void deleteNode(Node*& root, int key)
{
	Node* parent = NULL;
	Node* curr = root;

	searchKey(curr, key, parent);

	if (curr == NULL) {
		return;
	}
	if (curr->left == NULL && curr->right == NULL)
	{
		if (curr != root)
		{
			if (parent->left == curr) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {
			root = NULL;
		}
		free(curr); 
	}
	else if (curr->left && curr->right)
	{

		curr->deleted = true;

	}
	else {
		Node* child = (curr->left) ? curr->left : curr->right;

		if (curr != root)
		{
			if (curr == parent->left) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}

		else {
			root = child;
		}

		free(curr);
	}

}

void TraverseL(struct Node* node, struct Node* root, int key, int arr[])
{
	if (node == NULL)
		return;
	TraverseL(node->left, root, key, arr);

	TraverseL(node->right, root, key, arr);

	if (node->data < key) {

		if (node->deleted) {
			int a = node->data;
			deleteNode(root, a);
		}
		else {
			int a = node->data;
			arr[i] = a;
			deleteNode(root, a);
			i++;
		}


	}

}

void TraverseR(struct Node* node, struct Node* root, int key, int arr[])
{
	if (node == NULL)
		return;
	// first recur on left subtree
	TraverseR(node->left, root, key, arr);

	// then recur on right subtree
	TraverseR(node->right, root, key, arr);

	if (node->data > key) {

		if (node->deleted) {
			//cout<<"deleted: " << node->data;
			int a = node->data;
			deleteNode(root, a);
		}
		else {
			int a = node->data;
			arr[i] = a;
			deleteNode(root, a);
			//cout << arr[i];
			i++;
		}


	}

}

Node* GetNewNode(int data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	bool deleted = false;
	return newNode;
}

Node* Insert(Node* root, int data) {
	if (root == NULL) {
		root = GetNewNode(data);
	}
	else if (data <= root->data) {
		root->left = Insert(root->left, data);
	}
	else {
		root->right = Insert(root->right, data);
	}

	return root;
}

void CheckLeft(struct Node*& node, int key)
{

	if (node == NULL)
		return;

	CheckLeft(node->right, key);
	CheckLeft(node->left, key);

	if (node->data < key) {
		if (node->deleted == false)all += 1;
		if (node->deleted) c += 1;

		if (c > all && all > 0 && findHeight(node) >= 3)cout << "TRUE";
		if (c > all && all > 0 && findHeight(node) >= 3) {
			deletP = node->data;
		}
	}


}

void CheckRight(struct Node*& node, int key)
{

	if (node == NULL)
		return;

	CheckRight(node->right, key);
	CheckRight(node->left, key);

	if (node->data > key) {
		if (node->deleted == false)all += 1;
		if (node->deleted) c += 1;

		if (c > all && all > 0 && findHeight(node) >= 3)cout << "TRUE";
		if (c > all && all > 0 && findHeight(node) >= 3) {
			deletP = node->data;
		}
		//cout << " "<< findHeight(node) << " ";
		//cout << node->data << " ";
	}


}

void DeletionL(struct Node* root) {
	c = 0;
	all = 0;
	i = 0;
	deletP = 0;
	CheckLeft(root, root->data);
	//cout << deletP;
	if (deletP != 0) {
		static int arr[100];
		TraverseL(root, root, root->data, arr);
		while (i != 0) {
			int a = arr[i - 1];
			root = Insert(root, arr[i - 1]);
			i--;
		}

	}

}

void DeletionR(struct Node* root) {
	c = 0;
	all = 0;
	i = 0;
    deletP = 0;
	CheckRight(root, root->data);
	//cout << deletP;
	if (deletP != 0) {
		static int arr[100];
		TraverseR(root, root, root->data, arr);
		while (i!=0) {
			int a = arr[i - 1];
			root=Insert(root,arr[i-1]);
				i--;
		}
		
	}

}

void Weighing(struct Node*& node, int w1, int w2,int key) {
	
	if (node == NULL)
		return;

	Weighing(node->right, w1,w2,key);
	Weighing(node->left, w1,w2,key);

	if (node->data > key) {
		w2 += 1;
	}
	else w1 += 1;


 }

void FindBetween(struct Node*& root, int k1, int k2) {
	if (root == NULL)
		return;

	FindBetween( root->right,  k1,  k2);
	FindBetween( root->left,  k1,  k2);

	if (root->data > k1 && root->data < k2 && root->deleted==false)
		cout <<" "<< root->data;

}


void deleteCheck(struct Node* root, int key) {
	deleteNode(root, key);
	DeletionR(root);
	DeletionL(root);
	
}




int main()
{
	//create empty tree
	Node* root = NULL;
	//root=Insert(root, 5);
	//root = Insert(root, 1);
	root = Insert(root, 15);
	root = Insert(root, 10);
	root = Insert(root, 20);
	root = Insert(root, 7);
	root = Insert(root, 13);
	root = Insert(root, 18);
	root = Insert(root, 22);

	root = Insert(root, 14);
	root = Insert(root, 11);
	root = Insert(root, 19);
	root = Insert(root, 1);
	root = Insert(root, 8);

	//max check example
	/*
	deleteCheck(root, 20);
	deleteCheck(root, 22);
	deleteCheck(root, 19);
	deleteCheck(root, 18);
    cout <<"TO MEGISTO EINAI TO "<< findMax(root)<<" ";  
	
	cout << "TO ELAXISTO EINAI TO "<<findMin(root)<< " ";
	*/



	print2D(root);
	/*
	int number;
	cout << "enter to be searched\n";
	cin >> number;
	if (Search(root, number) == true) cout << "found!\n";
	else cout << "NotFOUND!\n";
	*/
	

	//anadomisi dentro me tin diagrafi
	/*
	deleteCheck(root, 10);
	deleteCheck(root, 13);
	deleteCheck(root, 7);
    deleteCheck(root, 1);
	deleteCheck(root, 8);
	deleteCheck(root, 11);
	print2D(root);
	*/
	
	



	//psaxnw anamesa apo
	
	FindBetween(root, 13, 19);
	
	
	char p;
	cout<<"Write something to close....";
	cin>>p;
	

}

