#include "wine.h"

#include <mysql.h>
#include "dbconnect.h"

using namespace std;

// Removes unnecessary space characters at the beginning and at the end of the string
string truncateSpaces(char *arg);

// Extracts an integer from a string
int getIntegerFromString(char *data);

// Extracts a double from a string
double getDoubleFromString(char *data);

// Get the specific wines using a sql command
bool queryWineSQL(char* command, vector<Wine> &wineList);

// Swaps two integers
void swapInt(int &x, int &y);

// Swaps two doubles
void swapDouble(double &x, double &y);

// Make sure a string has the same number of characters for better formatting
string makeEqualString(string s, int length);

// Print out the wine list
void printWineList(vector<Wine> wineList);

// About me
void printMeFirst();

int main(int argc, char* argv[])
{
	int choice;
	int i, x, y;
	double total, average;
	double priceX, priceY;
	char sql_command[2048];

	bool bQuit = false;
	vector<Wine> wineList;

	while(bQuit == false)
	{
		// Alternative - This clears the terminal more thoroughly and quickly		
		system("tput reset");

		cout << "Wine Menu (SQL version)" << endl;
		cout << "------------------------" << endl;
		cout << "1. Display Wine by rating" << endl;
		cout << "2. Display Wine by price" << endl;
		cout << "3. Display all Wine sorted by price" << endl;
		cout << "4. Display all Wine sorted by score" << endl;
		cout << "5. Display all Wine sorted by Wine type, ratings and price" << endl;
		cout << "6. About me" << endl;
		cout << "7. Exit the program" << endl;

		cout << endl;
		cout << "Your choice : "; 
		
		if(cin >> choice && choice >= 1 && choice <= 7)
		{
			cin.ignore();
			switch(choice)
			{
				// 1. 
				// Display all the wine has a score / rating (valid inputs is between 0 and 100) between x and y. You need to check the validity of user's input.  
				// For example, if user enters range between 90 and 100, also display the total number of wine between the selected range and average price for the selected wines. 
				// YOU MUST USE SQL to retrieve the data with the selection criteria, and then store the data in a vector (similar to the previous lab). 
				case 1 : 
				{
					do
					{
						cout << "Please enter rating x and y (0 - 100) : " << endl;

						if((cin >> x >> y) && (x > 0 && x <= 100 && y >= 0 && y <= 100))
						{
							cin.ignore();

							// We need to make sure x <= y
							if(x > y)
							{
								swapInt(x, y);
							}
						}
						else
						{
							x = -1;
							y = -1;

							if(!cin)
							{
								cin.clear();
								cin.ignore(1000, '\n');
							}
							cout << "You have entered incorrect numbers. Please try again.\n\n";
						}

					} while(x == -1 || y == -1);

					sprintf(sql_command, "Select * from wineInfo where rating >= %d and rating <= %d;", x, y);

					if(queryWineSQL(sql_command, wineList))
					{
						if(wineList.size())
						{
							cout << "Wines which have ratings between " << x << " and " << y << " : " << endl;
							printWineList(wineList);
							cout << endl;
						}
						else
						{
							cout << "There are no wines whose ratings are between " << x << " and " << y << endl;
						}
					}
					else
					{
						cout << endl;
						cout << "An error occured when querying SQL data. Possibly incorrect command." << endl;
					}
				}
				break;	

				// 2. 
				// Display all the wine has a price between x and y, and after print out all the wine in the selected range, also print out the total number of wine between the selected range and average price for the selected wines. You need to check the validity of user's input. 
				// For example, if user enters range between 20 and 50, only wines with the price between 20 and 50 will be printed.  
				// YOU MUST USE SQL to retrieve the data with the selection criteria, and then store the data in a vector (similar to the previous lab). 
				case 2 : 
				{
					do
					{
						cout << "Please enter price x and y : " << endl;

						if((cin >> priceX >> priceY) && (priceX >= 0 && priceY >= 0))
						{
							cin.ignore();

							// We need to make sure priceX <= priceY
							if(priceX > priceY)
							{
								swapDouble(priceX, priceY);
							}
						}
						else
						{
							priceX = -1;
							priceY = -1;

							if(!cin)
							{
								cin.clear();
								cin.ignore(1000, '\n');
							}
							cout << "You have entered incorrect price. Please try again.\n\n";
						}

					} while(priceX == -1 || priceY == -1);

					sprintf(sql_command, "Select * from wineInfo where price >= %f and price <= %f;", priceX, priceY);

					if(queryWineSQL(sql_command, wineList))
					{
						if(wineList.size())
						{
							cout << "Wines which have price between " << priceX << " and " << priceY << " : " << endl;
							printWineList(wineList);
							cout << endl;
						}
						else
						{
							cout << "There are no wines whose price is between " << priceX << " and " << priceY << endl;
						}
					}
					else
					{
						cout << endl;
						cout << "An error occured when querying SQL data. Possibly incorrect command." << endl;
					}				
				}
				break;	

				// 3. 
				// Display all the wines sorted by price, also display the total number of wine selected and average price for the selected wines.
				// YOU MUST USE SQL to retrieve the data with the selection criteria, and then store the data in a vector (similar to the previous lab). 
				case 3 : 
				{
					cout << "Display all wines sorted by price : " << endl;
					sprintf(sql_command, "Select * from wineInfo order by price;");

					if(queryWineSQL(sql_command, wineList))
					{
						if(wineList.size())
						{
							total = 0;
							for(i = 0; i < (int)wineList.size(); i++)
							{
								total += wineList[i].getPrice();
							}
							average = total / wineList.size();

							printWineList(wineList);
							cout << endl;

							cout << "Total number of wines selected : " << wineList.size() << endl;
							cout << "Average price for the selected wines : " << average << endl;

							cout << endl;
						}
						else
						{
							cout << "There are no wines in the database. Please check your database." << endl;
						}
					}
					else
					{
						cout << endl;
						cout << "An error occured when querying SQL data. Possibly incorrect command." << endl;
					}		
				}
				break;	

				// 4. 
				// Display all the wines sorted by score, also display the total number of wine selected and average price for the selected wines, also display the total number of wine selected and average price for the selected wines. 
				// YOU MUST USE SQL to retrieve the data with the selection criteria, and then store the data in a vector (similar to the previous lab). 
				case 4 : 
				{
					cout << "Display all wines sorted by score : " << endl;
					sprintf(sql_command, "Select * from wineInfo order by rating;");

					if(queryWineSQL(sql_command, wineList))
					{
						if(wineList.size())
						{
							total = 0;
							for(i = 0; i < (int)wineList.size(); i++)
							{
								total += wineList[i].getPrice();
							}
							average = total / wineList.size();

							printWineList(wineList);
							cout << endl;

							cout << "Total number of wines selected : " << wineList.size() << endl;
							cout << "Average price for the selected wines : " << average << endl;

							cout << endl;
						}
						else
						{
							cout << "There are no wines in the database. Please check your database." << endl;
						}
					}
					else
					{
						cout << endl;
						cout << "An error occured when querying SQL data. Possibly incorrect command." << endl;
					}		
				}					
				break;	
				
				// 5. 
				// Display all the wines that is sorted by wineType, ratings and price. Highest ratings wine should be listed 1st. 
				// YOU MUST USE SQL to retrieve the data with the selection criteria, and then store the data in a vector (similar to the previous lab).
				case 5 : 
				{
					cout << "Display all wines sorted by wineType, ratings and price : " << endl;
					sprintf(sql_command, "Select * from wineInfo order by wineType, rating DESC, price DESC;");

					if(queryWineSQL(sql_command, wineList))
					{
						if(wineList.size())
						{
							printWineList(wineList);
							cout << endl;
						}
						else
						{
							cout << "There are no wines in the database. Please check your database." << endl;
						}
					}
					else
					{
						cout << endl;
						cout << "An error occured when querying SQL data. Possibly incorrect command." << endl;
					}		
				}	
				break;	
				case 6 : 
					printMeFirst(); 
				break;	

				// Exit the program
				case 7 : bQuit = true; break;
			}
		}
		else
		{
			if(!cin)
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else cin.ignore();

			cout << "You have made an invalid choice." << endl;
		}

		if(bQuit == false)
		{
			cout << "Please press any key to continue. . ."; cin.get();
		}
	}

	cout << endl;
	cout << "Program ended. Thank you for using the program..." << endl;
	cout << "Press any key to continue. . ."; cin.get();

	return 0;
}

