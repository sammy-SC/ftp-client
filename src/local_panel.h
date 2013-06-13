#ifndef LOCAL_PANEL_H_oeauhroq3298039oiorishorsihtoi3h4
#define LOCAL_PANEL_H_oeauhroq3298039oiorishorsihtoi3h4
#include <deque>
#include <string>
#include "ui_window.h"


/*! Represent local file system
 *
*/
class Local_panel: public UI_window
{
protected:
	const char * m_title;

	//! Contains files and folders in current directory.
	std::deque <std::string> m_files;

	//! Index of currently highlighted item.
	short unsigned m_choice;
public:
	Local_panel( int, int , int , int , const char * ); 	

	void set_content( void );

	/*! lists current directory and displays it.
	 * 
	*/
	void list_directory( void );

	/*! propagates key down event further.
	 * \param key code pressed.
	 * \return if something has changed returns true, otherwise false.
	*/
	bool key_down( int );

	/*! when user chooses to upload a file this method returns filepath
	 * \return filepath
	*/
	const char * upload ( void ) const;

	/*! creates new folder on local file system
	 * \return filepath
	*/
	void new_folder( const char * );

	void m_delete ( const char * );
};

#endif //LOCAL_PANEL_H_oeauhroq3298039oiorishorsihtoi3h4
