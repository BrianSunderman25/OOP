#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*classes for JSON*/
struct Value 
{
	virtual ~Value() = default;
	virtual int weight() const = 0;
};

struct Null : Value
{
	int weight() const { return 1; }

};

struct Bool : Value
{
	Bool(bool B) : Val(B) {}
	bool Val;
};

struct String : Value, string
{
	using string::string;

};

struct Array : Value, vector<Value*>
{
	using vector<Value*>::vector;
	~Array() {
		for (Value* v : *this)
			delete v;
	}
};

//struct values
string JSON;

int parse();



int main()
{
	
	//put json from web page into a string
	ifstream myfile("JSON_from_reddit.txt");
	if (myfile.is_open())
	{
		//put file contents into a string
		while (myfile)
		{
			getline(myfile, JSON);
		}
	}

	//close file
	else cout << "Unable to open file";
	myfile.close();

	//start parsing
	cout << "The weight of the JSON file is " << parse();

	system("Pause");
    return 0;
}

/*Functions for parsing*/

int parse()
{
	char * F;
	char * L;
	int weight = 0;

	//set f and l to the first and last elements of the string
	F = &JSON[0];
	L = &JSON[JSON.size() - 1];

	while (F != L)
	{
		//when f is blank, move on to the next element
		if (*F == ' ')
		{
			F++;
		}

		//when f equals a true, move 4 bits and add to the weight
		else if (*F == 't')
		{
			F = F + 4;
			weight++;

		}

		//when f == false, move 5 and add to weight
		else if (*F == 'f')
		{
			F = F + 5;
			weight++;
		}

		//for when f == null
		else if (*F == 'n')
		{
			F = F + 4;
			weight++;
		}

		//signals the start of the string
		else if (*F == '"')
		{
			F++;

			//anything that isnt the end of the string
			while (*F != '"')
			{

				//character used for unseen characters
				if (*F == '\' ')
				{
					F = F + 2;
				}
				F++;

			}
			F++;
			weight++;

		}

		//array character
		else if (*F == '[')
		{
			weight++;
			F++;
		}

	
		else if (*F == '{')
		{

			weight++;
			F++;
		}

		//used for any numbers
		else if (isdigit(*F))
		{
			while (isdigit(*F))
			{
				F++;
			}
			weight++;
		}
		else
			F++;
	}

	return weight;

}
