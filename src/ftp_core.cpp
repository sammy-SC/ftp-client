#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <netdb.h>
#include <sys/socket.h>

#include "ftp_core.h"

using namespace std;
#define THREAD_LIMIT 10

//-------------------------------------------------------------------------------------------------
int Ftp_core::open (const char * addr, const int port)
{
	struct addrinfo * ai;
	char portStr[20];
	int fd;

	snprintf ( portStr, sizeof ( portStr ), "%d", port );

	if ( getaddrinfo ( addr, portStr, NULL, &ai ) != 0 )
	{
		return -1;
	}

	fd = socket ( ai -> ai_family, SOCK_STREAM, 0 );
	if ( fd == -1 ) 
	{
		return -1;
	}

	if ( connect ( fd, ai -> ai_addr, ai -> ai_addrlen ) != 0 ) 
	{
		freeaddrinfo ( ai );
		return -1;
	}
	freeaddrinfo ( ai );
	return fd;
}
//-------------------------------------------------------------------------------------------------
int Ftp_core::passive_mode ( void )
{
	m_send ( "PASV" );
	char * openingBracket, * closingBracket;

	openingBracket = strstr(buffer, "(");
	closingBracket = strstr(buffer, ")");
	++openingBracket;

	*closingBracket = '\0';

	int h1, h2, h3, h4, p1, p2;
	sscanf(openingBracket, "%i,%i,%i,%i,%i,%i", &h1, &h2, &h3, &h4, &p1, &p2);

	flush_buffer();
	sprintf( buffer, "%d.%d.%d.%d", h1, h2, h3, h4 );

	return open(buffer, (p1*256) + p2 );
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::set_buffer ( const char * message ) 
{
	flush_buffer();
	strcpy( buffer, message );
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::flush_buffer ()
{
	memset ( buffer, 0, sizeof(buffer) );
}
//-------------------------------------------------------------------------------------------------
bool Ftp_core::m_connect(const char * addr, const int port )
{
	m_port = open( addr, port );
	if ( m_port == -1 ) 
		return false;
	receive();
	return true;	
}
//-------------------------------------------------------------------------------------------------
Ftp_core::Ftp_core( void ): m_port(0)
{
}
//-------------------------------------------------------------------------------------------------
Ftp_core::~Ftp_core()
{
	m_send("QUIT");
	close(m_port);
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::m_send ( const char * message )
{
	set_buffer( message );
	strcat ( buffer, "\n" );
	send ( m_port, buffer, strlen ( buffer ), 0 );
	receive();
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::m_send ( void )
{
	strcat ( buffer, "\n" );
	send ( m_port, buffer, strlen ( buffer ), 0 );
	receive();
}
//-------------------------------------------------------------------------------------------------
int Ftp_core::receive( void ) 
{

	flush_buffer();

	int result = recv ( m_port, buffer, sizeof(buffer) - 1, 0 );

	sscanf( buffer, "%i ", &m_code );
	
	return result;
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::ls ( ostream & os, const char * directory )
{
	int data = passive_mode();
	command( "NLST", directory );
	flush_buffer();
	while ( recv( data, buffer, sizeof(buffer) - 1, 0 ) )
	{	
		os << buffer;
		flush_buffer();
	}
	close(data);
	receive();
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::cwd ( const char * directory ) 
{
	set_buffer("CWD ");
	strcat( buffer, directory );
	m_send();
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::mkd ( const char * newDir ) 
{
	set_buffer("MKD ");
	strcat( buffer, newDir );
	m_send( );
}
//-------------------------------------------------------------------------------------------------
bool Ftp_core::login ( const char * username, const char * password ) 
{
	command("USER", username);
	command("PASS", password);

	int code;

	sscanf( buffer, "%i ", &code );

	if ( code == 230 ) return true;
	else return false;
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::command ( const char * command, const char * param ) 
{
	set_buffer(command);
	strcat( buffer, " " );
	strcat( buffer, param );
	m_send( );
}
//-------------------------------------------------------------------------------------------------
void Ftp_core::mkdir ( const string & filename )
{
	string command ("mkdir -p ");
	command += filename;
	system ( command.c_str() );
}
