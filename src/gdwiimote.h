#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/ref.hpp>

namespace godot {

class GDWiimote : public RefCounted {
	GDCLASS(GDWiimote, RefCounted)

private:
	wiimote** wiimotes;

protected:
	static void _bind_methods();

public:
	GDWiimote();
	~GDWiimote();
	// find();
	connect();
	start();
	

	void _process(double delta);
};

}

#endif