// About me
void printMeFirst()
{
    cout << "Program written by: " << "Hamza Sheikh" << endl;
    cout << "Course info: " << "Lab2" << endl << "CS-116: Thursday class" << endl << endl;
    time_t now = time(0);

    char* t= ctime(&now);
    cout << "Date: " << t << endl;
}

void printWineList(vector<Wine> wineList)
{
	int i;
	if(!wineList.size()) return;

	// Make sure the wine names are displayed equally with the same length
	int nameLengthMax = 41;

	// A line made of hyphens (-)
	cout << setfill('-') << setw(77) << '-' << setfill(' ') << endl;

	// Column header
	cout << "     ";
	cout << "Wine Name" << setw(40);
	cout << "Vintage" << setw(8);
	cout << "Rating" << setw(8);
	cout << "Price" << setw(7);
	cout << "Type" << endl;

	cout << setfill('-') << setw(77) << '-' << setfill(' ') << endl;
	 
	for(i = 0; i < wineList.size(); i++)
	{
		char num_idx[1000];

		// Index number
		sprintf(num_idx, "%.3d. ", i + 1);

		// Print out each wine element
		cout << num_idx << makeEqualString(wineList[i].getName(), nameLengthMax) << ' ' << setw(6) // field #1 - Wine Name
			<< wineList[i].getVintage() << setw(8) // field #2 - Vintage
			<< wineList[i].getRating() << setw(8) // field #3 - Rating
			<< wineList[i].getPrice() << setw(8) // field #4 - Price
			<< wineList[i].getType() // field #5 - Wine type
		<< endl;
      }
}

