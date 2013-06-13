#include <string.h>
#include <stdio.h>
#include <iostream>

#include "ftp_commander.h"
#include "ftp_thread.h"

using namespace std;
#define THREAD_LIMIT 10

//-------------------------------------------------------------------------------------------------
void *thread_download ( void * arg )
{
	Ftp_thread * conn = (Ftp_thread *) arg;
	conn->prepare_download( conn->m_target );
	conn->init_download();
	pthread_exit(NULL);
}
//-------------------------------------------------------------------------------------------------
void *thread_upload( void * arg )
{
	Ftp_thread * conn = (Ftp_thread *) arg;
	conn->prepare_upload( conn->m_target );
	conn->init_upload();
	pthread_exit(NULL);
}
//-------------------------------------------------------------------------------------------------
Ftp_commander::Ftp_commander ( void ): Ftp_core::Ftp_core()
{
	m_threads[0] = (pthread_t) NULL;
	m_threads[1] = (pthread_t) NULL;
}
//-------------------------------------------------------------------------------------------------
Ftp_commander::~Ftp_commander ( void )  
{
	if ( m_threads[0] )
		pthread_join(m_threads[0],NULL);

	if ( m_threads[1] )
		pthread_join(m_threads[1],NULL);
}
//-------------------------------------------------------------------------------------------------
void Ftp_commander::dele ( const char * target ) 
{
	command("dele", target);
}
//-------------------------------------------------------------------------------------------------
void Ftp_commander::upload ( const char * target)
{
	char current_directory [50];	

	m_send("PWD");
	sscanf( buffer, "257 \"%49[^\"]\"", current_directory );

	Ftp_thread * tmp = new Ftp_thread( m_addr, m_port, m_user, m_pass, target,  current_directory );
	pthread_create( &m_threads[1], NULL, thread_upload, (void*) tmp );
}
//-------------------------------------------------------------------------------------------------
void Ftp_commander::download ( const char * target)
{
	Ftp_thread * tmp = new Ftp_thread( m_addr, m_port, m_user, m_pass, target );
	pthread_create( &m_threads[0], NULL, thread_download, (void*) tmp );
}
//-------------------------------------------------------------------------------------------------
bool Ftp_commander::m_connect ( const char * addr, const int port )
{
	m_addr = addr;
	m_port = port;	
	return Ftp_core::m_connect( addr, port );
}
//-------------------------------------------------------------------------------------------------
bool Ftp_commander::login ( const char * user, const char * pass )
{
	m_user = user;
	m_pass = pass;
	return Ftp_core::login( user, pass );

}
