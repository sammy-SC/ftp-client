#ifndef REMOTE_PANEL_H_23087298329487q3ohf298h9vbksjhgksejh830
#define REMOTE_PANEL_H_23087298329487q3ohf298h9vbksjhgksejh830

#include "local_panel.h"
#include "ftp_commander.h"

/*! Represents remote file system.
 *
*/
class Remote_panel: public Local_panel
{
	const char * m_addr;
public:
	//! Connection through which this class can comunicate with remote server.
	Ftp_commander m_connection;
	
	//! Flag whether we are connected or not.
	bool m_connected;

	Remote_panel( int, int, int, int, const char *, const char * );

	/*! Logs the user in and sets %m_connected flag.
	 * \param username
	 * \param password
	*/
	void login( const char *, const char * );

	void list_directory( void );

	bool key_down( int );

	/*! Uploads file to remote server.
	 * \param filename
	*/
	void upload( const char * );

	/*! Creates new folder on the remote server.
	 * \param folder name
	*/
	void new_folder( const char * );

	void m_delete( const char * );
};
#endif //REMOTE_PANEL_H_23087298329487q3ohf298h9vbksjhgksejh830
