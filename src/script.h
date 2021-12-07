//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 20, 2019
//Class: CS202 - Programming Systems
//Program: #3 - Script Decisions
//File: script.h
//Purpose: The purpose of this program is to load in data from a file specifically a script and
//allow to user to make decisions on which path the user can take to get different results.
//script.h has the purpose of defining the classes and their functions that were used in the
//program. Also defines the relationship between classes whether it is "is a" or "has a".
//*****************************************************************************************
#include <iostream> 
#include <cstring>



using namespace std;



//Character NODE
//Chracter: Has the purpose of defining a character and overloading operators for the class.
class character {
	public:
		character();
		character(const char * new_name);
		character(const character &to_copy);
		~character();

		friend ostream & operator << (ostream &out, const character &to_print);
		friend istream & operator >> (istream &in, character &to_change);

		character & operator = (const character &to_equal);

		char & operator [] (unsigned int index) const;

		bool operator == (const character &to_compare) const;
		bool operator != (const character &to_compare) const;
		bool operator > (const character &to_compare) const;
		bool operator >= (const character &to_compare) const;
		bool operator < (const character &to_compare) const;
		bool operator <= (const character &to_compare) const;

		char * get_name() const;

	protected:
		char * character_name;
};



//List_Node: Has the purpose of defining was a node for a list is, only allows getting a node reference.
class list_node : public character
{
	public:
		list_node();
		list_node(const char * new_name);

		list_node *& get_next();
		list_node * get_next_const() const;
	protected:
		list_node * next;
};



//BT NODE
//Character_List: Has the purpose of defining what the character list is, uses operation overloaders
//to perform operation on the class/data structure.
class character_list
{
	public:
		character_list();
		character_list(const character_list &to_copy);
		~character_list();

		friend ostream & operator << (ostream &out, const character_list &to_print);
		friend ostream & output(const list_node * head, ostream &out);
		friend istream & operator >> (istream &in, character_list &to_change);

		friend int merge(const list_node * source, list_node *& copy, list_node *& tail);
		friend character_list operator + (const character_list & list1, const character_list & list2);
		friend character_list operator + (const character_list & list, const char * new_character);
		friend character_list operator + (const char * new_character, const character_list & list);

		character_list & operator = (const character_list & list);	
		character_list & operator += (const character_list & list);
		character_list & operator += (const char * new_character);
	
		char *& operator [] (unsigned int index) const;

		bool operator == (const character_list & to_compare) const;
		bool operator != (const character_list & to_compare) const;
		bool operator > (const character_list & to_compare) const;
		bool operator >= (const character_list & to_compare) const;
		bool operator < (const character_list & to_compare) const;
		bool operator <= (const character_list & to_compare) const;

	protected:
		list_node * head;	
		list_node * tail;

		unsigned int number_of_characters;

		char * grab_index(const list_node * head, unsigned int index) const;	
		int copy_list(const list_node * head, list_node *& copy);
		bool compare_list(const list_node * head, const list_node * head_two) const;
		int delete_list(list_node *& head);
};



//Event: Has the purpose of defining what a event is. Handles mosty printing out of all data values.
class event : public character_list
{
	public:
		event();
		event(const char * new_dialogue);
		event(const event & to_copy);
		~event();

		friend ostream & operator << (ostream &out, const event &to_print);

	protected:
		char * dialogue;
};



//Binary Node: Has the purpose of defining was a node for a binary tree is, only allows getting a node references.
class binary_node : public event
{
	public:
		binary_node();
		binary_node(const char * new_dialogue, int new_id);

		binary_node *& get_left();
		binary_node *& get_right();

		binary_node * get_left_const() const;
		binary_node * get_right_const() const;

		int get_id() const;

	protected:
		binary_node * left, * right;
		int id;
};



//Script Classes
//Binary_Tree has the purpose of defining what a binary tree is, hands the operations on
//a binary tree and uses some overloaders.
class binary_tree
{
	public:
		binary_tree();
		binary_tree(const binary_tree &to_copy);
		~binary_tree();

		binary_tree & operator = (const binary_tree & new_tree);

		int display() const;

	protected:
		binary_node * root, *curr;

		int insert(binary_node *& root, char * new_dialogue, int new_id, binary_node *& ptr);
		int display(const binary_node * root) const;
		int copy_tree(const binary_node * root, binary_node *& copy);
		int delete_tree(binary_node * root);
};



//Script: Has the purpose of defining what a script is, has access to functions to control the binary
//tree. Has functions to determine of the user is at a leaf node, allow the user to move to the next
//dialogue/decision, and a function to load from a file.
class script : public binary_tree
{
	public:
		script();
		script(const char * file_name);

		int move();
		bool is_finished();

	protected:
		int choice;

		bool load_from_file(const char * file_name);
};
