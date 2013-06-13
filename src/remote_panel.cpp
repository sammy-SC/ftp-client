#include <sstream>
#include <algorithm>
#include "remote_panel.h"
#include "functions.h"
#include "global_definitions"

using namespace std;



Remote_panel::Remote_panel( int rows, int cols, int y , int x, const char * title, const char * addr ):
	Local_panel::Local_panel( rows, cols, y, x, title ), m_addr( addr ), m_connected( true )
{ 
	//if( !m_connection.m_connect( "ftp.xssusla.lbx.sk", 21 ) )
	if ( !m_connection.m_connect( addr, 21 ) )
		m_connected = false;
}
//--------------------------------------------------------------------------------------------
void Remote_panel::login( const char * user, const char * pass )
{
	/*
	if ( m_connected )
		m_connected = m_connection.login("xssusla.lbx.sk", "Cr6w9ceb" );
	*/
	if ( m_connected )
		m_connected = m_connection.login( user, pass );
	
}
//--------------------------------------------------------------------------------------------
void Remote_panel::list_directory( void )
{  
	m_files.clear();
	stringstream files;
	string tmp;
	m_connection.ls( files );
	while ( files >> tmp )
		m_files.push_back( string( tmp ) );

	sort( m_files.begin(), m_files.end(), compare_nocase );
	set_content();
}
//--------------------------------------------------------------------------------------------
bool Remote_panel::key_down( int key )
{
	m_choice = UI_window::key_down( key );
	if ( key == ENTER )
	{
		m_connection.cwd( m_files.at( m_choice ).c_str() );
		list_directory();
	}
	else if ( key == F5 )
	{
		m_connection.download( m_files.at( m_choice ).c_str() );
		return true;
	}
	else if ( key == DELETE_KEY )
	{
		m_delete( m_files.at( m_choice ).c_str() );
	}
	return false;
}
//--------------------------------------------------------------------------------------------
void Remote_panel::new_folder( const char * folder_name )
{
	m_connection.mkd( folder_name );
	list_directory();
}
//--------------------------------------------------------------------------------------------
void Remote_panel::m_delete( const char * target )
{
	m_connection.dele( target );
	list_directory();
}
