#include <stdio.h>                      /* for printf */


#include "gdwiimote.h"


#include <godot_cpp/core/class_db.hpp>

#ifndef WIIUSE_WIN32
#include <unistd.h>                     /* for usleep */
#endif

#define MAX_WIIMOTES				1//4

using namespace godot;

void GDWiimote::_bind_methods() {

	ClassDB::bind_method(D_METHOD("wiimote_connect", "timeout"), &GDWiimote::connect);
	ClassDB::bind_method(D_METHOD("poll"), &GDWiimote::poll);
	ClassDB::add_property("GDWiimote", PropertyInfo(Variant::FLOAT, "x"), "", "get_x");//set_x
	ClassDB::add_property("GDWiimote", PropertyInfo(Variant::FLOAT, "y"), "", "get_y");//set_y
	ClassDB::add_property("GDWiimote", PropertyInfo(Variant::FLOAT, "z"), "", "get_z");//set_z
	ClassDB::bind_method(D_METHOD("get_x"), &GDWiimote::get_x);
	ClassDB::bind_method(D_METHOD("get_y"), &GDWiimote::get_y);
	ClassDB::bind_method(D_METHOD("get_z"), &GDWiimote::get_z);
	ClassDB::bind_method(D_METHOD("set_x_sensitivity"), &GDWiimote::set_x_sensitivity);
	ClassDB::bind_method(D_METHOD("set_y_sensitivity"), &GDWiimote::set_y_sensitivity);
	ClassDB::bind_method(D_METHOD("set_z_sensitivity"), &GDWiimote::set_z_sensitivity);


	ClassDB::bind_method(D_METHOD("simulate_data"), &GDWiimote::simulate_data);
}

short any_wiimote_connected(wiimote** wm, int wiimotes) {
	int i;
	if (!wm) {
		return 0;
	}

	for (i = 0; i < wiimotes; i++) {
		if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
			return 1;
		}
	}

	return 0;
}


/**
 *	@brief Callback that handles a disconnection event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *
 *	This can happen if the POWER button is pressed, or
 *	if the connection is interrupted.
 */
void handle_disconnect(wiimote* wm) {
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}


/**
 *	@brief Callback that handles a controller status event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *	@param attachment		Is there an attachment? (1 for yes, 0 for no)
 *	@param speaker			Is the speaker enabled? (1 for yes, 0 for no)
 *	@param ir				Is the IR support enabled? (1 for yes, 0 for no)
 *	@param led				What LEDs are lit.
 *	@param battery_level	Battery level, between 0.0 (0%) and 1.0 (100%).
 *
 *	This occurs when either the controller status changed
 *	or the controller status was requested explicitly by
 *	wiiuse_status().
 *
 *	One reason the status can change is if the nunchuk was
 *	inserted or removed from the expansion port.
 */
void handle_ctrl_status(struct wiimote_t* wm) {
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}


/**
 *	@brief Callback that handles an event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *
 *	This function is called automatically by the wiiuse library when an
 *	event occurs on the specified wiimote.
 */
