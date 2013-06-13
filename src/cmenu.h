#ifndef CMENU_H_heirkhajeh23kk3jh4kjnk23jkjbkj2b3kjh43jk
#define CMENU_H_heirkhajeh23kk3jh4kjnk23jkjbkj2b3kjh43jk

/*! Structure is used as parameter for %UI_window.
* 
*/
struct CMenu
{
	
	/*! Structure is used as parameter for %UI_window.
	 * 
	 */
	const char ** m_menu;

	/*! Structure is used as parameter for %UI_window.
	 * 
	 */
	short unsigned m_length;

	/*! Structure is used as parameter for %UI_window.
	 * 
	 */
	CMenu( const char * [], short unsigned );

	~CMenu();

};

#endif // CMENU_H_heirkhajeh23kk3jh4kjnk23jkjbkj2b3kjh43jk
