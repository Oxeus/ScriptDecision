//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 20, 2019
//Class: CS202 - Programming Systems
//Program: #3 - Script Decisions
//File: script.cpp
//Purpose: The purpose of this program is to load in data from a file specifically a script and
//allow to user to make decisions on which path the user can take to get different results.
//script.cpp has the purpose of implementing the functions pertaining to the script classes.
//*****************************************************************************************
#include "script.h"
#include <fstream>
#include <stdlib.h>



//Default Constructor
binary_tree::binary_tree()
{
	root = curr = nullptr;
}



//Copy Constructor, takes a const binary_tree object as an argument.
binary_tree::binary_tree(const binary_tree &to_copy)
{
	curr = root = nullptr;
	copy_tree(to_copy.root, root);
}



//Recursive function to coy a tree, called by copy constructor. Takes a const binary_node pointer
//and pass by reference binary_node pointer as arguments. Returns an int;
int binary_tree::copy_tree(const binary_node * root, binary_node *& copy)
{
	if(!root) 
	{
		copy = nullptr;
		return 1;
	}
	copy = new binary_node(*root);
	copy_tree(root->get_left_const(), copy->get_left());
	copy_tree(root->get_right_const(), copy->get_right());
	return 1;
}



//Destructor, calls recursive delete_list
binary_tree::~binary_tree()
{
	delete_tree(root);
}



//Recursive function to delete a tree, takes a binary_node pointer as an argument and returns an int.
int binary_tree::delete_tree(binary_node * root)
{
	if(!root) return 1;
	delete_tree(root->get_left());
	delete_tree(root->get_right());
	delete root;
	root = nullptr;
	return 1;
}



//= Overloader Operator, takes a const binary_tree object as an argument and returns the same.
binary_tree & binary_tree::operator = (const binary_tree &new_tree)
{
	if(this == &new_tree) return *this;
	delete_tree(this->root);
	if(!new_tree.root)
	{
		root = nullptr;
	}
	else
	{
		copy_tree(new_tree.root, this->root);
	}
	return *this;
}



//Recursive function used ti insert into the tree based on id value. Takes a pass by reference binary_node pointer,
//char pointer, int, and pass by reference binary_node as arguments. Returns an int.
int binary_tree::insert(binary_node *& root, char * new_dialogue, int new_id, binary_node *& ptr)
{
	if(!root)
	{
		root = new binary_node(new_dialogue, new_id);
		ptr = root;
		return 1;
	}
	if(new_id > root->get_id())
	{
		insert(root->get_right(), new_dialogue, new_id, ptr);
	}
	else
	{
		insert(root->get_left(), new_dialogue, new_id, ptr);
	}
	return 1;	
}



//Wrapper Function used to print all binary_nodes in the binary tree, returns an int
int binary_tree::display() const
{
	cout << "Script: " << endl;
	return display(root);
}



//Recursive Function to display binary tree, takes a const binary_node pointer and returns am int of the count
int binary_tree::display(const binary_node * root) const
{
	int count = 0;
	if(!root) return count;
	count += display(root->get_left_const());
	cout << *root << endl;
	count += display(root->get_right_const());
	return count;
}



//Script Class
//Default Constructor
script::script()
{
	choice = 0;
}



//Argument Constructor, takes a const char pointer as an argument.
script::script(const char * file_name)
{
	choice = 0;
	load_from_file(file_name);
}



//Function used to move the user to the next dialogue and decision. Returns an int.
int script::move()
{
	if(curr)
	{
		cout << *curr << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		cout << endl;
	}
	return 1;
}



//Function used to load script data from a file, takes a const char pointer as an argument. Returns a bool.
bool script::load_from_file(const char * file_name)
{
	char new_id[10], new_dialogue[1024], new_number[24], new_name[64], buffer[64];

	binary_node * ptr = nullptr;

	ifstream in;
	in.open(file_name);

	while(!in.eof() && in.getline(new_id, 64, '|'))
	{
		in.getline(new_dialogue, 1024, '|');
		insert(this->root, new_dialogue, atoi(new_id), ptr);

		in.getline(new_number, 24, '|');

		if(atoi(new_number) > 0)
		{
			for(int i = 0; i < atoi(new_number); ++i)
			{
				in.getline(new_name, 64, '|');
				*ptr += new_name;
			}
		}
		in.getline(buffer, 64);

	}
	curr = this->root;
	return true;
}



//Function used to determine if the user it at a leaf or not, changes curr pointer. Returns a bool.
bool script::is_finished()
{
	if(curr)
	{
		if(choice == 1)
		{
			curr = curr->get_left();
		}
		else if(choice == 2)
		{
			curr = curr->get_right();
		}
		return true;
	}
	else 
	{
		return false;
	}
}
