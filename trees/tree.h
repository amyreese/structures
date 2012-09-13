//sg
/* A simple program to learn about binary trees.
 * Author : Aman Madaan <madaan.amanmadaan@gmail.com>
 */
#include<iostream>
#include<string>
#include<queue>
using namespace std;
/* A NODE OF THE TREE*/
template <class T>
struct TreeNode
{
	T  data;
	TreeNode * left,*right;
	TreeNode(T data)
	{
		this->data=data;
		left=right=NULL;
	}
};
/*CLASS REPRESENTING A TREE*/
template <class T>
class Tree
{
	TreeNode<T> * head;
	public:
	Tree(T  data)
	{
		head=new TreeNode<T>(data);
	}
	
	TreeNode<T>* getHead()
	{
		return head;
	}
	/*Reading a tree */
	template<class L>
	friend istream& operator >> (istream& i,Tree<L>& t);
	/*Standard traversals*/
	void inorder(TreeNode<T>* head);
	void preorder(TreeNode<T>* head);
	void postorder(TreeNode<T>* head);
	/*Calculating height*/
	int  height(TreeNode<T>* head);
	/*Determining type of nodes*/
	int  internalNodes(TreeNode<T>* head);
	int  totalNodes(TreeNode<T>* head);
	int  leafNodes(TreeNode<T>* head);
	/* Tree summary*/
	void treeStatPrinter();
	/*Printing the tree*/
	void prettyPrint(TreeNode<T>* head);
	/* Mirror : calculation and check*/
	TreeNode<T>*  getMirror(TreeNode<T>* head);
	bool  isMirror(TreeNode<T>* head1,TreeNode<T>* head2);
};
template<class T>
TreeNode<T>* Tree<T>::getMirror(TreeNode<T>* head)
{
	if(!head)  //required for non leafs
	{
		return NULL;
	}
	if(head->left==NULL&&head->right==NULL)
	{
		return head;
	}
	TreeNode<T> * nN=new TreeNode<T>(head->data);
	nN->left=getMirror(head->right);
	nN->right=getMirror(head->left);
	return nN;
}
template<class T>
bool Tree<T>::isMirror(TreeNode<T>* head1,TreeNode<T>* head2)
{
	if(head1==NULL && head2==NULL)
	return true;
	if((head1==NULL && head2!=NULL)&&(head2==NULL && head1!=NULL))
	return false;
	if(head1->data==head2->data)
	{return isMirror(head1->left,head2->right)&&isMirror(head1->right,
	head2->left);
}
	//else
	return false;
}
template<class T>
void Tree<T>::prettyPrint(TreeNode<T>* head)
{
	/* Prints the tree on the basis of following pattern
	 * of spaces that is observed with binary trees :  
	 *  <--------2^h-----------><--------2^h----------->
	 *  
	 *  <--2^(h-1)--><--------2^h---------><--2^(h-1)-->
	 *  
	 *  <-2^(h-2)-><--2^(h-1)--><--2^(h-1)--><-2^(h-2)->
	 * 
	 * Maintains 2 queues : 
	 * 1. Ready queue : This queue contains all nodes of the same level
	 * 2. Print queue : Nodes to be printed. 
	 * Head is first added to the ready queue, then for each level,
	 * a node is taken out from ready queue,added to print queue and then
	 * it's children are inserted into the ready queue.
	 * This helps in maintaining a Breadth first traversal.
	 * 
	 * The function is far from perfect, but prints "ok" looking trees 
	 * for most of the cases.
	 * Eg : A special case ,Left skewed tree and it's mirror image
	 * [aman@aman trees]$ ./a.out 
	 * Enter root node value 1

	 * Enter left child of  1 : 2
	 * Enter right child of 1 : 0

	 * Enter left child of  2 : 3
	 * Enter right child of 2 : 0

	 * Enter left child of  3 : 0
	 * Enter right child of 3 : 0
	 *     1    

	 *   2         

	 *  3           

	 *     1    

	 *        2    

	 *           3  
	 */
	queue<TreeNode<T>*> ready;
	queue<TreeNode<T>*> print;
	TreeNode<T>* curr,*currP;
	int ht=height(head);
	int nl=ht+1;
	//whitespace
	int wsBEG=1<<ht;//white space start
	int wsIBW=wsBEG;
	
	/*ready queue at any time stores the nodes that belong to the 
	 * same level only*/
	 
	/*add head to ready queue*/
	ready.push(head);
	do
	{
	//fill print queue
	while(!ready.empty())
	{
		curr=ready.front();
		if(curr==NULL) 
		{
		print.push(NULL);
		ready.pop();  //delete the null
		continue;
		}
		ready.pop();
		//fill print queue
		print.push(curr);
	}
	for(int i=0;i<wsBEG;i++)
	{
		cout<<" ";
	}
	//print all of these and refill the ready queue
	while(!print.empty())
	{
		currP=print.front();
		print.pop();
	
		if(currP==NULL)
		{
			cout<<" ";
			/*a null should also ensure 
			 * that his children are 
			 * NULLs, this shall help in printing a balanced
			 * tree*/
			
			ready.push(NULL);
			ready.push(NULL);
		
		}
		else
		{
		cout<<currP->data;
		ready.push(currP->left);
		ready.push(currP->right);
		}
			for(int i=0;i<wsIBW;i++)
		{
		cout<<" ";
		}
	}
	wsIBW=wsBEG;
	wsBEG=wsBEG>>1;
	cout<<"\n\n";
	}while(--nl);	
}
template<class T>
void Tree<T>::treeStatPrinter()
{
	cout<<"\n\t\tTREE STATS\n\n";
	cout<<"_____________________\n";
	cout<<"\tInorder Trace = ";inorder(head);cout<<"\n";
	cout<<"\n\tHeight = "<<height(head)<<"\n";
	cout<<"\n\tInternal Nodes = "<<internalNodes(head)<<"\n";
	cout<<"\n\tLeaf Nodes = "<<leafNodes(head)<<"\n";
	cout<<"\n\tTotal Nodes = "<<totalNodes(head)<<"\n";
	cout<<"_____________________\n";
}
template<class T>
int Tree<T>::height(TreeNode<T>* head)
{
	if((!head)||(!head->right&&!head->left))
	return 0;
	int lh=height(head->left);
	int rh=height(head->right);
	return 1+((lh>rh)?lh:rh);
}
template<class T>
int Tree<T>::internalNodes(TreeNode<T>* head)
{
	if(!head)
	return 0;
	if(!head->right&&!head->left)
	return 0;
	//ok not a leaf
	return 1+internalNodes(head->left)+internalNodes(head->right);
}
template<class T>
int Tree<T>::leafNodes(TreeNode<T>* head)
{
	if(!head)
	return 0;
	if(!head->right&&!head->left)
	return 1;
	//ok not a leaf
	return leafNodes(head->left)+leafNodes(head->right);
}

