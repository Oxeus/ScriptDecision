//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 20, 2019
//Class: CS202 - Programming Systems
//Program: #3 - Script Decisions
//File: event.cpp
//Purpose: The purpose of this program is to load in data from a file specifically a script and
//allow to user to make decisions on which path the user can take to get different results.
//event.cpp has the purpose of implementing the functions pertaining to the event classes.
//*****************************************************************************************
#include "script.h"



//Character List Class
//Default Constructor
character_list::character_list()
{
	head = tail = nullptr;
	number_of_characters = 0;
}



//Copy Constructor, takes a const character_list as an argument.
character_list::character_list(const character_list &to_copy)
{
	head = tail = nullptr;
	copy_list(to_copy.head, head);
	number_of_characters = to_copy.number_of_characters;
}



//Function used to recursively copy the data structure. Takes a const list_node pointer and a pass by reference list_node pointer as arguments.
int character_list::copy_list(const list_node * head, list_node *& copy)
{
	int result = 1;
	if(!head)
	{
		copy = nullptr;
		return result;
	}
	copy = new list_node(*head);
	result = copy_list(head->get_next_const(), copy->get_next());
	if(copy->get_next() == nullptr)
	{
		tail = copy;
	}
	return result;
}



//Destructor, calls recursive delete list function.
character_list::~character_list()
{
	if(delete_list(this->head) == 1)
	{
		head = tail = nullptr;
	}
	number_of_characters = 0;
}



//Recursive Function to delete the character list. Takes a pass by reference pointer as an input and returns a int
int character_list::delete_list(list_node *& head)
{
	int result = 1;
	if(!head) return result;
	result = delete_list(head->get_next());
	if(head)
	{
		delete head;
		head = nullptr;
	}
	return result;
}



//Recursive Function to print character list, takes a list_node pointer and ostream object as inputs and returns an ostream object.
ostream & output(const list_node * head, ostream &out)
{
	if(!head) return out;
	out << "Character Name: " << *head << endl;
	return output(head->get_next_const(), out);
}



//<< Overload Operator, takes an ostream object and const character_list object as arguments and returns an ostream bject.
ostream & operator << (ostream &out, const character_list &to_print)
{
	out << "Character List: (" << to_print.number_of_characters << ")" << endl;
	return output(to_print.head, out);
}



//>> Overload Operator, takes an istream object and character_list object as arguments and return an istream object
istream & operator >> (istream &in, character_list &to_change)
{
	char name[64];
	cin.getline(name, sizeof(name));
	if(!to_change.head)
	{
		to_change.head = to_change.tail = new list_node(name);
	}
	else
	{
		to_change.tail->get_next() = new list_node(name);
		to_change.tail = to_change.tail->get_next();
	}
	++to_change.number_of_characters;
	return in;
}



// = Overload Operator, takesa const character_list object as an input and returns the same.
character_list & character_list::operator = (const character_list & list)
{
	if(this == &list) return *this;
	delete_list(this->head);
	if(!list.head)
	{
		head = tail = nullptr;
	}
	else
	{
		copy_list(list.head, this->head);	
	}
	number_of_characters = list.number_of_characters;
	return *this;
}



//Recursive function used merge two lists together by appending the second list to first list. Takes a const list_node pointer, 
//pass by reference list_node pointer, and pass by reference list_node tail as arguments. Returns a bool.
int merge(const list_node * source, list_node *& copy, list_node *& tail)
{
	int result = 1;
	if(!source)
	{
		copy = nullptr;
		return result;
	}
	copy = new list_node(*source);
	result = merge(source->get_next_const(), copy->get_next(), tail);
	if(copy->get_next() == nullptr)
	{
		tail = copy;
	}
	return result;
}



//+ Operator Overloader, appends one list to another, takes two const character_list objects as arguments, returns a new character_list
character_list operator + (const character_list & list1, const character_list & list2)
{
	character_list temp(list1);
	if(!temp.head) temp = list2;
	else
	{
		merge(list2.head, temp.tail->get_next(), temp.tail);
	}
	temp.number_of_characters += list2.number_of_characters;
	return temp;	
}



//+ Operator Overloader, adds a new character to the tail, takes a const character_list object and const char pointer as arguments, returns a new
//character_list
character_list operator + (const character_list & list, const char * new_character)
{
	character_list temp(list);
	if(!temp.head)
	{
		temp.head = temp.tail = new list_node(new_character);
	}
	else
	{
		temp.tail->get_next() = new list_node(new_character);
		temp.tail = temp.tail->get_next();
	}
	++temp.number_of_characters;
	return temp;
}



//+ Operator Overloader, adds a new character to the tail, takes a const character_list object and const char pointer as arguments, returns a new
//character_list
character_list operator + (const char * new_character, const character_list & list)
{
	character_list temp(list);
	if(!temp.head)
	{
		temp.head = temp.tail = new list_node(new_character);
	}
	else
	{
		temp.tail->get_next() = new list_node(new_character);
		temp.tail = temp.tail->get_next();
	}
	++temp.number_of_characters;
	return temp;
}



//+= Operator Overloader, appends one list to another, takes a const character_list objects as an argument, returns a character_list object
character_list & character_list::operator += (const character_list & list)
{
	if(!head) *this = list;
	else
	{
		list_node * temp = tail;
		list_node * source = list.head;
		copy_list(source, temp->get_next());
	}
	number_of_characters += list.number_of_characters;
	return *this;
}



