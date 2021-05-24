#include "tree.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
//source: https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-introduction-to-algorithms-sma-5503-fall-2005/video-lectures/lecture-10-red-black-trees-rotations-insertions-deletions/lec10.pdf
using namespace std;
void tree::read_file(char * file_name){
	FILE * file;
	file = fopen(file_name,"r");
	char buff[150];
	if(file){
		while(fgets(buff,150,file)){
			insert(new node(atoi(buff)));
		}
	}
	else{
		cout << "No file"<<endl;
	}
}
void tree::rb_delete(node * to_delete){
	nullptr;
}
void tree::bst_delete(node * to_delete){
	node * p = to_delete->parent;
	if(to_delete->left and to_delete->right){
	
	}
	else if(to_delete->left){
	
	}
	else if(to_delete->right){
		
	}
	else{
		if(to_delete->red){
			p->left==to_delete ? p->left=nullptr:p->right=nullptr;
			delete to_delete;
		}
		else{
			if(p->left = to_delete){
				
			}
			else{
				
			}
		}
	}
}
void tree::del(int num){
	itr = root;
	while(itr){
		if(num >itr->value){
			itr = itr->right;
		}
		else if(num < itr->value){
			itr = itr->left;
		}
		else{
			bst_delete(itr);
		}
	}
}
void tree::insert(node * to_add){
	if(!root){
		root = to_add;
		root->red = false;
	}	
	else{
		itr = root;
		to_add->red = true;
		while(true){
			if(to_add->value> itr->value){
				if(itr->right){
					itr = itr->right;
				}
				else{
					itr->right = to_add;
					to_add->parent = itr;
					break;
				}
			} 
			else if(to_add->value < itr->value){
				if(itr->left){
					itr = itr->left;
				}
				else{
					itr->left = to_add;
					to_add->parent = itr;
					break;
				}
			}
			else{
				cout << "Duplicate Value"<<endl;
				delete to_add;
				return;
			}
		}
		fix_tree(to_add);
		root->red = false;		
	}
	
}
void tree::fix_tree(node * new_node){
	node * gp;
	node * p;
	while(new_node->parent and new_node->parent->red){
		gp = new_node->parent->parent;
		p = new_node->parent;
		if(gp and gp->left == p){
			if(gp->right and gp->right->red){
				gp->left->red = gp->right->red = 0;
				gp->red = 1;	
			}
			else{
				if(p->right == new_node){
					gp->left = new_node;
					p->right = new_node->left;
					new_node->left = p;
					if(p->right){
						p->right->parent = p;
					}
					new_node->parent = gp;
					p->parent = new_node;
					swap(p,new_node);
				}
				p->left = p->right;
				p->right = gp->right;
				gp->left = new_node;
				gp->right = p;
				swap(p->value,gp->value);
				new_node->parent = gp;
				if(p->right){
					p->right->parent = p;
				}
			}
		}
		else if(gp and gp->right == p){
			if(gp->left and gp->left->red){
				gp->left->red = gp->right->red = 0;
				gp->red = 1;
			}
			else{
				//break;
				if(p->left == new_node){
					gp->right = new_node;
					p->left = new_node->right;
					new_node->right = p;
					if(p->left){
						p->left->parent = p;
					}
					new_node->parent = gp;
					p->parent = new_node;
					swap(new_node,p);
				}
				p->right = p->left;
				p->left = gp->left;
				gp->right = new_node;
				gp->left = p;
				swap(gp->value,p->value);
				new_node->parent = gp;
				if(p->left){
					p->left->parent = p;
				}
			}
		}
	}
}
void tree::print_util(node * in_node, int spaces){
	if(in_node == nullptr){
		return;
	}
	spaces+=5;
	print_util(in_node->right,spaces);
	cout << endl;
	for(int i = 0; i<spaces; i++){
		cout << " ";
	}
	in_node->red ? cout<< in_node->value<<" red"<<endl : cout << in_node->value<<" black"<<endl;
	print_util(in_node->left,spaces);
}
void tree::print(){
	print_util(root,0);
}
tree::~tree(){
	if(root and root->left){
		delete root->left;
	}
	delete root;
	if(root and root->right){
		delete root->right;
	}
}
