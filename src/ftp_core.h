#ifndef FTP_CORE_H_1082341384u918hf983219h9uvhuhseiuvh
#define FTP_CORE_H_1082341384u918hf983219h9uvhuhseiuvh

#include <string>

class Ftp_core
{
protected:
	//! port number
	int m_port;

	//! shared buffer within instance of class
	char buffer[200];
	
	/*! creates a new connection
	* \param address of the server 
	* \param port of the connection
	*/
	int open (const char * , const int );

	/*! clears out buffer and fills it with provided value
	* \param desired value to be put into buffer 
	*/
	void set_buffer ( const char * );

	/*! erases buffer
	*/
	void flush_buffer ();

	/*! opens data port in passive mode
	* \return port number 
	*/
	int passive_mode ();

	/*! sends whatever is currently in the %buffer to %m_port  
	*  
	*/
	void m_send ( void );

	/*! creates directory on local file system
	* \param path to new directory 
	*/
	void mkdir ( const std::string & );
public:
	//! response code from last command
	int m_code;

	Ftp_core( void );

	~Ftp_core( void );

	bool m_connect( const char *, const int );
	
	/*! sends message to %m_port  
	* \param message that you want to send 
	*/
	void m_send ( const char * );

	/*! listnes to %m_port and fills %buffer with incoming message
	*  
	*/
	int receive( void ); 

	/*! Opens data port using %passive_mode and lists current directory
	* \param ostream that is filled with the results 
	* \param directory that we wish to list
	*/
	void ls ( std::ostream & , const char * = "."  );

	/*! Creates directory on the remote server    
	* \param New directory name, path to new directory can be provided as well.
	*/
	void mkd ( const char * );
	
	/*! Changes working directory 
	* \param Desired directory 
	*/
	void cwd ( const char * );

	/*! Sends to %m_port login credentials    
	* \param User name 
	* \param Passwod 
	*/
	bool login ( const char *, const char * );

	/*! Sends a command with parameter to %m_port    
	* \param command that will be send to remote 
	* \param parameter of the command 
	*/
	void command ( const char *, const char * );
};

#endif 
//FTP_CORE_H_1082341384u918hf983219h9uvhuhseiuvh
