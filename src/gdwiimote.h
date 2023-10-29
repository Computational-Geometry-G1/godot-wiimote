#ifndef GDWIIMOTE_H
#define GDWIIMOTE_H

#include <godot_cpp/classes/ref.hpp>

namespace godot {

class GDWiimote : public RefCounted {
	GDCLASS(GDWiimote, RefCounted)

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