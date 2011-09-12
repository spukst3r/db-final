#include <gtkmm.h>
#include "connectdialog.h"

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	ConnectDialog dlg;
	
	Gtk::Main::run(dlg);
	return 0;
}

