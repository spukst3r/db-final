#include <gtkmm.h>
#include "connectdialog.h"

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	ConnectDialog dlg;

	dlg.set_position(Gtk::WIN_POS_CENTER);
	
	Gtk::Main::run(dlg);
	return 0;
}

