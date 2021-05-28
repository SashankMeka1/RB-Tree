struct node{
	node * left = nullptr;
	node * right = nullptr;
	node * parent = nullptr;
	bool red;
	int value;
	node(int in_value){value = in_value;}
};
class tree{
	private:
	node * root = nullptr;
	node * itr = nullptr;
	public:
	void recur_delete(node * in_node);
	void rrotate(node *gp,node *p, node * new_node);
	void lrotate(node *gp,node *p, node * new_node);
	void rlr(node *gp,node *p, node * new_node);
	void lrl(node *gp,node *p, node * new_node);
	void fix(node * p);
	void fix_double_blk(node * replace);
	void get_replacement(node* to_delete);
	node * get_succ(node*in_node);
	node *get_pred(node*in_node);
	bool check_red(node * sibling);
	void bst_delete(node * to_delete);
	void read_file(char * file_name);
	void del(int num, bool del);
	void insert(node * to_add);
	void fix_tree(node * new_node);
	void print();
	void print_util(node * in_node, int spaces);
	~tree();	
};
