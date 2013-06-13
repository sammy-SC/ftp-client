#include "cmenu.h"
using namespace std;


CMenu::CMenu( const char * menu [], short unsigned length ): m_menu( menu ), m_length( length ) {}

CMenu::~CMenu()
{
	for ( int i = 0 ; i < m_length ; ++ i )
	{
		delete m_menu[i];
	}	
	delete [] m_menu;
}