void handle_event(struct wiimote_t* wm, struct GDWiimote* instance) {
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	/* if a button is pressed, report it */
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
		printf("A pressed\n");
		instance->calibrate();
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		printf("B pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		printf("UP pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN))	{
		printf("DOWN pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
		printf("LEFT pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
		printf("RIGHT pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
		printf("MINUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
		printf("PLUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		printf("ONE pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		printf("TWO pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
		printf("HOME pressed\n");
	}

	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) {
		int i = 0;

		/* go through each of the 4 possible IR sources */
		// for (; i < 4; ++i) {
		// 	/* check if the source is visible */
		// 	if (wm->ir.dot[i].visible) {
		// 		printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
		// 	}
		// }

		instance->set_x(wm->ir.x);
		instance->set_y(wm->ir.y);
		instance->set_z(wm->ir.z);

		// printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
		// printf("IR z distance: %f\n", wm->ir.z);
	}

	/* show events specific to supported expansions */
}


GDWiimote::GDWiimote() {
	// Initialize any variables here.
	// IR dot distance apart
	// 
	// 
	// time_passed = 0.0;
	wiimotes = wiiuse_init(MAX_WIIMOTES);
	time_passed = 0.0;
}

GDWiimote::~GDWiimote() {

	//Disconnect the wiimotes
	wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
}

int GDWiimote::connect(int timeout) {
	/*
	 *	Find wiimote devices
	 *
	 *	Now we need to find some wiimotes.
	 *	Give the function the wiimote array we created, and tell it there
	 *	are MAX_WIIMOTES wiimotes we are interested in.
	 *
	 *	Set the timeout to be 5 seconds.
	 *
	 *	This will return the number of actual wiimotes that are in discovery mode.
	 */
	int found = wiiuse_find(wiimotes, MAX_WIIMOTES, timeout);
	if (!found) {
		printf("No wiimotes found.\n");
		return 0;
	}
	// TODO: connect to a user-chosen wiimote by breaking this out

	/*
	 *	Connect to the wiimotes
	 *
	 *	Now that we found some wiimotes, connect to them.
	 *	Give the function the wiimote array and the number
	 *	of wiimote devices we found.
	 *
	 *	This will return the number of established connections to the found wiimotes.
	 */
	int connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
	if (connected) {
		printf("Connected to %i wiimotes (of %i found).\n", connected, found);
	} else {
		printf("Failed to connect to any wiimote.\n");
		return 0;
	}


	/*
	 *	Now set the LEDs and rumble for a second so it's easy
	 *	to tell which wiimotes are connected (just like the wii does).
	 */
	wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
	// wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_2);
	// wiiuse_set_leds(wiimotes[2], WIIMOTE_LED_3);
	// wiiuse_set_leds(wiimotes[3], WIIMOTE_LED_4);
	wiiuse_rumble(wiimotes[0], 1);
	// wiiuse_rumble(wiimotes[1], 1);

	#ifndef WIIUSE_WIN32
		usleep(200000);
	#else
		Sleep(200);
	#endif

	wiiuse_rumble(wiimotes[0], 0);
	// wiiuse_rumble(wiimotes[1], 0);


	wiiuse_set_ir(wiimotes[0], 1);
	// wiiuse_set_ir(wm, 0);


	return connected;
}

/**
 * @brief Set the offset values to ones that cancel out the current values so that the returned values are "centered" on 0,0,0
 * 
 */
void GDWiimote::calibrate() {
	//struct wiimote_t* wm

	struct wiimote_t* wm = wiimotes[0];

	if (WIIUSE_USING_IR(wm)) {
		set_x(-wm->ir.x);
		set_y(-wm->ir.y);
		set_z(-wm->ir.z);
	}
}

void GDWiimote::start() {

	/*
	 *	This is the main loop
	 *
	 *	wiiuse_poll() needs to be called with the wiimote array
	 *	and the number of wiimote structures in that array
	 *	(it doesn't matter if some of those wiimotes are not used
	 *	or are not connected).
	 *
	 *	This function will set the event flag for each wiimote
	 *	when the wiimote has things to report.
	 */
	while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
		poll();
	}

}

void GDWiimote::poll() {
	if(any_wiimote_connected(wiimotes, MAX_WIIMOTES)){
		if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
			/*
				*	This happens if something happened on any wiimote.
				*	So go through each one and check if anything happened.
				*/
			int i = 0;
			for (; i < MAX_WIIMOTES; ++i) {
				switch (wiimotes[i]->event) {
					case WIIUSE_EVENT:
						/* a generic event occurred */
						handle_event(wiimotes[i], this);
						break;

					case WIIUSE_STATUS:
						/* a status event occurred */
						handle_ctrl_status(wiimotes[i]);
						break;

					case WIIUSE_DISCONNECT:
					case WIIUSE_UNEXPECTED_DISCONNECT:
						/* the wiimote disconnected */
						handle_disconnect(wiimotes[i]);
						break;

					case WIIUSE_READ_DATA:
						/*
							*	Data we requested to read was returned.
							*	Take a look at wiimotes[i]->read_req
							*	for the data.
							*/
						break;

					case WIIUSE_NUNCHUK_INSERTED:
						/*
							*	a nunchuk was inserted
							*	This is a good place to set any nunchuk specific
							*	threshold values.  By default they are the same
							*	as the wiimote.
							*/
						/* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
						/* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
						printf("Nunchuk inserted.\n");
						break;

					case WIIUSE_CLASSIC_CTRL_INSERTED:
						printf("Classic controller inserted.\n");
						break;

					case WIIUSE_WII_BOARD_CTRL_INSERTED:
						printf("Balance board controller inserted.\n");
						break;

					case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
						/* some expansion was inserted */
						handle_ctrl_status(wiimotes[i]);
						printf("Guitar Hero 3 controller inserted.\n");
						break;

					case WIIUSE_MOTION_PLUS_ACTIVATED:
						printf("Motion+ was activated\n");
						break;

					case WIIUSE_NUNCHUK_REMOVED:
					case WIIUSE_CLASSIC_CTRL_REMOVED:
					case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
					case WIIUSE_WII_BOARD_CTRL_REMOVED:
					case WIIUSE_MOTION_PLUS_REMOVED:
						/* some expansion was removed */
						handle_ctrl_status(wiimotes[i]);
						printf("An expansion was removed.\n");
						break;

					default:
						break;
				}
			}
		}
	}

}

void GDWiimote::simulate_data(double delta) {
	time_passed += delta;

	x = 10.0 + (10.0 * sin(time_passed * 2.0));
	y = 10.0 + (10.0 * cos(time_passed * 1.5));
	z = 10.0 + (10.0 * sin(time_passed));
}

void GDWiimote::set_x(const double new_x) {
	x = new_x;
}

double GDWiimote::get_x() {
	return (x + x_offset) * x_sensitivity;
}

void GDWiimote::set_y(const double new_y) {
	y = new_y;
}

double GDWiimote::get_y() {
	return (y + y_offset) * y_sensitivity;
}

void GDWiimote::set_z(const double new_z) {
	z = new_z;
}

double GDWiimote::get_z() {
	return (z + z_offset) * z_sensitivity;
}


void GDWiimote::set_x_sensitivity(const double new_x_sensitivity) {
	x_sensitivity = new_x_sensitivity;
}

void GDWiimote::set_y_sensitivity(const double new_y_sensitivity) {
	y_sensitivity = new_y_sensitivity;
}

void GDWiimote::set_z_sensitivity(const double new_z_sensitivity) {
	z_sensitivity = new_z_sensitivity;
}
