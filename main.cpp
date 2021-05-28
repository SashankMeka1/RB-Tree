#include "tree.h"
#include <iostream>
#include <cstring>
using namespace std;
int main(){
	tree * main_tree = new tree();
	char input[150];
	while(true){
		cout << "ADD, PRINT, FILE, EXIT, DELETE"<<endl;
		cin.getline(input,150);
		if(!strcmp(input,"ADD")){
			cout << "Number?"<<endl;
			cin.getline(input,150);
			main_tree->insert(new node(atoi(input)));
		}
		else if(!strcmp(input,"DELETE")){
			cout << "Number?"<<endl;
			cin.getline(input,150);
			main_tree->del(atoi(input));
		}
		else if(!strcmp(input,"PRINT")){
			main_tree->print();
		}
		else if(!strcmp(input,"FILE")){
			cout << "File name?"<<endl;
			cin.getline(input,150);
			main_tree->read_file(input);
		}
		else if(!strcmp(input,"EXIT")){
			break;
		}
		else{
			cout << "Invalid"<<endl;
		}
	}
	delete main_tree;
	return 0;
}
