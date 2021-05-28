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
node* tree::get_pred(node * in_node){
	if(in_node->right){
		return get_pred(in_node->right);	
	}
	else{
		return in_node;
	}
}
void tree::fix(node * p){
	node * c;
	node * gc;
	if(!(p->right) and p->left){
		if(p->left->right){
			gc = p->left->right;
			c = p->left;
			lrl(p,c,gc);
		}
		c = p->left;
		gc = p->left->left;
		lrotate(p,c,gc);
		if(p->right){
			p->right->parent = c;
		}
		if(gc){
			gc->parent = p;
		}
	}
	else if(!(p->left) and p->right){
		if(p->right->left){
			gc = p->right->left;
			c = p->right;
			rlr(p,c,gc);
                }
		c = p->right;
		gc = p->right->right;
            	rrotate(p,c,gc); 
                if(p->left){
                        p->left->parent = c;
                }
                if(gc){
                        gc->parent = p;
                }
	}
	if(p->left){
		p->left->red = 0;
	}
	if(p->right){
		p->right->red = 0;
	}
}
node * tree::get_succ(node * in_node){
	if(in_node->left){
                return get_pred(in_node->left);
        }
        else{
                return in_node;
        }
}
void tree::fix_double_blk(node * replace){
	node * p = replace->parent;
	node * sib;
	if(!p){
		itr = root;
		if(root->left){
			root = root->left;
		}
		else{
			root = root->right;
		}
		delete itr;
		return;
	}
	if(p->left == replace){
		sib = p->right;
		if(check_red(sib)){
			swap(p->value,sib->value);
			p->right = sib->right;
			if(sib->right){
				sib->right->parent = p;
			}
			sib->right = sib->left;
			sib->left = p->left;
			if(p->left){
				p->left->parent = sib;
			}
			p->left = sib;
			if(sib->right){
				sib->right->red = 1;
			}
			if(p->left){p->left->red = 0;}
			if(p->right){p->right->red = 0;}	
			if(!(sib->red)){
				fix(p);
			}
		}
		else{
			if(p->right){
				p->right->red = 1;
			}
			if(p!=root and !(p->red)){
				fix_double_blk(p);	
			}
			else{
				p->red = 0;
			}
		}
	}
	else{
		if(check_red(p->left)){
			sib = p->left;//p
			if(check_red(sib)){//r bb
                                swap(p->value,sib->value);
				p->left = sib->left;
				if(sib->left){
					sib->left->parent = p;
				}
				sib->left = sib->right;
				sib->right = p->right;
				if(p->right){
					p->right->parent = sib;
				}
				p->right = sib;
				if(sib->left){
					sib->left->red = 1;
				}
				if(p->left){p->left->red = 0;}
				if(p->right){p->right->red = 0;}
				if(!(sib->red)){
					fix(p);
				}
                        }
		}
		else{
			if(p->left){
				p->left->red = 1;
			}
			if(p!=root and !(p->red)){
                                fix_double_blk(p);
                        }
			else{
				p->red = 0;
			}	
		}
	}
}
void tree::get_replacement(node * to_delete){
	node * p = to_delete->parent;
	node* replace;
	if(p){
		replace = to_delete==p->left?get_pred(to_delete->left):get_succ(to_delete->right);
	}
	else{
		replace = get_succ(to_delete->right);
	}
		
	if(check_red(replace)){
		if(replace->right or replace->left){
			replace->right?replace->right->red=0:replace->left->red=0;
		}
	}
	else{
		fix_double_blk(replace);			
	}
	if(replace->right){
		if(replace->parent->right == replace){
			replace->parent->right = replace->right;
		}
		else{
			replace->parent->left = replace->right;
		}
		replace->right->parent = replace->parent;
		replace->right->red = replace->red;
	}
	else{
		if(replace->parent->right == replace){
			replace->parent->right = replace->left;
		}
		else{
			replace->parent->left = replace->right;
		}
		if(replace->left){
			replace->left->parent = replace->parent;
			replace->left->red = replace->red;
		}
	}
	swap(to_delete->value, replace->value);	
	delete replace;
}
bool tree::check_red(node * sibling){
	return sibling and ((sibling and sibling->red) or (sibling->left and sibling->left->red) or (sibling->right and sibling->right->red));
}
void tree::bst_delete(node * to_delete){
	node * p = to_delete->parent;	
	if(to_delete->left and to_delete->right){
		get_replacement(to_delete);
	}
	else if(to_delete->left){
		if(!p){
			root = to_delete->left;
			return;
		}
		if(!check_red(to_delete)){
			fix_double_blk(to_delete);
		}		
		p->left = to_delete->parent;
		p->left==to_delete?p->left=to_delete->left:p->right=to_delete->left;
		p->left->parent = p;
		p->left->red = 1;
		delete to_delete;
		
	}
	else if(to_delete->right){
		if(!p){
			root = to_delete->left;
			return;
		}
		if(!check_red(to_delete)){
			fix_double_blk(to_delete);
		}
			p = to_delete->parent;
			p->left==to_delete?p->left=to_delete->right:p->right=to_delete->right;
                        p->left->parent = p;
			p->left->red = 1;
			delete to_delete;
	}
	else{
		if(!p){
			root = nullptr;
			return;
		}
		if(to_delete->red){
			p->left==to_delete?p->left=nullptr:p->right=nullptr;
		}
		else{
			fix_double_blk(to_delete);
			p = to_delete->parent;
			if(p->left == to_delete){
				p->left = nullptr;
			}
			else{
				p->right = nullptr;
			}
		}
		delete to_delete;
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
		else if(num == itr->value){
			bst_delete(itr);
			break;
		}
	}
}
void tree::insert(node * to_add){
	to_add->left=to_add->right=to_add->parent=nullptr;
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
void tree::lrotate(node *gp,node *p, node *new_node){
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
void tree::rrotate(node *gp,node *p, node *new_node){
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
void tree::lrl(node *gp,node *p, node *new_node){
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
void tree::rlr(node *gp,node *p, node *new_node){
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
				new_node = gp;	
			}
			else{
				if(p->right == new_node){
					lrl(gp,p,new_node);
				}
				lrotate(gp,p,new_node);	
			}
		}
		else if(gp and gp->right == p){
			if(gp->left and gp->left->red){
				gp->left->red = gp->right->red = 0;
				gp->red = 1;
				new_node = gp;
			}
			else{
				//break;
				if(p->left == new_node){
					rlr(gp,p,new_node);	
				}
				rrotate(gp,p,new_node);
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
void tree::recur_delete(node * in_node){
	if(in_node and in_node->left){
		recur_delete(in_node->left);
	}
	if(in_node and in_node->right){
		recur_delete(in_node->right);
	}
	if(in_node){
		delete in_node;
	}
}
tree::~tree(){
	recur_delete(root);
}
