#ifndef FTP_H_dzpohdo23h2lj3hljh3230428u98938dkj
#define FTP_H_dzpohdo23h2lj3hljh3230428u98938dkj

#include <queue>
#include <pthread.h>
#include "ftp_core.h"

class Ftp_commander: public Ftp_core
{
	pthread_t m_threads[2];
	const char * m_addr;
	int m_port;
	const char * m_user;
	const char * m_pass;
public:
	//! queue of file to be downloaded
	std::queue <std::string> downloadList;

	//! queue of file to be uploaded
	std::queue <std::string> uploadList;

	Ftp_commander();

	~Ftp_commander();

	/*! Deletes directory on the remote server.
	* \param Directory name to be deleted, path the the directory can be provided as well
	*/
	void dele ( const char * );

	void upload( const char * );

	void download( const char * );

	bool m_connect( const char *, const int );

	bool login( const char *, const char * );
};


#endif // FTP_H_dzpohdo23h2lj3hljh3230428u98938dkj
