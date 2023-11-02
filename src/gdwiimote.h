#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/ref.hpp>
#include "wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */

namespace godot {

static class GDWiimote : public RefCounted {
	GDCLASS(GDWiimote, RefCounted)

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