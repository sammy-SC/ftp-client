#include <menu.h>
#include <ncurses.h>
#include <deque>
#include <algorithm>
#include <string>
#include <string.h>
#include <sstream>

#include "ui_window.h"
#include "local_panel.h"
#include "remote_panel.h"
#include "ui_menu.h"
#include "ui_form.h"
#include "functions.h"
#include "english.lang"

#define ENTER 10
#define ESCAPE 27
#define TAB 9
#define F5 269
#define F6 270

using namespace std;




bool new_folder_view( const char * & result )
{
	CMenu new_folder( tretie, 1 ); 

	UI_window test( 10, 50, COLS / 2 - 25, LINES / 2 - 10 );
	test.set_intestines ( new UI_form );
	test.set_content ( &new_folder, 0, 0 );
	test.set_title( "New folder" );
	int c;
	while ( (c = getch()) != ESCAPE )
	{ 
		if ( c == ENTER )
		{
			result = test.get_value(0);
			break;
		}
		test.key_down( c );
	}
	return true;
}

void alert( const char * message )
{
	UI_window tmp( 8, 50, COLS / 2 - 25, 2 );
	tmp.set_title( message );
	mvprintw(6, COLS / 2 - 20, "Press escape to continue");
	int c;
	while(  (c = getch()) != ESCAPE ){
		printf("%d\n", c );

	}
}

void dual_panel_view(const char * addr, const char * user, const char * pass, const char * & response)
{
	Local_panel local(LINES - 5, COLS / 2 - 1, 1, 1,"Local"); 
	Remote_panel remote( LINES - 5, COLS / 2, ( COLS / 2 ) - 1 + 1, 1, "Remote", addr );
	
	if ( !remote.m_connected )
	{
		response = "Could not reach server";
		return;
	}

	remote.login( user, pass );

	if ( !remote.m_connected )
	{
		response = "Bad login / password";
		return;
	}


	mvprintw(LINES - 3, 5, "Press Escape to disconnect    |    <F5> to copy files    |    <F6> to create a new folder    |    <Delete> to remove a file"); 
	refresh();

	local.list_directory();
	remote.list_directory();

	int c;
	bool left = true;

	while ( (c = getch() ) != ESCAPE ) 
	{
		if ( c == TAB ) 
			left = !left; 
		else if ( c == F6 )
		{
			const char * new_folder;
			new_folder_view( new_folder );
			if ( left ) 
			{
				local.new_folder( new_folder );
				remote.set_borders();
			}
			else
			{
				remote.new_folder( new_folder );
				local.set_borders();
			}
		}
		else if ( left )
		{
			if ( local.key_down( c ) )
				remote.m_connection.upload( local.upload() );
		}
		else
		{
			// change occured, refresh is required
			if  ( remote.key_down( c ) )
				local.list_directory();
		}
	}
	response = NULL;
	mvprintw(LINES - 3, 5, "                                                                                                                                     "); 
	refresh();
}

int main()
{ 
	//----------------- init ncurses ----------------------
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	//-----------------------------------------------------

	refresh();

	//-----------------Define menus------------------------
	CMenu main_menu( prve, 2 ); 
	CMenu new_connection( druhe, 3 ); 
	//-----------------------------------------------------

	UI_window test( 20, 50, COLS / 2 - 25, LINES / 2 - 10 );

	test.set_intestines ( new UI_menu );
	test.set_content ( &main_menu, 4, 4 );
	test.set_title( "Main Menu" );
	
	int c, current = 0;
	bool entering_data = false;
	while ( (c = getch())  )
	{ 
		if ( c == ENTER )
		{
			if ( entering_data ) 
			{
				const char * message = NULL;
				dual_panel_view( test.get_value(0), test.get_value(1), test.get_value(2), message ); 

				if ( message )
				{
					alert(message);
				}

				test.set_intestines ( new UI_menu );
				test.set_content ( &main_menu, 4, 4 );
				test.set_title( "Main Menu" );
				entering_data = false;
			}
			else if ( current == 0 )
			{
				test.set_intestines ( new UI_form );
				test.set_content( &new_connection, 4, 4);
				test.set_title( "New connection" );
				entering_data = true;
			}
			else if ( current == 1 )
			{
				break;
			}
		}
		else if ( c == ESCAPE )
		{
			test.set_intestines ( new UI_menu );
			test.set_content ( &main_menu, 4, 4 );
			test.set_title( "Main Menu" );
			entering_data = false;
		}
		else
		{
			current = test.key_down( c );
		}
	}
	endwin();
	return 0;
}
