#include <string.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "ui_window.h"

using namespace std;

int UI_window::n_of_windows = 0;
//------------------------------------------------------------------------------------------
UI_window::UI_window(int rows, int cols, int y, int x ): m_rows(rows), m_cols(cols), m_x(x), m_y(y), m_intestines( NULL )
{
	window = newwin( rows, cols, x, y);

	keypad( window, TRUE );

	set_borders();
	
	++n_of_windows;
}
//------------------------------------------------------------------------------------------
UI_window::~UI_window()
{
	if ( m_intestines ) delete m_intestines;

	erase_window();

	if ( --n_of_windows == 0 )
		endwin();
}
//------------------------------------------------------------------------------------------
void UI_window::set_title( const char * title)
{
	int length = strlen(title) , x, y = 1;
	float temp;
	m_title = title;

	temp = ( m_cols - length) / 2;
	x = (int)temp;
	wattron( window, COLOR_PAIR(1) );
	mvwprintw( window, y, x, "%s", title );
	wattroff( window, COLOR_PAIR(1) );
	wrefresh(window);
}
//------------------------------------------------------------------------------------------
void UI_window::set_intestines ( UI_window_intestines * intestines )
{
	if ( m_intestines ){
		delete m_intestines;
	}
	m_intestines = intestines;
}
//------------------------------------------------------------------------------------------
void UI_window::set_content ( const CMenu * content, int x, int y )
{
	werase( window );
	m_intestines->change_content( content );
	m_intestines->render( window, x, y );
	set_borders();
	wrefresh( window );
}
//------------------------------------------------------------------------------------------
int UI_window::key_down ( int key )
{
	int result = m_intestines->key_down_event( key );
	wrefresh( window );
	return result;
}
//------------------------------------------------------------------------------------------
void UI_window::erase_window( void ) 
{
	werase( window );
	wrefresh( window );
}
//------------------------------------------------------------------------------------------
void UI_window::set_borders ()
{
	box( window, 0, 0);
	mvwaddch( window, 2, 0, ACS_LTEE);
	mvwhline( window, 2, 1, ACS_HLINE, m_cols - 2);
	mvwaddch( window, 2, m_cols - 1, ACS_RTEE);
	wrefresh( window );
}
//------------------------------------------------------------------------------------------
const char * UI_window::get_value ( int index ) const
{
	return m_intestines->get_value( index );
}
