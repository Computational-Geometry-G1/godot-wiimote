#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class GDWiimote : public Sprite2D {
	GDCLASS(GDWiimote, Sprite2D)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	GDWiimote();
	~GDWiimote();

	void _process(double delta);
};

}

#endif