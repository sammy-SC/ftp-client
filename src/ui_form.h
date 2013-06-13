#ifndef UI_FORM_H_02840238457023897502937480928304123  
#define UI_FORM_H_02840238457023897502937480928304123  
#include "ui_window_intestines.h"
#include "form.h"

/*! Wrapper class aroud ncurses form.h library
 * Class is designed to easy the work with form.h library, provides basic API to display and process forms
*/
class UI_form : public UI_window_intestines
{
	//! Pointer to ncurses's form
	FORM * m_form;

	//! Array of current fields contained by %m_form
	FIELD ** m_fields;

	//! number of %m_fields
	short unsigned n_of_fields;

	const char ** form_labels;

	void m_free_form();
public:
	UI_form( void );

	~UI_form( void );

	virtual void render ( WINDOW *, int, int );

	virtual void change_content ( const CMenu * );

	virtual int key_down_event( int );

	virtual const char * get_value ( int ) const;
};
#endif //UI_FORM_H_02840238457023897502937480928304123  
