#include<cstdlib>
#include<iostream>
#include"treap.h"

using namespace std;

void indent(int num = 2, char sep='-'){
	for(int i = 0;i < num;++i) cout << sep;
}

void analyze(string tree, int depth = 0){
	string subtree(tree, 1, tree.length() - 2);

	//indent(depth);
	//cout << subtree << endl;

	int count = 0;
	int i = 0;
	if(subtree[0] == '('){
		for(i = 0;i < subtree.length();++i){ // Left subtree
			if(subtree[i] == '(') count++;
			else if(subtree[i] == ')') count--;
			if(count <= 0){
				string new_tree(subtree, 0, i+1);
				analyze(new_tree, depth+1);
				break;
			}
		}
		i++; // Move i off closing parenthesis
	}

	int j = 0;
	for(j = i;j < subtree.length();++j){
		if(subtree[j] == '(') break;
	}

	string current(subtree, i, j-i);
	indent(depth);
	cout << current << endl;

	if(subtree[j] == '('){
		string right(subtree, j);
		analyze(right, depth+1);
	}
}

int main(int argc, char *argv[]){
	//((1:13:1:2((2:6:1:2)3:12:2:4(4:12:1:2)))5:14:4:9(((6:3:1:2)7:5:2:4)8:12:3:6((9:4:1:2)10:8:0:1)))
	string example = "((((A:21:0)B:24:1)C:35:2((D:8:0)E:33:1))G:50:5(H:29:4(I:25:3((J:13:1(K:9:0))L:16:2))))";
	if(argc == 2){
		example = string(argv[1]);
	}

	analyze(example);

	return 0;
}
