#ifndef _CONNECT_DIALOG_H_
#define _CONNECT_DIALOG_H_

#include "lab.h"

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/combo.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <giomm/file.h>

class ConnectDialog :
	public Gtk::Window
{
public:
	ConnectDialog();
	virtual ~ConnectDialog();

protected:
	void on_connect_button_clicked();
	void on_close_button_clicked();

	void init_widgets();
	void parse_config();
	void create_deafult_config(Glib::RefPtr<Gio::File> cfg_file);

	Gtk::VBox main_vbox;
	Gtk::Button connect, close;
	Gtk::CheckButton save_login;
	Gtk::HButtonBox button_box;
	Gtk::Label label_login, label_password;
	Gtk::Entry entry_password;
	Gtk::Combo combo_login;
};

#endif

