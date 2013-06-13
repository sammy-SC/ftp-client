#ifndef UI_MENU_H_eoathaeoihtaeoithaoeihtoaeihtoaeuht
#define UI_MENU_H_eoathaeoihtaeoithaoeihtoaeihtoaeuht
#include "ui_window_intestines.h"
#include <menu.h>

class UI_menu : public UI_window_intestines
{
	MENU * m_menu;

	ITEM ** m_items;

	short unsigned n_of_items;

	void menu_free ();

	inline int currently_selected() const;
public:
	UI_menu ( void );

	~UI_menu ( void );

	inline short int selected_index ( void ) const;

	virtual void render ( WINDOW *,int ,int );
	
	virtual void change_content( const CMenu * );

	virtual int key_down_event( int );

	virtual const char * get_value( int ) const;
};

#endif //UI_MENU_H_eoathaeoihtaeoithaoeihtoaeihtoaeuht
