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
	save_login("Remember login"),
	combo_login(true)
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

	main_vbox.add(label_login);
	main_vbox.add(combo_login);
	main_vbox.add(save_login);

	button_box.add(connect);
	button_box.add(close);

	main_vbox.add(button_box);
	main_vbox.show_all();

	add(main_vbox);
	show_all();

	combo_login.remove_all();
	for (int i=0; i<logins.size(); i++) {
		combo_login.append(logins[i]);
	}
	combo_login.set_active(0);
}

void ConnectDialog::parse_config()
{
	Glib::ustring config_file_name = Glib::get_home_dir();
	config_file_name += "/." PROJECT_TITLE;

	Glib::KeyFile config_file;
	Glib::RefPtr<Gio::File> file;
	Glib::RefPtr<Gio::FileOutputStream> new_config;

	file = Gio::File::create_for_path(config_file_name);

	if (file->query_exists()) {
		config_file.load_from_file(config_file_name);
	} else {
		cerr << "Config file not found, creating default one" << endl;

		try {
			new_config = file->create_file(Gio::FILE_CREATE_PRIVATE);
			create_default_config(new_config);
			new_config->close();
		} catch (const Glib::Error &e) {
			cerr << "parse_config(): Creation of config file failed! "
									 "what(): " << e.what() << endl;
		}

		config_file.load_from_file(config_file_name);
	}

	try {
		logins =
			config_file.get_string_list("Account", "logins");
	} catch (const Glib::Error &e) {
		cerr << "parse_config(): " << e.what() << endl;
	}
}

void ConnectDialog::create_default_config(Glib::RefPtr<Gio::FileOutputStream> cfg_file)
{
	Glib::ustring config_lines[] = {
		"# Configuration file for " PROJECT_TITLE "\n",
		"# Lines beginning with a '#' and blank lines are ignored\n",
		"# Groups are started by a header line containing the group name enclosed in '[' and ']'\n\n",
		"# Group for remembered account settings\n",
		"[Account]\n",
		"logins=\n\n",
		"public_key=\n\n",
		"# Group for DB conection settings\n",
		"[Connection]\n",
		"server=127.0.0.1\n",
		"login=guest\n",
		"password=guest_passwd\n\n",
	};

	for (int i=0; i<sizeof(config_lines)/sizeof(config_lines[0]); i++)
		cfg_file->write(config_lines[i]);
}

void ConnectDialog::on_connect_button_clicked()
{
}

void ConnectDialog::on_close_button_clicked()
{
	Gtk::Main::quit();
}

