//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 20, 2019
//Class: CS202 - Programming Systems
//Program: #3 - Script Decisions
//File: character.cpp
//Purpose: The purpose of this program is to load in data from a file specifically a script and
//allow to user to make decisions on which path the user can take to get different results.
//character.cpp has the purpose of implementing the functions pertaining to the character classes.
//*****************************************************************************************
#include "script.h"



//Character Class
//Default Constructor, initializes character_name
character::character()
{
	character_name = nullptr;
}



//Argument Constructor, takes a const char pointer as input.
character::character(const char * new_name)
{
	if(new_name)
	{
		character_name = new char[strlen(new_name) + 1];
		strcpy(character_name, new_name);
	}
	else
	{
		character_name = nullptr;
	}
}



//Copy Constructor, takes a const pass by reference character as input.
character::character(const character &to_copy)
{
	if(to_copy.character_name)
	{
		character_name = new char[strlen(to_copy.character_name) + 1];
		strcpy(character_name, to_copy.character_name);
	}
	else
	{
		character_name = nullptr;
	}
}



//Destructor.
character::~character()
{
	if(character_name)
	{
		delete [] character_name;
	}
}



//<< Overloader, takes an ostream object and a const character, returns an ostream object.
ostream & operator << (ostream &out, const character &to_print)
{
	if(to_print.character_name)
	{
		out << to_print.character_name;
	}
	return out;
}



//>> Overloader, takes an istream object and a character object, returns an istream object;
istream	& operator >> (istream &in, character &to_change)
{
	if(to_change.character_name)
	{
		delete [] to_change.character_name;
	}
	char name[64];
	cin.getline(name, sizeof(name));
	to_change.character_name = new char[strlen(name) + 1];
	strcpy(to_change.character_name, name);
	return in;
}



//[] Overloader, takes an unsigned it value as an argument, returns a char value. Doesn't change data so const
char & character::operator [] (unsigned int index) const
{
	static char grab = 0;
	unsigned int len = strlen(character_name);
	if(index >= 0 && (index < (len - 1)))
	{
		grab = *(character_name + index);
	}
	return grab;
}



//= Overloader, takes a const character reference as input, returns a derefenced this object. Used to assign one
//object to another.
character & character::operator = (const character &to_equal)
{
	if(this == &to_equal)
	{
		return *this;
	}
	if(character_name)
	{
		delete [] character_name;
	}
	character_name = new char[strlen(to_equal.character_name) + 1];
	strcpy(character_name, to_equal.character_name);
	return *this;
}



//== Overloader, takes a const character as input, and returns a bool value. Compares two characters. Constant.
bool character::operator == (const character &to_compare) const
{
	bool same;
	if(character_name == nullptr || to_compare.character_name == nullptr)
	{
		if(character_name == nullptr && to_compare.character_name == nullptr)
		{
			same = true;
		}
		else
		{
			same = false;
		}
	}
	else
	{
		if(strcmp(character_name, to_compare.character_name) == 0)
		{
			same = true;
		}
		else
		{
			same = false;
		}
	}
	return same;
}



//!= Overloader, takes a const character as an inout, and returns a bool value. Compares two characters. Constant.
bool character::operator != (const character &to_compare) const
{
	bool not_same;
	if(character_name == nullptr || to_compare.character_name == nullptr)
	{
		if(character_name == nullptr && to_compare.character_name == nullptr)
		{
			not_same = false;
		}
		else
		{
			not_same = true;
		}
	}
	else
	{
		if(strcmp(character_name, to_compare.character_name) == 0)
		{
			not_same = false;
		}
		else
		{
			not_same = true;
		}
	}
	return not_same;
}



//> Overloader, takes a const character as input, and returns a bool value. Compares two characters. Constant.
bool character::operator > (const character &to_compare) const
{
	bool greater;
	if(strcmp(character_name, to_compare.character_name) > 0)
	{
		greater = true;
	}
	else
	{
		greater = false;
	}
	return greater;
}



//>= Overloader, takes a const character as input, and returns a bool value. Compares two characters. Constant.
bool character::operator >= (const character &to_compare) const
{
	bool greater_equal = false;
	if(strcmp(character_name, to_compare.character_name) >= 0)
	{
		greater_equal = true;
	}
	return greater_equal;
}



//< Overloader, takes a const character as input, and returns a bool value. Compares two characters. Constant.
bool character::operator < (const character &to_compare) const
{
	bool less = false;
	if(strcmp(character_name, to_compare.character_name) < 0)
	{
		less = true;
	}
	return less;
}



//<= Overloader, takes a const character as input, and returns a bool value. Compares two characters. Constant.
bool character::operator <= (const character &to_compare) const
{
	bool less_equal = false;
	if(strcmp(character_name, to_compare.character_name) <= 0)
	{
		less_equal = true;
	}
	return less_equal;
}



//Function used to grab a name used for retrieval in a derived class.
char * character::get_name() const
{
	return character_name;
}



//List_Node
//Default Constructor, initializes next to nullptr
list_node::list_node() : next(nullptr) {}



//Argument Constructor, passes const char to character class.
list_node::list_node(const char * new_name) : character(new_name), next(nullptr) {}



//Function used to retrieve reference to next pointer, returns this.
list_node *& list_node::get_next()
{
	return next;
}



//Function used to rerieve pointer to the next pointer, returns this. Constant to prevent changes to structure.
list_node * list_node::get_next_const() const
{
	return next;
}
