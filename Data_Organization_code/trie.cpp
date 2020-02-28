
#include <bits/stdc++.h> 
using namespace std; 

const int t_size = 26; 

struct treenode 
{ 
	struct treenode *children[t_size]; 
	bool end; 
}; 

struct treenode *getNode(void) 
{ 
	struct treenode *pnode = new treenode; 

	pnode->end = false; 

	for (int i = 0; i < t_size; i++) 
		pnode->children[i] = NULL; 

	return pnode; 
} 

void insert(struct treenode *root, string key) 
{ 
	struct treenode *node = root; 

	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = key[i] - 'a'; 
		if (!node->children[index]) 
			node->children[index] = getNode(); 

		node = node->children[index]; 
	} 
	node->end = true; 
} 

bool search(struct treenode *root, string key) 
{ 
	struct treenode *node = root; 

	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = key[i] - 'a'; 
		if (!node->children[index]) 
			return false; 

		node = node->children[index]; 
	} 

	return (node != NULL && node->end); 
} 

int main() 
{ 
	int a;
	cout << "\nEnter the no String: ";
	cin>>a;
	string keys[a],s;
	for(int j=0;j<a;j++)
	{
		cout<<"\nEnter the string: ";
		cin>>s;
		keys[j]=s;
	} 

	struct treenode *root = getNode(); 

	for (int i = 0; i < a; i++) 
		insert(root, keys[i]); 
	
	cout << "\nEnter the String you wants to search: ";
	cin>>s;
	
	if(search(root,s))
		 cout << "\nYes\n";
	else
		 cout << "\nNo\n"; 
	return 0; 
} 

