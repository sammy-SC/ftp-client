#include <string.h>
#include <stdlib.h>
#include <menu.h>
#include "ui_menu.h"
#include "global_definitions"

using namespace std;

void UI_menu::menu_free ()
{	
	unpost_menu( m_menu );
	free_menu( m_menu );

	for( short unsigned i = 0; i < n_of_items + 1; ++i)
	{
		free_item( m_items[i]);
	}
	delete [] m_items;
	m_items = NULL;
	m_menu = NULL;
}
//-------------------------------------------------------------------------------------------
UI_menu::UI_menu ( void ): m_items(NULL),n_of_items(0) 
{ 
}
//-------------------------------------------------------------------------------------------
UI_menu::~UI_menu ( void ) 
{
	menu_free ();
}
//-------------------------------------------------------------------------------------------
short int UI_menu::selected_index () const
{
	ITEM *cur;
	cur = current_item( m_menu );
	if ( strcmp( item_name( cur ), EXIT_PHRASE ) == 0 ) return -1;
	if ( strcmp( item_name( cur ), BACK_PHRASE ) == 0 ) return -1;

	for ( short unsigned i = 0 ; i < n_of_items ; ++i )
	{
		if ( cur == m_items[i] )
		{
			return i;
		}
	}

	return -1;
}
//-------------------------------------------------------------------------------------------
void UI_menu::render ( WINDOW * window, int x, int y )
{
	set_menu_win( m_menu, window );

	set_menu_sub( m_menu, derwin ( window, 0, 0, x , y ));

	set_menu_format( m_menu, LINES - 11, 1 );	

	post_menu( m_menu );

	wrefresh( window );
}
//-------------------------------------------------------------------------------------------
void UI_menu::change_content( const CMenu * content )
{
	if ( m_items ) menu_free();

	n_of_items = content->m_length;

	m_items = new ITEM * [ n_of_items + 1 ];

	for ( short unsigned i = 0; i < n_of_items; ++i )
		m_items[i] = new_item( content->m_menu[i], "  " );

	m_items[ n_of_items ] = NULL;
	
	m_menu = new_menu(( ITEM** ) m_items ); // creating menu out of items

	set_menu_mark( m_menu, " -> " ); // setting menu pointer
}
//-------------------------------------------------------------------------------------------
int UI_menu::key_down_event( int key )
{
	switch(key)
	{	
		case KEY_DOWN:
			menu_driver(m_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(m_menu, REQ_UP_ITEM);
			break;
	}
	return currently_selected();
}
//-------------------------------------------------------------------------------------------
inline int UI_menu::currently_selected() const
{
	ITEM * cur;
	cur = current_item( m_menu );
	for ( int i = 0 ; i < n_of_items ; ++i )
	{
		if ( cur == m_items[i] ) return i;

	}
	return -1;
}
//-------------------------------------------------------------------------------------------
const char * UI_menu::get_value( int index ) const
{
	return (char*)NULL;
}	