template<class T>
int Tree<T>::totalNodes(TreeNode<T>* head)
{
	if(!head)
	return 0;
	if(!head->right&&!head->left)
	return 1;
	//ok not a leaf
	return 1+totalNodes(head->left)+totalNodes(head->right);

}
template <class T>
void Tree<T>::inorder(TreeNode<T>* head)
{
	if(head)
	{
	inorder(head->left);
	cout<<" "<<head->data;
	inorder(head->right);
	}
}
template <class T>
void Tree<T>::preorder(TreeNode<T>* head)
{
	if(head)
	{
	cout<<" "<<head->data;
	preorder(head->left);
	preorder(head->right);
	}
}
template <class T>
void Tree<T>::postorder(TreeNode<T>* head)
{
	if(head)
	{
	postorder(head->left);
	postorder(head->right);
	cout<<" "<<head->data;
	}
}
template <class T>
istream& operator >> (istream& i,Tree<T>& t)
{
	/*The tree was earlier read in Depth first order
	 * this has been changed to breadth first order. 
	 * To change this to depth first order,simple toggle 
	 * comments.
	 */   
	//this will help in reading the tree in depth order
	//TreeNode<T> * stack[100];
	queue<TreeNode<T>*> inputQ;
	
	//int top=-1;
	/*Any type that has to be used with tree must define it's
	 * own input,output and null check operators*/
	T lv,rv;
	bool complete=false;
	TreeNode<T> * curr=t.head,*lc,*rc;
	while(!complete)
	{
		cout<<"\n";
		cout<<"Enter left child of  "<<curr->data<<" : ";
		cin>>lv;
		cout<<"Enter right child of "<<curr->data<<" : ";
		cin>>rv;
		if((lv==0)&&(rv==0)) //at a leaf
		{
			//if(top==-1) //no  more to process
			if(inputQ.empty())
			{
				complete=true;
				break;
			}
			else //go to the next node
			{
				//curr=stack[top];
				//top--;
				curr=inputQ.front();
				inputQ.pop();
				continue;
			}
		}
		else if((lv==0)&&(rv!=0)) //only right child is there
		{
		rc=new TreeNode<T>(rv);
		//top++;
		//stack[top]=rc;
		inputQ.push(rc);
		curr->right=rc;
		}
		else if((lv!=0)&&(rv==0)) //only left child is there
		{
		lc=new TreeNode<T>(lv);
		//top++;
		//stack[top]=lc;
		inputQ.push(lc);
		curr->left=lc;
		}
		else //not a leaf, gotta update the l and r childs
		{
		lc=new TreeNode<T>(lv);
		//top++;
		//stack[top]=lc;
		rc=new TreeNode<T>(rv);
		//top++;
		//stack[top]=rc;
		curr->left=lc;
		curr->right=rc;
		inputQ.push(lc);
		inputQ.push(rc);
		}
		//curr=stack[top];
		//top--;
		curr=inputQ.front();
		inputQ.pop();
		}
return i;
}


