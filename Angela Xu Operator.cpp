/*************************************************
Purpose of Code: This program uses simple overload operators to create a stack and output how many the user wants, while checking for exceptions
Date: 04/28/2022
By: Angela Xu
**************************************************/

#include <iostream>

using namespace std;

class Stack {
private:
    int *stackstore;
    int SP;
public:
    Stack(int size = 100)
    {
        stackstore = new int[size];
        SP = 0;
    }
    ~Stack()
    {
        delete [] stackstore;
    }
    void push(int value)
    {
        stackstore[SP++] = value;
    }
    int pop()
    {
        return stackstore[--SP];
		}
    int& operator[](int index);

		//a function to output the top
		int top(){
			return stackstore[SP-1];
		}
};

int& Stack::operator[] (int index)
{
    if(index > 0 || index <= -SP)
        throw range_error("out of stack");
    return stackstore[SP + index - 1];
}
Stack& operator<< (Stack &s, int v)
{
    s.push(v);
    return s;
}

Stack& operator>>(Stack &s, int &v)
{
    v = s.pop();
    return s;
}

//another way to get the top element in the stack
int stacktop(Stack &stk){
	return stk[0];
}

int main()
{
	Stack stk;
	int num;
	int num2;
	cout<<"How many numbers are in the stack?: ";
	cin>>num;

	cout<<"Please input your numbers"<<endl;
	for(int i=0; i<num ; i++){
		int temp;
		cin >> temp;
		stk << temp;
	}
	cout<< "How many numbers do you want to print out of the stack?: ";
	cin>> num2;

	for(int a=0; a < num2; a++){
		int print;
		try{
		print = stk[0-a];
		cout << print <<endl;
		}
		catch(range_error x){
			cout<< "Exception: stack is empty. " <<endl;
		}
	}
}