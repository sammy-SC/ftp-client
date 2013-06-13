#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/socket.h>
#include "ftp_thread.h"

#include <ncurses.h>

#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------
Ftp_thread::Ftp_thread ( const char * addr, const int port, const char * user, const char * pass, const char * target, const char * working_dir ): 
	working_directory( working_dir ), m_target(target) 
{
	working_directory += "/";
	m_connect( addr, port );
	login( user, pass );
	command("TYPE", "I");
}
//-------------------------------------------------------------------------------------------------
Ftp_thread::Ftp_thread ( const char * addr, const int port, const char * user, const char * pass, const char * target ): m_target(target)
{
	m_connect( addr, port );
	login( user, pass );
	command("TYPE", "I");
}
//-------------------------------------------------------------------------------------------------
void Ftp_thread::prepare_download ( const char * target ) 
{
	command( "RETR", target );

	if ( m_code == 425 )
	{ 
		fileList.push( string( target ) );	
	}
	else if ( m_code == 550 )
	{
		stringstream files;
		string oneFile;

		mkdir ( target );

		ls ( files , target );
		files >> oneFile;
		files >> oneFile;
		while ( files >> oneFile ){
			prepare_download( oneFile.c_str() );
		}
	}
}

//-------------------------------------------------------------------------------------------------
void Ftp_thread::init_download () 
{
	int response_size
		, data_port;

	while ( !fileList.empty() )
	{
		data_port = passive_mode();	

		command("RETR", fileList.front().c_str() );

		ofstream newFile( fileList.front().c_str(), ofstream::binary );	

		flush_buffer();

		while ( ( response_size = recv( data_port, buffer, sizeof( buffer ), 0 ) ) )
		{
			newFile.write( buffer, response_size );
			flush_buffer();
		}
		newFile.close();
		close( data_port );
		receive();
		fileList.pop();
	}
}
//-------------------------------------------------------------------------------------------------
void Ftp_thread::prepare_upload ( const string & target ) 
{
	string tmp("test -d ");	
	tmp += target;	

	if ( system( tmp.c_str() ) == 0 )
	{
		tmp.clear();
		tmp += working_directory;
		tmp += "/";
		tmp += target;
		mkd( tmp.c_str() );
		DIR * dr;
		struct dirent * dirp;

		dr = opendir( target.c_str() );
		while ((dirp = readdir(dr)) != NULL)
		{
			if ( dirp->d_name[0] == '.' ) continue;
			tmp.clear();
			tmp = target;
			tmp += "/";
			tmp += dirp->d_name;
			prepare_upload( tmp );
		}
	}
	else
	{
		fileList.push( target );
	}
}
//-------------------------------------------------------------------------------------------------
void Ftp_thread::init_upload()
{
	int data_port
		, loaded;
	while ( !fileList.empty() )
	{
		string target_file = working_directory + fileList.front();

		data_port = passive_mode();	

		command("STOR", target_file.c_str() );

		ifstream file ( fileList.front().c_str(), ifstream::in | ifstream::binary );

		loaded = 0;
		do 
		{
			loaded = file.readsome( buffer, sizeof(buffer) - 1 );
			send ( data_port, buffer, loaded, 0 );
			flush_buffer();
		} while ( loaded != 0 );

		file.close();

		close( data_port );
		
		receive();

		fileList.pop();
	}
}
