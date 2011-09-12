#include "connectdialog.h"
#include <gtkmm/main.h>
#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include <glibmm/keyfile.h>
#include <glibmm/ustring.h>
#include <glibmm/fileutils.h>
#include <giomm/file.h>

#include <iostream>
#include <vector>

using std::cerr;
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
	Glib::ustring config_file_name = Glib::get_home_dir();
	config_file_name += "/." PROJECT_TITLE;

	Glib::KeyFile config_file;
	Glib::RefPtr<Gio::File> file;

	try {
		config_file.load_from_file(config_file_name);
	} catch (const Glib::Error &e) {
		if (e.code() == Glib::FileError::NO_SUCH_ENTITY) {
			cerr << "Config file not find, creating new one..." << endl;

			file = Gio::File::create_for_path(config_file_name);

			try {
				Glib::RefPtr<Gio::FileOutputStream> new_config = 
					file->create_file(Gio::FILE_CREATE_PRIVATE);
				create_default_config(new_config);
			} catch (const Glib::Error &e) {
				cerr << "parse_config(): Creation of config file failed! \
										 what(): " << e.what() << endl;
			}
		}
	}

	try {
		std::vector<Glib::ustring> logins = 
			config_file.get_string_list("Account", "logins");

		for (int i=0; i<logins.size(); i++)
			cerr << logins[i] << endl;

	} catch (const Glib::Error &e) {
		cerr << "parse_config(): logins key not found" << endl;
	}
}

void ConnectDialog::create_default_config(Glib::RefPtr<Gio::FileOutputStream> cfg_file)
{
	cfg_file->write("# configuration file for " PROJECT_TITLE "\n");
	cfg_file->write("# Lines beginning with a '#' and blank lines are ignored\n");
	cfg_file->write("# Groups are started by a header line containing the group "
			"name enclosed in '[' and ']'\n");

	cfg_file->close();
}

void ConnectDialog::on_connect_button_clicked()
{
}

void ConnectDialog::on_close_button_clicked()
{
	Gtk::Main::quit();
}