//+= Operator Overloader, adds a new character to the tail, takes a const char pointer as an argument, returns a character_list object
character_list & character_list::operator += (const char * new_character)
{
	if(!head)
	{
		head = tail = new list_node(new_character);
	}
	else
	{
		tail->get_next() = new list_node(new_character);
		tail = tail->get_next();
	}
	++number_of_characters;
	return *this;
}



//Recursive Function used to retrieve a certain name, based on an index. Takes a const list_node pointer and unsigned int as arguments,
//and returns a char value.
char * character_list::grab_index(const list_node * head, unsigned int index) const
{
	if(!head) return nullptr;
	if(index == 0)
	{
		return head->get_name();
	}
	return grab_index(head->get_next_const(), --index);
}



//[] Operator Overloader, retrieves the character name at a certain index passed in, calls grab_index to retrieve char value. Takes 
//a unisgned int and returns a char pointer.
char *& character_list::operator [] (unsigned int index) const
{
	static char * grab = nullptr;
	if(head)
	{
		if(index >= 0 && index <= (number_of_characters - 1))
		{
			grab = grab_index(this->head, index);
		}
		else
		{
			grab = nullptr;
		}
	}
	else
	{
		grab = nullptr;
	}
	return grab;
}



//== Operator Overloader, used to compare two lists, takes a const character_list object as an argument and returns a bool.
bool character_list::operator == (const character_list & to_compare) const
{
	return compare_list(head, to_compare.head);
}



//=! Operator Overloader, used to compare two lists, takes a const character_list object as an argument and returns a bool.
bool character_list::operator != (const character_list & to_compare) const
{
	return !(compare_list(head, to_compare.head));
}




//Recursive Function called by operator overloaders to compare two lists, takes two const list_node pointers and returns a bool value
bool character_list::compare_list(const list_node * head, const list_node * head_two) const
{
	if((head == nullptr) || (head_two == nullptr))
	{
		if(head == nullptr && head_two == nullptr) return true;
		else return false;
	}
	if (*head != *head_two)
	{
		return false;
	}
	return compare_list(head->get_next_const(), head_two->get_next_const());
}



//> Operator Overloader, used to compare two lists, takes a const character_list object as an argument and returns a bool.
bool character_list::operator > (const character_list & to_compare) const
{
	if(number_of_characters > to_compare.number_of_characters)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//>= Operator Overloader, used to compare two lists, takes a const character_list object as an argument and returns a bool.
bool character_list::operator >= (const character_list & to_compare) const
{	
	if(number_of_characters >= to_compare.number_of_characters)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//< Operator Overloader, used to compare two lists, takes a const character_list object as an argument and returns a bool.
bool character_list::operator < (const character_list & to_compare) const
{
	if(number_of_characters < to_compare.number_of_characters)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//<= Operator Overloader, used to compare two lists, takes a const character_list object as an argument and returns a bool.
bool character_list::operator <= (const character_list & to_compare) const
{
	if(number_of_characters <= to_compare.number_of_characters)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Event Class
//Default Constructor, initializes dialogue
event::event()
{
	dialogue = nullptr;
}



//Argument Constructor, takes a const char ponter as an argument.
event::event(const char * new_dialogue)
{
	dialogue = nullptr;
	dialogue = new char[strlen(new_dialogue) + 1];
	strcpy(dialogue, new_dialogue);
}



//Copy Constructor, takes a const event object as an argument and passes it to its base class
event::event(const event &to_copy) : character_list(to_copy)
{
	if(to_copy.dialogue)
	{
		dialogue = new char[strlen(to_copy.dialogue) + 1];
		strcpy(dialogue, to_copy.dialogue);
	}
	else
	{
		dialogue = nullptr;
	}
}



//Destructor
event::~event()
{
	if(dialogue)
	{
		delete [] dialogue;
	}
}



//<< Operator Overloader, takes a ostream objectm and a const event as arguments and returns an ostream object.
ostream & operator << (ostream &out, const event &to_print)
{
	if(to_print.dialogue)
	{
		out << "Dialogue: " << to_print.dialogue << endl << endl;
	}
	out << (character_list&) to_print;
	return out;
}



//Binary Node Class
//Default Constrcutor, sents left, right pointers to null and sets id to 0
binary_node::binary_node()
{
	left = right = nullptr;
	id = 0;
}



//Argument Constructor, tkes a const char pointer and int value and passes the const char pointer to parent event class.
binary_node::binary_node(const char * new_dialogue, int new_id) : event(new_dialogue)
{
	left = right = nullptr;
	id = new_id;
}



//Functions used to return pass by refernece pointer of left node.
binary_node *& binary_node::get_left()
{
	return left;
}



//Functions used to return pass by refernece pointer of right node.
binary_node *& binary_node::get_right()
{
	return right;
}



//Functions used to return pointer of left node.
binary_node * binary_node::get_left_const() const
{
	return left;
}



//Functions used to return pointer of right node.
binary_node * binary_node::get_right_const() const
{
	return right;	
}



//Function used to get the id of a node, returns an int id
int binary_node::get_id() const
{
	return id;
}
