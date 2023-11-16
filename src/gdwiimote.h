#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/node3d.hpp>
#include "wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */

namespace godot {

class GDWiimote : public Node3D {
	GDCLASS(GDWiimote, Node3D)

private:
	wiimote** wiimotes;
	double time_passed;

	double x_offset;
	double y_offset;
	double z_offset;

protected:
	static void _bind_methods();

public:
	double x;
	double y;
	double z;
	
	GDWiimote();
	~GDWiimote();
	// find();
	int connect(int timeout);
	void start();
	void poll();
	void simulate_data(double);
	

	void set_x(const double new_x);
	double get_x();
	void set_y(const double new_y);
	double get_y();
	void set_z(const double new_z);
	double get_z();
};

}

#endif