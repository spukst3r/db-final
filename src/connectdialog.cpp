#include "connectdialog.h"
#include <gtkmm/main.h>
#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include <glibmm/keyfile.h>
#include <glibmm/ustring.h>
#include <glibmm/fileutils.h>
#include <giomm/file.h>

#include <iostream>

using std::cout;
using std::endl;

ConnectDialog::ConnectDialog():
	main_vbox(false, 5),
	connect(Gtk::Stock::CONNECT),
	close(Gtk::Stock::CLOSE),
	button_box(Gtk::BUTTONBOX_SPREAD, 5),
	label_login("Login:"),
	label_password("Password:"),
	save_login("Remember login")
{
	parse_config();
	init_widgets();
}

ConnectDialog::~ConnectDialog()
{
}

void ConnectDialog::init_widgets()
{
	set_border_width(5);
	set_title(PROJECT_TITLE);

	connect.signal_clicked().connect(sigc::mem_fun(*this,
				&ConnectDialog::on_connect_button_clicked));
	close.signal_clicked().connect(sigc::mem_fun(*this,
				&ConnectDialog::on_close_button_clicked));

	entry_password.property_caps_lock_warning() = true;
	entry_password.set_visibility(false);

	main_vbox.add(label_login);
	main_vbox.add(combo_login);
	main_vbox.add(label_password);
	main_vbox.add(entry_password);
	main_vbox.add(save_login);

	button_box.add(connect);
	button_box.add(close);

	main_vbox.add(button_box);
	main_vbox.show_all();

	add(main_vbox);
	show_all();
}

void ConnectDialog::parse_config()
{
	Glib::ustring config_file_name = "~/." PROJECT_TITLE;
	config_file_name = config_file_name.lowercase();

	Glib::KeyFile config_file;
	Glib::RefPtr<Gio::File> new_config;

	try {
		config_file.load_from_file(config_file_name);
	} catch (const Glib::Error &e) {
		if (e.code() == Glib::FileError::NO_SUCH_ENTITY) {
			Gtk::MessageDialog msg("Creating new config...");
			msg.run();
			new_config = Gio::File::create_for_path(config_file_name);
			try {
				new_config->create_file(Gio::FILE_CREATE_PRIVATE);
			} catch (const Glib::Error &e) {
				cout << e.what() << endl;
			}
		}
	}

	try {
		Glib::ArrayHandle<Glib::ustring> logins = 
			config_file.get_string_list("Account", "logins");
	} catch (const Glib::Error &e) {
		Gtk::MessageDialog msg("logins key not found");
		msg.run();
	}
}

void ConnectDialog::create_deafult_config(Glib::RefPtr<Gio::File> cfg_file)
{
}

void ConnectDialog::on_connect_button_clicked()
{
}

void ConnectDialog::on_close_button_clicked()
{
	Gtk::Main::quit();
}

