#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/ref.hpp>
#include "wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */

namespace godot {

class GDWiimote : public RefCounted {
	GDCLASS(GDWiimote, RefCounted)

private:
	wiimote** wiimotes;

protected:
	static void _bind_methods();

public:
	int x;
	int y;
	int z;
	
	GDWiimote();
	~GDWiimote();
	// find();
	int connect(int timeout);
	void start();
	void poll();

};

}

#endif