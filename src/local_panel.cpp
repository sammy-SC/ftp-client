#include <dirent.h>
#include <algorithm>
#include "functions.h"
#include "local_panel.h"
#include "ui_menu.h"
#include "global_definitions"

using namespace std;

bool compare_nocase (const std::string & first, const std::string & second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  if (first.length()<second.length()) return true;
  else return false;
}

Local_panel::Local_panel( int rows, int cols, int y , int x, const char * title ): UI_window::UI_window(rows,cols,y,x), m_title(title)
{
	set_title(title);
	set_intestines( new UI_menu );
}
//------------------------------------------------------------------------------------------
void Local_panel::set_content( void )
{
	const char ** items = new const char * [ m_files.size() + 1 ];

	unsigned i = 0;
	for ( deque<string>::const_iterator it = m_files.begin() ; it != m_files.end() ; ++it )
	{
		items[i++] = (*it).c_str();
	}

	items[ m_files.size() ] =  NULL;

	CMenu files ( items, m_files.size() + 1 );

	UI_window::set_content( &files , 3, 1 );

	set_title( m_title );

	delete [] items;
}       
//------------------------------------------------------------------------------------------
void Local_panel::list_directory( )
{
	m_files.clear();
	DIR * dr;
	struct dirent * dirp;

	dr = opendir( "." );

	while ((dirp = readdir(dr)) != NULL)
		m_files.push_back( string( dirp->d_name ) );


	sort( m_files.begin(), m_files.end(), compare_nocase );

	closedir( dr );

	set_content( );
}
//------------------------------------------------------------------------------------------
bool Local_panel::key_down( int key )
{
	m_choice = UI_window::key_down( key );
	if ( key == ENTER )
	{
		chdir( m_files.at( m_choice ).c_str() );
		list_directory();
	}
	else if ( key == F5 )
	{
		return true;
	}
	else if ( key == DELETE_KEY )
	{
		m_delete( m_files.at( m_choice ).c_str() );		
	}
	return false;
}
//------------------------------------------------------------------------------------------
const char * Local_panel::upload () const
{
	return m_files.at( m_choice ).c_str();
} 
//------------------------------------------------------------------------------------------
void Local_panel::new_folder( const char * folder_name )
{
	string command ("mkdir -p ");
	command += folder_name;
	system ( command.c_str() );
	list_directory();
}
//------------------------------------------------------------------------------------------
void Local_panel::m_delete ( const char * target ) 
{
	remove( target );
	list_directory();
}