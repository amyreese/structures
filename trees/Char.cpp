//sg
/* Following class demonstrates how user defined types can be used with 
 * the tree. This class defines a type Char which is a character wrapped 
 * inside bundle of operations that make it compatible with the tree.
 * 
 * Please note all the functions that are specified must be defined by 
 * such a type : 
 *  1. == 
 *  2. >>
 *  3. <<
 * 	4. !=
 * Also note that you almost never have to modify the tree source code.
 * Exception being the case when you want to implement new functions.  
 */
class Char
{
	char c;
	public:
	Char(char ct):c(ct)
	{}
	Char():c('0')
	{}
	friend bool operator ==(Char& c,int x);
	bool operator ==(Char& c);
	bool operator !=(Char& c);
	
	friend bool operator !=(Char& c,int x);
	friend istream& operator >>(istream& i,Char& C);
	friend ostream& operator <<(ostream& i,Char& C);
};
istream& operator >>(istream& i,Char& C)
{
	cin>>C.c;
	return i;
}
ostream& operator <<(ostream& o,Char& C)
{
	cout<<C.c;
	return o;
}
bool Char::operator ==(Char& C)
{
	return C.c==c;
}
bool Char::operator !=(Char& C)
{
	return !(C.c==c);
}
bool operator ==(Char& C,int x)
{
	int val=C.c-48;// 0 ASCII 48
	if(val==x)
	return true;
	else
	return false;
}
bool operator !=(Char& C,int x)
{
	return !(C==x);
}
