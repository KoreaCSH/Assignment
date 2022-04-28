#include "texteditor.h"
#include <iostream>
#include <string.h>

using namespace std;

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 데이터베이스 과제 
  *
  */


// Default constructor 
TextEditor::TextEditor()
{
	pos = buffer.Begin();
	currLine = 0;
}

TextEditor::~TextEditor()
{
	pos = buffer.Begin();
	while(buffer.DeleteNode(pos))
	{
		pos++;
	}
}

// Insert a new line after the current position
void TextEditor::Insert(const char* s)
{
	pos = buffer.InsertNext(pos, s);
	currLine++;
}

// Delete the current line
void TextEditor::Delete()
{	
	if ( buffer.Size() == 0 ) 
	{
		std::cout << "Buffer is empty" << std::endl;
	}
	else if ( buffer.Size() == currLine ) 
	{
		buffer.DeleteNode(pos);
		--pos;
		--currLine;
	}
	else
	{
		buffer.DeleteNode(pos);
		++pos;
	}
}

// Move one line up
void TextEditor::MoveUp()
{
	if ( currLine == 0 )
	{
		std::cout << "Buffer is empty" << std::endl;
	}
	else if ( currLine == 1 )
	{
		std::cout << "Beginning of the buffer" << std::endl;
	}
	else
	{
		--pos;
		currLine -= 1;
	}
}

// Move one line down
void TextEditor::MoveDown()
{
	if ( currLine == buffer.Size() )
	{
		std::cout << "End of the buffer" << std::endl;
	}
	else
	{
		++pos;
		currLine += 1;
	}
}

//
// Interactive mode
//
void TextEditor::Run()
{
	std::string inp;
		
	while(1)
	{
		std::cout << "> ";
		getline(cin, inp);
						
		// ToDo	- implement other functions
		if(inp == "u") MoveUp();
		else if(inp == "d") MoveDown();
		else if(inp == "p") Print();
		else if(inp == "pa") PrintAll();
		else if(inp == "r") Delete();
		else if(inp == "i")
		{
			string s;
			const char* ps;
			cout << "(Insert) > ";
			getline(cin, s);
			ps = s.c_str();
				
			Insert(ps);
		}
		else if(inp == "x") exit(0);
		else
		{
			cout << "No such command. Available commands are u(up), d(down), p(print), pa(print all), r (delete), i(insert), and x(exit)" << endl;
		}		
	}
}


// ----------------------

// Print the current line with the line number
void TextEditor::Print()
{
	if(buffer.Size() < 1) {
		std::cout << "Buffer is empty" << std::endl;
	}
	else {
		std::cout << "Current(L" << currLine << ") : " << *pos << std::endl;
	}
}

// Print all with the line number
void TextEditor::PrintAll()
{
	int i=1;
	for(BufferType::Iterator it=buffer.Begin(); it != buffer.End(); it++)
	{
		cout << "L" << i++ << " :";
		if(i == (currLine+1)) cout << "*";
		else cout << " ";
		cout << *it << endl;		
	}
}
