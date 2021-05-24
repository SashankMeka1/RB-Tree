struct node{
	node * left;
	node * right;
	node * parent;
	bool red;
	int value;
	node(int in_value){value = in_value;}
};
class tree{
	private:
	node * root;
	node * itr;
	public:
	void rb_delete(node * to_delete);
	void bst_delete(node * to_delete);
	void read_file(char * file_name);
	void del(int num);
	void insert(node * to_add);
	void fix_tree(node * new_node);
	void print();
	void print_util(node * in_node, int spaces);
	~tree();	
};
