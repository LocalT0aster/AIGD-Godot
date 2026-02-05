#include "boid.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Boid::_bind_methods() {
}

Boid::Boid() {
	time_passed = 0.0;
}

Boid::~Boid() {}

void Boid::_process(double delta) {
	time_passed += delta;

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	set_position(new_position);
}

void Boid::_enter_tree() {
    if (Engine::get_singleton()->is_editor_hint()) {
        set_process(false);
    }
}
