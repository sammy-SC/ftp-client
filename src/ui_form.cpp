#include <stdlib.h>
#include <string.h>
#include "ui_form.h"
using namespace std;

UI_form::UI_form():  m_form( NULL ), m_fields ( NULL ), n_of_fields( 0 )
{
}
//--------------------------------------------------------------------------------------------
UI_form::~UI_form()
{
	m_free_form();
}	
//--------------------------------------------------------------------------------------------
void UI_form::m_free_form()
{
	unpost_form( m_form );
	free_form( m_form );
	for ( int i = 0 ; i < n_of_fields ; ++i )
	{
		free_field( m_fields[i] );
	}
	delete [] m_fields;

	m_form = NULL;
	m_fields = NULL;
}	
//--------------------------------------------------------------------------------------------
void UI_form::render ( WINDOW * window, int x, int y ) 
{
	m_form = new_form(m_fields);

        set_form_win(m_form, window);
        set_form_sub(m_form, derwin(window, 0, 0, 2, 2));

	
	post_form(m_form);
	wrefresh(window);

	for ( short unsigned i = 0 ; i < n_of_fields ; ++i )
	{
		mvwprintw( window, 5 + i * 2, 5, "%s", form_labels[i] ); 
	}	

	refresh();
}

//--------------------------------------------------------------------------------------------
void UI_form::change_content ( const CMenu * content )
{
	if ( m_form )
		m_free_form();

	form_labels = content->m_menu;
	n_of_fields = content->m_length;
	m_fields = new FIELD * [ n_of_fields + 1 ];

	for ( short unsigned i = 0; i < n_of_fields; ++i )
		m_fields[i] = new_field( 1, 25, 3 + i*2, 15, 0, 0 );

	m_fields[n_of_fields] = NULL;

	for ( short unsigned i = 0; i < n_of_fields; ++i )
	{
		set_field_back(m_fields[i], A_UNDERLINE);
		field_opts_off(m_fields[i], O_AUTOSKIP); 
	}
}
//--------------------------------------------------------------------------------------------
int UI_form::key_down_event( int key )
{
	
	switch(key)
	{	
		case KEY_DOWN:
			/* Go to next field */
			form_driver(m_form, REQ_NEXT_FIELD);
			/* Go to the end of the present buffer */
			/* Leaves nicely at the last character */
			form_driver(m_form, REQ_END_LINE);
			break;
		case KEY_UP:
			/* Go to previous field */
			form_driver(m_form, REQ_PREV_FIELD);
			form_driver(m_form, REQ_END_LINE);
			break;
		case KEY_LEFT:
			form_driver(m_form, REQ_PREV_CHAR);
			break;
		case KEY_RIGHT:
			form_driver(m_form, REQ_NEXT_CHAR);
			break;
		case KEY_BACKSPACE:
			form_driver(m_form, REQ_PREV_CHAR);
			form_driver(m_form, REQ_DEL_CHAR);
			break;
		case 10:
			break;
		default:
			/* If this is a normal character, it gets */
			/* Printed				  */	
			form_driver(m_form, key);
			break;
	}
	return -1;
}

const char * UI_form::get_value ( int index ) const
{
	form_driver(m_form, REQ_PREV_FIELD);
	char * value = field_buffer(m_fields[index],0);
	for ( unsigned i = 0 ; i < strlen( value ) ; ++i )
	{
		if ( value[i] == ' ') 
		{
			value[i] = '\0';
			break;
		}
	}
	return value;
}
