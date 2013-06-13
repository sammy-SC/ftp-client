#ifndef UI_WINDOW_H_3094u0238hy0283082h08fh2038hf0238hf
#define UI_WINDOW_H_3094u0238hy0283082h08fh2038hf0238hf
#include <ncurses.h>
#include "ui_window_intestines.h"

/*! Wrapper class to work with ncurses windows.
 * Class provides more verbose API to work with windows in ncurses.
 */
class UI_window
{
	//! Dimensions of the window.
	int m_rows, m_cols, m_x, m_y;

	//! Pointer to intestines or insides of the window, %UI_window_intestines has given interface.
	UI_window_intestines * m_intestines;

	//! Title of the window, not obligatory however everytime window needs to refresh even title needs to be remembered.
	const char * m_title;
public:
	//! Counting references to all windows to know when to start ncurses and when to close ncurses.
	static int n_of_windows;

	/*! Sets borders around window and for title.
	 * 
	*/
	void set_borders ( void );

	/*! Pointer to ncurses struct window.
	 * 
	*/
	WINDOW * window;

	//! Sets dimensions of the window.
	UI_window( int ,int , int = COLS / 2 , int = LINES / 2 );

	~UI_window();

	/*! changes title of the window.
	 * \param Desired title.
	*/
	void set_title( const char * );

	/*! Changes type of intestines contained by window.
	 * \param new intestines.
	*/
	void set_intestines ( UI_window_intestines * );

	/*! Changes content of intestines.
	 * \param labels.
	 * \param x position within window.
	 * \param y position within window.
	*/
	void set_content ( const CMenu * , int = 1, int = 1 );

	/*! Propagates key_down to its intestine.
	 * \param Key code.
	*/
	int key_down ( int key );

	/*! Removes window from the screen.
	 * 
	*/
	void erase_window ( void );

	/*! If window contains form, this will get his value
	 * \param index of the field
	*/
	const char * get_value ( int ) const;
};

#endif //UI_WINDOW_H_3094u0238hy0283082h08fh2038hf0238hf
