#include <iostream>
#include "ftp_commander.h"

using namespace std;

int main()
{
	Ftp_commander conn;

	conn.m_connect( "ftp.xssusla.lbx.sk", 21 );

	conn.login("xssusla.lbx.sk", "Cr6w9ceb" );

	//conn.download("image.jpg");
	conn.download("examples2");

	return 0;
}
