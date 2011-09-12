#ifndef _CONNECT_DIALOG_H_
#define _CONNECT_DIALOG_H_

#include "lab.h"

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <giomm/file.h>
#include <glibmm/ustring.h>

#include <vector>

class ConnectDialog :
	public Gtk::Window
{
public:
	ConnectDialog();
	virtual ~ConnectDialog();

protected:
	// Signals
	void on_connect_button_clicked();
	void on_close_button_clicked();

	// Funcs
	void init_widgets();
	void parse_config();
	void create_default_config(Glib::RefPtr<Gio::FileOutputStream> cfg_file);

	// Configuration
	std::vector<Glib::ustring> logins;

	Gtk::VBox main_vbox;
	Gtk::Button connect, close;
	Gtk::CheckButton save_login;
	Gtk::HButtonBox button_box;
	Gtk::Label label_login, label_password;
	Gtk::Entry entry_password;
	Gtk::ComboBoxText combo_login;
};

#endif

