#ifndef H_GUI_PREFERENCES
#define H_GUI_PREFERENCES

//custom
#include "client.h"
#include "global.h"
#include "server.h"

//Gtk
#include <gtkmm.h>

//std
#include <sstream>

class gui_preferences : public Gtk::Window
{  
public:
	gui_preferences(client * Client_in, server * Server_in);

private:
	Gtk::Window * window;
	Gtk::Entry * download_directory_entry;
	Gtk::Entry * share_directory_entry;
	Gtk::Entry * max_download_rate_entry;
	Gtk::Entry * max_upload_rate_entry;
	Gtk::Label * downloads_label;
	Gtk::Label * share_label;
	Gtk::Label * rate_label;
	Gtk::Label * connection_limit_label;
	Gtk::Label * upload_rate_label;
	Gtk::Label * download_rate_label;
	Gtk::Button * ok_button;
	Gtk::Button * cancel_button;
	Gtk::Button * apply_button;
	Gtk::HButtonBox * button_box;
	Gtk::HScale * client_connections_hscale;
	Gtk::HScale * server_connections_hscale;
	Gtk::Fixed * fixed;

	//holds pointers to the client/server the GUI has while preferences are open
	client * Client;
	server * Server;

	/*
	apply_click                - apply button clicked
	apply_settings             - read input preferences and set them
	cancel_click               - cancel button clicked
	server_connections_changed - called when server_connections_hscale changes value
	ok_click                   - ok button clicked
	*/
	void apply_click();
	void apply_settings();
	void cancel_click();
	void server_connections_changed();
	void ok_click();
};
#endif
