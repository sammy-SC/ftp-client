#ifndef FTP_H_thread_eajrhoalirhoaelhro2380283hobjlwbefkjah
#define FTP_H_thread_eajrhoalirhoaelhro2380283hobjlwbefkjah

#include <queue>
#include "ftp_core.h"

class Ftp_thread: public Ftp_core 
{
	std::queue< std::string > fileList;
	std::string working_directory; 
public:
	const char * m_target;

	Ftp_thread( const char *, const int, const char *, const char *, const char *, const char * );

	Ftp_thread( const char *, const int, const char *, const char *, const char * );
	/*! Creates necesarry directories and fills %m_files   
	* \param Path to the file needs to be provided
	*/
	void prepare_download ( const char * );

	void init_download ( void );

	/*! Creates necesarry directories and fills %m_files   
	* \param Path to the file needs to be provided
	*/
	void prepare_upload( const std::string & );

	void init_upload ( void );
};

#endif // FTP_H_thread_eajrhoalirhoaelhro2380283hobjlwbefkjah
