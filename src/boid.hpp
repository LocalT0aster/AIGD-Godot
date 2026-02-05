#pragma once

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Boid : public Sprite2D {
	GDCLASS(Boid, Sprite2D)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	Boid();
	~Boid();

	void _process(double delta) override;
    void _enter_tree() override;
};

}