bool queryWineSQL(char* command, vector<Wine> &wineList)
{
	string name;
	int vintage, rating;
	double price;
	string type;
	
	// Clear the vector
	wineList.clear();

	MYSQL *conn; // The connection
	MYSQL_RES *res; // The results
	MYSQL_ROW row; // The results row (line by line)

	struct connection_details mysqlD;
	mysqlD.server = (char *)"localhost"; // Where the mysql database is
	mysqlD.user = (char *)"root"; // The root user of mysql	
	mysqlD.password = (char *)"password"; // The password of the root user in mysql
	mysqlD.database = (char *)"mysql"; // The databse to pick
 
	// Connect to the mysql database
	conn = mysql_connection_setup(mysqlD);

	res = mysql_perform_query(conn, (char *)("use wine"));

	// Assign the results return to the MYSQL_RES pointer
	if(res = mysql_perform_query(conn, command))
	{
		char buffer[2500];
		sprintf(buffer, "%s", mysql_error(conn));

		if(strlen(buffer) > 0)
		{
			printf("MySQL query error : %s\n", buffer);
			return false;
		}
	}

	// Extract Wine sql items one by one
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		// We sometimes need to truncate spaces, because from obversation there are rows with additional space characters
		name = truncateSpaces(row[0]);
		vintage = getIntegerFromString(row[1]);
		rating = getIntegerFromString(row[2]);
		price = getDoubleFromString(row[3]);
		type = truncateSpaces(row[4]);

		wineList.push_back(Wine(name, vintage, rating, price, type));
      }

	// Clean up the database result set
	mysql_free_result(res);
	// Clean up the database link
	mysql_close(conn);

	return true;
}

// Make sure a string has the same number of characters for better formatting
string makeEqualString(string s, int length)
{
	while(s.length() < length) s += ' ';
	return s;
}


// Swaps two integers
void swapInt(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

// Swaps two doubles
void swapDouble(double &x, double &y)
{
	int temp = x;
	x = y;
	y = temp;
}

// This removes any trailing space characters at the beginning and at the end of the string
string truncateSpaces(char *arg)
{
	int i;
	string str = arg;

	// Removes spaces from the beginning (though it might not be needed)
	for(i = 0; i < str.size(); i++)
	{
		if(str[i] == ' ') 
		{
			str.erase(str.begin() + i); i--;
		}
		else break;
	}

	// Removes spaces from the end of the string 
	for(i = str.size() - 1; i >= 0; i--)
	{
		if(str[i] != ' ') break; 
	}
	str.erase(i + 1);

	return str;
}

// Use stringstream to extract the integer from a string
int getIntegerFromString(char *data)
{
	int result;
	stringstream ss;
	ss << data;
	ss >> result;
	return result;
}

// Use stringstream to extract the double from a string
double getDoubleFromString(char *data)
{
	double result;
	stringstream ss;
	ss << data;
	ss >> result;
	return result;
}