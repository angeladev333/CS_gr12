/**************************************************
Purpose of code: This program decodes a cryptic puzzle using the solution key and returns whether the crypt is true or not. 

(When given a crypt with 3 words, [word1, word2, word3], output whether the decoded sum of word1 and word2 equals word3. If the decoded number starts with 0, the crypt is invalid)

Example Input: 
ABCD ABC ACEF
6 (number of elements in the solution key)
A 1
B 2
C 3
D 4
E 5
F 7

Example Output:
Newword 1 : 1234
Newword 2 : 123
Newword 3 : 1357
The crypt is valid.

Date: 2022-03-19
Created by: Angela Xu
**************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

bool cryptsolution(vector<string> crypt, vector<vector<char>> solution){
	bool flag = false;
	bool invalidcrypt = false;
	string words[3];
	int newword[3];

	//get the crypt words
	for(int i=2; i >=0; i--){
		words[i] = crypt.back();
		crypt.pop_back();
	}
	
	//process the solution key using a hashmap
	map<char, int> sol;

	while(!solution.empty()){
		vector<char> cur = solution.back();
		solution.pop_back();
		int value = (int)cur.back() - '0';
		cur.pop_back();
		char key = cur.back();
		cur.pop_back();
		sol.insert({key, value});
	}

	//go through each word in the crypt
	for(int a=0; a < 3; a++){
		string curword = words[a];
		newword[a] = 0;
		int len = curword.length();

		//go through each letter in each word and add new value to the corresponding newword variable
		for(int i=0; i< len; i++){
			char var = curword[i];
				//if the first converted letter is 0, the crypt is invalid
				if(sol[var]==0 && i==0){
					invalidcrypt = true;
				}
			newword[a] += sol[var] * pow(10, len-1-i);
		}
		cout << "Newword " << a+1 << " : " <<newword[a] <<endl;
	}

	if(newword[0] + newword [1] == newword[2] && invalidcrypt==false){
		flag = true;
	}
	return flag;
}

int main() {
	vector<vector<char>> solution;
	vector<string> crypt;

	//get input for crypt vector
	cout << "Please enter the crypt words: " << endl;

	string var;
	int N = 3;
	while (N--)
	{
   cin >> var;
   crypt.push_back(var);
	}

	//get input for solution vector
	cout << "How many elements does the solution key have?: \n";
	int M;
	cin >> M;
	cout<< "Please enter the solution key (character, corresponding integer): \n";
	cout<< "Example: A 1 corresponds to A = 1 \n";
	
	char var1;
	char var2;
	while (M--)
	{
		cin >> var1;
  	cin >> var2;
		vector<char> vec;
		vec.push_back(var1);
		vec.push_back(var2);
  	solution.push_back(vec);
	}
	
	bool flag = cryptsolution(crypt, solution);

	if(flag == false){
		cout<< "The crypt is invalid.";
	}
	else{
		cout << "The crypt is valid. ";
		}
}