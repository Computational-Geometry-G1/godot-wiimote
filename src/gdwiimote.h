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


protected:
	static void _bind_methods();

public:
	double x;
	godot::Variant y;
	godot::Variant z;
	
	GDWiimote();
	~GDWiimote();
	// find();
	int connect(int timeout);
	void start();
	void poll();

	void _process(double);
	void set_x(const double new_x);
	double get_x();
	void set_y(const godot::Variant new_y);
	godot::Variant get_y();
	void set_z(const godot::Variant new_z);
	godot::Variant get_z();
};

}

#endif