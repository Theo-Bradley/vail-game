#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/input_event_mouse_motion.hpp"

using namespace godot;

class PlayerLook : public Node3D {
	GDCLASS(PlayerLook, Node3D)

protected:
	static void _bind_methods();
	float pitch = 0.0f;
	float yaw = 0.0f;

public:
	PlayerLook() = default;
	~PlayerLook() override = default;
	void _ready();
	void _process(double delta);
	void _input(const Ref<InputEvent> event);

	void print_type(const Variant &p_variant) const;
};
