//Schuyler Davis
//Assignment 1 for CS 3100
// Program creates a function that checkds to see if certain types of input of valid to see if something is an
//Expression <expr>= SI(C)T(<expr>)

#include <iostream>
#include <string>

using namespace std;

int main()  
{
	

  string testStr;

  cout << endl << endl << "The Expression Checker is running." ;
  cout << endl << endl ;

  while (cin >> testStr)
  {
    cout << testStr << endl;
    if   (isAnExpression(testStr))
         cout << "The string IS an expression." << endl ;
    else cout << "The string IS NOT an expression." << endl ;
  }
  cout << endl << endl << "The Expression Checker Thanks You!" ;
  cout << endl << endl ;


		
	return 0;
}
bool isAnExpression(string s)
/*

*/
{
	if (length(s)< 1)
		return false;
	else if(length(s)==1)
	{
		if (s=="S") && (s.substr(length(s)-1,1))
			return true;
		
	}
	else if (s.substr(0, 5)=="I(C)T(")
	{
		return isAnExpression(s.substr(5,length(s)-7))
	}
}