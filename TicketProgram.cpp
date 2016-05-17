// TicketApplication.cpp : Defines the entry point for the console application.
//
//============================================================================
// Name        : TicketProgram.cpp
// Author      : Michael Gabbard
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/// c++ wants us to declare functions in scope of each other
int main();
int mainMenu();
int viewChart();
int revokeSeat();
int stats();
int reserveSeatMenu();
int readFile();
int seatAddress();
int updateFile();


///global variable definitions
const int BUFFSIZE = 420;

int seatLetterIndex;
int seatNumberIndex;
int seatingArray[26][15] = {0};///initialize an example array all values are 0 until the file is read
//this should be the same size as the number of rows (int r) and the number of colums(int c)

char alpha[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int numerical[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
int r = 26;//number of rows 26 in our case
int c = 15;//number of columns 15 in our program
int seat = 0;
double ticketPrice=15.00;
int totalSold =0;


///a row address will be using the seatingArray[r][c] set equal to a 1 or 0 to indicate if a seat is ocupied or not.
// we will write the seatingArray to a file when it is changed and populate the seatingArray from the file when the program starts
//if a user enters row A column 10, we would actually have a seating address of seatingArray[0][11];
//        A|B|C|D|E|F|G|H|I|J|K |L......
//int r:  0|1|2|3|4|5|6|7|8|9|10|11.....

//int c:  0|1|2|3|4|5|6|7|8|9 |10|11.....
//        1|2|3|4|5|6|7|8|9|10|11|12.....
/// this is all because we don't have and seat A0 or B0 or C0... etc in our actual table
// With the exact address we can easily populate the array element to a 1 if its occupied and 0 if not soo... if (seatingArray[0][11] != 0){cout << "**";}




int mainMenu(){
	bool isOpen = true;
	while (isOpen){
		int option;
		cout << "\n Welcome to the ticketing program \n \n \n";
				cout<<"88888888888 d8b          888               888       88888888888                       888                       "<<"\n";
				cout<<"    888     Y8P          888               888           888                           888                       "<<"\n";
				cout<<"    888                  888               888           888                           888                       "<<"\n";
				cout<<"    888     888  .d8888b 888  888  .d88b.  888888        888  888d888 8888b.   .d8888b 888  888  .d88b.  888d888 "<<"\n";
				cout<<"    888     888 d88P-    888 .88P d8P  Y8b 888           888  888P-      -88b d88P-    888 .88P d8P  Y8b 888P-   "<<"\n";
				cout<<"    888     888 888      888888K  88888888 888  888888   888  888    .d888888 888      888888K  88888888 888     "<<"\n";
				cout<<"    888     888 Y88b.    888 *88b Y8b.     Y88b.         888  888    888  888 Y88b.    888 *88b Y8b.     888     "<<"\n";
				cout<<"    888     888  *Y8888P 888  888  *Y8888   *Y888        888  888    *Y888888  *Y8888P 888  888  *Y8888  888     "<<"\n \n \n";



		stats();///show some stats

		cout << "\n\n Select an option:\n\n";
		cout << "1. View the Seating chart \n" <<
			"2. Reserve a Seat \n" <<
			"3. Return or Revoke a reservation \n" <<
			"4. Exit the Program \n";
		cin >> option;
		if (option == 1){ viewChart(); }
		if (option == 2){ reserveSeatMenu(); }
		if (option == 3){ revokeSeat(); }
		if (option == 4){ isOpen = false; exit(0);break; }
		if (option != 1||option != 2||option != 3||option != 4){ cout << "not a valid option, try again \n";mainMenu();}
	}
	return 0;
}
int seatAddress(char seatLetter, int seatNumber){
	for (int i = 0; i < r; i++){
		if (alpha[i]==seatLetter){ seatLetterIndex = i; }
		 }
	for (int i = 0; i < c; i++){
		if (numerical[i]==seatNumber ){ seatNumberIndex = i; }
	}
	return 0;
}

int updateFile(){///this function writes whatever is stored in our 2d array to a text file in the proper format

	ofstream thefile;
	thefile.open("seatingchart.txt");
	int i = 0;
	int j = 0;
	while (i < r)//prints the rows of the seating table to the file
	{
		while (j < c){//prints the columns of the seating table to the file
			//this code keeps delimiter away at the end of a line
			if (j < c){ thefile << seatingArray[i][j] << ","; j++; }//this places spaces or delimiter between  integers
			if (j == (c - 1)){ thefile << seatingArray[i][j] << ""; j++; break; }///this removes spaces on the end of the last intiger
		}
		j = 0;///reset j for a new row
		if (i<=r && i!=(r-1)){  thefile << "\n";  }//restrict last line to remove the last newline
			i++;//Increment i
	}
	thefile.close();
	//next populate the array with the file populateArray();
readFile();
	return 0;
}

//read file
int readFile(){
	const int ROWS = r;
	const int COLS = c;
	const int BUFFSIZE = 80;
	char buff[BUFFSIZE]; // a buffer to temporarily park the data
	  ifstream infile("seatingchart.txt");
	  stringstream ss;
	  for( int row = 0; row < ROWS; ++row ) {
	    // read a full line of input into the buffer (newline is
	    //  automatically discarded)
	infile.getline( buff,  BUFFSIZE );
	    // copy the entire line into the stringstream
	    ss << buff;
	    for( int col = 0; col < COLS; ++col ) {
	      // Read from ss back into the buffer.  Here, ',' is
	      ss.getline( buff, 16, ',' );
	      // Next, use the stdlib atoi function to convert the string to int
	      seatingArray[row][col] = std::atoi( buff );
	    }
	    // This copies an empty string into ss
	    ss << "";
	    //  clear the 'eof' flag.
	    ss.clear();
	  }
	  // Now print the seatingArray to see the result or comment to keep it from showing
	  infile.close();
	return 0;
}

////view chart function
//// we make two main menu functions to fix a scoping issue

///function to reserve a seat
int reserveSeatMenu(){
	// Declare Local Variables
	int reserveOption;
	char row;
	int column;
	cout << "this is the reservation menu: \n"; \
		cout << "Select an option: \n"
		"1. Reserve a Seat \n"
		"2. Go to Main Menu \n";
	cin >> reserveOption;
	if (reserveOption == 1){
		cout << "Enter the row Letter: \n";
		cin >> row;
		char rowCase = toupper(row);
		cout << "Enter the column number: \n";
		cin >> column;
		seatAddress(rowCase, column);
		//cout << "seat address is seat letter:" << seatLetterIndex << " seat number: " << seatNumberIndex;
		///call the function to set the 2d seatingArray address of the seat
		if (seatingArray[seatLetterIndex][seatNumberIndex]==1){cout<<"\n Sorry that seat is already reserved. Try another seat \n"<<endl;}else{
				seatingArray[seatLetterIndex][seatNumberIndex]=1;cout<<endl;}

		//call the updatFile() function to save to the file automatically

		updateFile();reserveSeatMenu();
	}
	if (reserveOption == 2){ main(); }
	if (reserveOption != 1||reserveOption != 2){ cout << " not a valid option, try again \n";reserveSeatMenu();}

	return 0;
}


//function to display the seating chart
int viewChart(){
	int option;
	readFile();
	cout << "\n this is the seating chart: \n";
		///view chart code goes here
		int i = 0;
		int j = 0;
		while (i < r)//prints the rows of the seating table
		{
			while (j < c)
			{//prints the column of each row
				seatAddress(alpha[i], numerical[j]);//sets seatLetterIndex and seatNumberIndex
				///conditions to fill in the seating chart table
				if (seatingArray[seatLetterIndex][seatNumberIndex] == 1||seatingArray[seatLetterIndex][seatNumberIndex] == '1')
					{ cout << '|' << std::left << std::setw(1) << '*' << '*'; if (numerical[j] >= 10){ cout << '*'; }j++; }
				else{ cout << '|' << std::left << std::setw(1) << alpha[i] << numerical[j]; j++; }
			}
			i++; j = 0; cout << "|\n";
		}
	cout << "\n select '1' to return to the main menu \n";
	cin >> option;
	if (option != 1){ cout << "not a valid option, try again \n"; viewChart(); }
	if (option == 1){ main(); }
	return 0;
};

//function to remove a reservation or set a seat back to unreserved
int revokeSeat(){
	// Declare Local Variables
	int reserveOption;
	char row;
	int column;
	cout << "\n this is the revoke seat menu: \n you can revoke any reservation in the same you reserve a reservation \n";
		cout << "Select an option: \n"
		"1. Revoke a Seat \n"
		"2. Go to Main Menu \n";
	cin >> reserveOption;
	if (reserveOption == 1){
		cout << "Enter the row Letter: \n";
		cin >> row;
		char rowCase = toupper(row);
		cout << "Enter the column number: \n";
		cin >> column;
		seatAddress(rowCase, column);
		///cout << "seat address is seat letter:" << seatLetterIndex << " seat number: " << seatNumberIndex;
		///call the function to set the 2d seatingArray address of the seat
		if (seatingArray[seatLetterIndex][seatNumberIndex]==0){cout<<"\n Sorry that seat is already open, try canceling a different seat";}else{
		seatingArray[seatLetterIndex][seatNumberIndex]=0;}
		//call the updatFile() function to save to the file automatically
		updateFile();revokeSeat();
	}
	if (reserveOption == 2){ main(); }
	if (reserveOption != 1||reserveOption != 2){ cout << "not a valid option, try again \n";revokeSeat();}
	return 0;
};

////main function
int main(){

	///load the readFile(); function instead to populate the array for easy editing
	readFile();
	mainMenu();
	return 0;
}
///stats function displays basic info like how many seats are available/filled
int stats(){

///construct the total number sold
	totalSold=0;///start with zero when the function starts
	  for( int row = 0; row < r; ++row ) {
	    for( int col = 0; col < c; ++col ) {
	    			if(seatingArray[row][col]==1){totalSold++;}
	    	}
	  }
		double totalNumSeats= c*r;
		double  percent = (totalSold/totalNumSeats)*100.00;
		double available = totalNumSeats-totalSold;

	cout<<"Occupancy is at  [";
	int b=10;int count=0;int spaces;
			while(b<100){
				if(percent>b){cout<<"#";count++;}
				b=b+10;
			}
			spaces=10-count;
				int initial=0;
				while (initial<spaces){cout<<"-";initial++;}
				cout<<']'<<percent<< "%";
				cout<<"\n Seats Sold: "<<totalSold;
				cout<<"\n Tickets Available: "<<available;
				cout<<"\n Ticket cost: $"<<ticketPrice;
				cout<<"\n Total Sales: $"<<ticketPrice*totalSold;

return 0;
}
