//sg
#include<iostream>
#include "tree.h"
#include "Char.cpp"
using namespace std;
int main()
{
	Char rootVal('a');
	cout<<"\nTree input : Level by Level\n\nEnter 0 to specify leave\n\n";
	
	cout<<"Enter root node value " ;
	cin>>rootVal;
	Tree<Char> * t=new  Tree<Char>(rootVal);
	cin>>(*t);
	t->prettyPrint(t->getHead());
	t->prettyPrint(t->getMirror(t->getHead()));
	t->treeStatPrinter();
	bool res1=t->isMirror(t->getHead(),t->getMirror(t->getHead()));
	if(res1)
	cout<<"\n\nTrees printed above are mirrors!\n\n";
	return 0;
}
