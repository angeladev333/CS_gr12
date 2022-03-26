/**************************************************
Purpose of code: This program reserves, cancels, and books different flights and displays a record of the total flights in the system.
Date: 2022-03-07
Created by: Angela Xu
**************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class FlightBooking {
public:
	FlightBooking(int id, int capacity, int reserved);

	//default FlightBooking constructor
	FlightBooking();
	void printStatus();
	bool reserveSeats(int number_of_seats);
	bool cancelReservations(int number_of_seats);

	//function that returns the id
	int getId() { return id; }
		
private:
	int id;
	int capacity;
	int reserved;
};

//save data to members according to limits
FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	this->id=id;
	this->capacity=capacity;
	if(reserved > capacity *1.05){
		reserved = capacity * 1.05;
	}
	this->reserved=reserved;
}

// print report here "Flight [id] : [reserved]/[capacity] ([percentage]%) seats taken"
void FlightBooking::printStatus()
{
	if(id == -1){
		return;
	}
		cout << "Flight " << id << " : " <<reserved << "/" <<capacity << "(" << round((reserved*10000.0)/capacity)/10000*100 << "%) seats reserved\n";
	
}

//try to add reservations and return true on success
bool FlightBooking::reserveSeats(int number_of_seats){
	if(number_of_seats + reserved <= capacity * 1.05){
		reserved += number_of_seats;
		return true;
	}
	return false;
}

//try to cancel reservations and return true on success
bool FlightBooking::cancelReservations(int number_of_seats){
	if(reserved - number_of_seats >= 0){
		reserved -= number_of_seats;
		return true;
	}
	return false;
}

int findID(vector <int> flightspace, int id){
	int returnid=-1;
	for(int i=0; i<flightspace.size(); i++){
		if(flightspace[i]==id){
			returnid = i;
			break;
		}
	}
	return returnid;
}

int main() {
	vector <FlightBooking> flights;
	vector <int> flightID;

	int reserved = 0,	capacity = 0, id=0;

	string command="";
	
	while(command!="quit"){
		
		bool donecommand=false;
		//print current flight status
		bool empty_flight = true;

		int k=0;
		for(auto i = flights.begin(); i!= flights.end(); i++){
			
				if(flightID[k] != -1){
					empty_flight = false;
					}
				k++;
			}

		//if all flights are -1, still counts as no flights
		if(empty_flight == true ){
				cout<< "No Flights in the System. \n";
			}
		
		if(empty_flight == false){
			int k=0;
			for(auto i = flights.begin(); i!= flights.end(); i++){
				
				if(flightID[k] !=-1){
					i->printStatus();
				}
				k++;
			}
		}
			
		cout << "What would you like to do?: " <<endl;
		getline(cin, command);
		//handle the command
		int length=command.length();

		//create new flight (id, cap needs to be provided)
		if(command.rfind("create",0)!=-1){
			string cmd = command.substr(7);
			int space_index = cmd.find(" ");

			if(space_index == -1){
				cout << "Cannot perform this operation. Please enter the capacity for the flight. \n";
				continue;
			}

			if(cmd.substr(space_index+1).length() == 0){
				cout << "Cannot perform this operation. No capacity specified. \n";
				continue;
			}
			
			id = stoi(cmd.substr(0, space_index));
			capacity = stoi(cmd.substr(space_index+1));
			int pos = findID(flightID, id);
			
			//if the flight ID already exists: 
			if(pos != -1){
				cout << "Cannot perform this operation. Flight " << id << " already exists. \n";
			}
			else{
				//create a flight that has the given id and capacity, and 0 reservations

				flights.push_back(FlightBooking(id, capacity, 0));
				flightID.push_back(id);
			}
			donecommand=true;
			
		}

		//delete flight (only id needs to be provided)
	// check if flightID doesn't exist		
		if(command.rfind("delete", 0)!=-1){
			id = stoi(command.substr(7));
			int pos = findID(flightID, id);
			if(pos == -1){
				cout << "Canont perform this operation. Flight "<< id << " does not exist. \n";
				donecommand=true;
			}
			else{
			flightID[pos]= -1;
				donecommand=true;
			}
		}

		//cancel reservations for current flight (id, number_of_seats)
		//check if flight ID exists
		if(command.rfind("cancel", 0)!= -1){
			string cmd = command.substr(7);
			int space_index = cmd.find(" ");

			if(space_index == -1){
				cout << "Cannot perform this operation. Please enter the amount of reservations you want to cancel. \n";
				continue;
			}

			if(cmd.substr(space_index+1).length() == 0){
				cout << "Cannot perform this operation. No number of reservations specified. \n";
				continue;
			}
			
			id = stoi(cmd.substr(0, space_index));
			int number_of_seats = stoi(cmd.substr(space_index+1));
			
			int pos = findID(flightID, id);
			
		if(pos == -1){
				cout << "Canont perform this operation. Flight "<< id << " does not exist. \n";
			donecommand=true;
			}	
			else {
						if(flights[pos].cancelReservations(number_of_seats) == true){
				donecommand=true;
			}
			else{
				cout << "Cannot perform this operation. You cannot cancel more flight reservations than already exists. \n";
				donecommand=true;
				}
			}	
		}		

		//add reservations for current flight (id, number_of_seats)
		//see if there is "add" at the start of the string
		if(command.rfind("add",0)!=-1){
			string cmd = command.substr(4);
			int space_index = cmd.find(" ");

			if(space_index == -1){
				cout << "Cannot perform this operation. Please enter the number of reservations you want to add for the flight. \n";
				continue;
			}

			if(cmd.substr(space_index+1).length() == 0){
				cout << "Cannot perform this operation. No number of reservations specified. \n";
				continue;
			}

			id = stoi(cmd.substr(0, space_index));
			int number_of_seats = stoi(cmd.substr(space_index+1));

			int pos = findID(flightID, id);

			if(pos == -1){
				cout << "Cannot perform this operation. Flight "<< id << " does not exist. \n";
				donecommand=true;
			}
			else{
				if(flights[pos].reserveSeats(number_of_seats)==true){
				donecommand=true;
			}
			else{ cout << "Cannot perform this operation. You cannot add more reservations than 105% of the flight capacity. \n" ;
				donecommand=true;
				}
			}
		}

		else if (command!="quit" && donecommand==false){
			cout << "Cannot perform this operation. Command invalid. \n";
		}
		
		cout<<endl;
	}
	flights.clear();
	flightID.clear();
	return 0;
}