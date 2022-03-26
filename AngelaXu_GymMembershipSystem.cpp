/**************************************************
Purpose of code: This program creates, deletes, cancels, and books extends gym memberships.
Date: 2022-03-21
Created by: Angela Xu
**************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Membership{
public: 
	void printStatus();
	void reserve(int duration);
	void cancel();
	Membership(int id, int subscr, string name);

private:
	int id;
	int subscr;
	string name;

};

Membership::Membership(int id, int subscr, string name){
		this-> id = id;
		this-> subscr = subscr;
		this-> name = name;
	}

void Membership::printStatus(){
		cout << "Member " << id << " : " << name << ", subscription valid for " << subscr << " months. \n";
	}

//try to add reservations and return true on success
void Membership::reserve(int duration){
		subscr += duration;
}

//try to cancel reservations and return true on success
void Membership::cancel(){
		subscr = 0;
}

int findIndex(vector<int> list, int id){
	int index=-1;
	for(int i=0; i<list.size(); i++){
		if(list[i]==id){
			index = i;
			break;
		}
	}
	return index;
}

int main() {

	cout<< " ************************************************"<< endl;
	cout<< "Thank you for using Angela's Gym Membership System!" <<endl;
	cout<< endl;
	cout<< "The command \"create [id] [name]\" will try to create a new member with 0 months of subscription" <<endl;
	cout<< "The command \"delete [id]\" will try to remove the member with ID [id]" <<endl;
	cout<< "The command \"extend [id] [n]\" will try to extend the membership number of months of the member by [n]" <<endl;
	cout<< "The command \"cancel [id]\" will try to set the number of months of subscription to 0 of the member with the ID [id]" <<endl;
	cout<< " ************************************************"<< endl;
	
	string command = "";
	int id;
	string other = ""; 
	vector<Membership> bookings;
	vector<int> bookingID;

	while(command != "quit"){
		command = "";
		bool empty_flight = true;

		//print all existing memberships
		//bookings are not empty when someone does not have a id=0
		for(int k=0; k < bookings.size(); k++){
			if(bookingID[k] != 0){
				bookings[k].printStatus();
				empty_flight = false;
			}
		}	

		//if all ids are 0, output "No members in the system. "
		if(empty_flight){
			cout << "No members in the system. \n";
		}

		cout << "What would you like to do? : \n";		
		//get command
		cin >> command;
		if(command == "quit"){
			break;
		}

		if(command != "create" && command != "extend" && command != "delete" && command != "cancel"){
			cout << "Cannot perform this operation. Command invalid. \n";
			continue;
		}
		
		cin >> id;
		getline(cin, other);
		if(other.length() > 0){
			other = other.substr(1);
		}

		//create command
		if(command == "create"){
			//create a new Membership with 0 months of subscription
			if(other.length() == 0){
				cout<< "Cannot perform this operation. Please provide a name to create a membership. \n";
				continue;
			}
			bookings.push_back(Membership(id, 0, other)); 
			bookingID.push_back(id);
		}

		//extend command
		else if(command == "extend"){
			int index = findIndex(bookingID, id);
			if(index == -1){
					cout << "Cannot perform this operation. Invalid id. \n";
				}
			else{
				bookings[index].reserve(stoi(other));
			}
		}

		//delete command
			else if(command == "delete"){
				int index = findIndex(bookingID, id);
				if(index == -1){
					cout << "Cannot perform this operation. Invalid id. \n";
				}
				else{
					bookingID[index] = 0;
				}
			}

		//cancel command
			else if(command == "cancel"){
				int index = findIndex(bookingID, id);
				if(index == -1){
					cout << "Cannot perform this operation. Invalid id. \n";
				}
				else{
					bookings[index].cancel();
				}
			}
		
		cout << endl;
	}
	cout << "Thank you for using the gym membership booking system, enjoy your workout! \n";
}