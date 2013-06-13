#ifndef UI_WINDOW_INTESTINES_H_023894520958209385029375029375
#define UI_WINDOW_INTESTINES_H_023894520958209385029375029375
#include <ncurses.h>

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
	CMenu( const char * menu [], short unsigned length ): m_menu( menu ), m_length( length ) {}

};

/*! Provides basic interface for window insides.
 * 
 */
class UI_window_intestines
{
public:
	/*! renders itself into window.
	 * \param window into which it should be displayed.
	 * \param x position within the window.
	 * \param y position within the window.
	 */
	virtual void render ( WINDOW *, int, int )  = 0;

	/*! changes content of the intestines.
	 * \param new content
	 */
	virtual void change_content ( const CMenu * ) = 0;

	/*! Receives key down event and respondes accordingly.
	 * \param key code.
	 */
	virtual int key_down_event( int ) = 0;

	/*! Returns field value at provided index.
	 * \param index of field, 0 based.
	 * \return value of field
	 */
	virtual const char * get_value ( int ) const = 0;

};
#endif //UI_WINDOW_INTESTINES_H_023894520958209385029375029375
