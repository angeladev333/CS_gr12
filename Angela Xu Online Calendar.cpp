/*************************************************
Purpose of Code: Create an online calendar to calculate the days passed since January 1st, 1970 for a certain date
Date: 04/21/2022
By: Angela Xu
**************************************************/
#include <iostream>
using namespace std;

enum weekday{
SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

//overload << operator
ostream& operator<< (ostream &strm, weekday day){
	switch(day){
		case SUNDAY: strm << "Sunday";	break;
		case MONDAY: strm << "Monday";	break;
		case TUESDAY: strm << "Tuesday";	break;
		case WEDNESDAY: strm << "Wednesday";	break;
		case THURSDAY: strm << "Thursday";	break;
		case FRIDAY: strm << "Friday";	break;
		case SATURDAY: strm << "Saturday";	break;
		default: strm<< "Somewhere inside the depths of time..."; break;
	}
	return strm;
}

weekday operator+(weekday day, int days) 
{
  return static_cast<weekday>((static_cast<int>(day) + days) % 7);
}

class Exception{
private:
	string msg;

public: 
	Exception(const string& message):msg(message){}
	string getMessage(){
		return msg;
	}
};

class Calendar{
private:
int day, month, year;
string monthname;
int dayspassed=-1;
bool leapyear=false;

public:
//constructor
	Calendar(int day, int month, int year) : day(day), month(month), year(year){}

void printDate(){
	switch(month){
		case 1:		monthname = "January"; break;
		case 2: 	monthname = "February";  break;
		case 3: 	monthname = "March"; break;
		case 4: 	monthname = "April"; break;
		case 5: 	monthname = "May"; break;
		case 6: 	monthname = "June"; break;
		case 7: 	monthname = "July"; break;
		case 8: 	monthname = "August"; break;
		case 9: 	monthname = "September"; break;
		case 10: 	monthname = "October"; break;
		case 11: 	monthname = "November"; break;
		case 12: 	monthname = "December"; break;
		default: monthname = "Non-existent month"; break;
	}

try{
	cout<<day <<" " << monthname << " " <<year <<endl;
	
	if(year <1970){
			throw Exception("Error: Date entered is before January 1st, 1970.");
	}
		//calculate how many years passed
	for(int i=1970; i<year; i++){
		if((i%4 ==0 && i%100!=0) || (i%4==0 && i%400==0)){
			//this is a leap year
			dayspassed+=366;
		}
		else dayspassed+=365;
	}

	if((year%4 ==0 && year%100!=0) || (year%4==0 && year%400==0)){
			//this is a leap year
			leapyear = true;
		}

	int count = 2;
	//add dates according to month
	while(count <= month){
			//January, March, May, July, August, October, December
		if(count == 3 || count == 5 || count== 7 || count == 8 || count ==10 || count == 12){
			dayspassed += 31;
		}
		//February
		else if(count == 2){
			if(leapyear){
				dayspassed += 29;
			}
			else dayspassed +=28;		
		}
		//April, June, September, November
		else if(count == 4 || count == 6 || count ==9 ||count ==11){
			dayspassed += 30;
		}
		count++;
	}
	
	//add days according to days
	dayspassed += day;
	
	//find the weekday
	int wday = (dayspassed+4) % 7;
	for(weekday i=SUNDAY; i <7; i=i+1){
		if(wday == i){
			cout << i;
			break;
		}
	}
	cout<<endl;
	cout << dayspassed <<" days since January 1st, 1970." <<endl;
}
	catch(Exception& e){
		cout << e.getMessage();
	}
}
};
int main() {
	int day, month, year;
  cout << "Enter the day: "<<endl;
	cin >> day;
	cout << "Enter the month: "<<endl;
	cin>> month;
	cout << "Enter the year: "<<endl;
	cin >>year;

	Calendar obj = Calendar(day, month, year);

	obj.printDate();
}