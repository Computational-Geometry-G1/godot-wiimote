#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/node3d.hpp>
#include "wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */

namespace godot {

class GDWiimote : public Node3D {
	GDCLASS(GDWiimote, Node3D)

private:
	wiimote** wiimotes;

protected:
	static void _bind_methods();

public:
	GDWiimote();
	~GDWiimote();
	// find();
	int connect();
	void start();

};

}

#endif