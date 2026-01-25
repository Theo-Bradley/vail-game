#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/input_event_mouse_motion.hpp"
#include "godot_cpp/core/gdvirtual.gen.inc"

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
	void _ready() override;
	GDVIRTUAL0(_ready);
	void _process(double delta) override;
	GDVIRTUAL1(_process, double);
	void _input(const Ref<InputEvent>& p_event) override;
	GDVIRTUAL1(_input, Ref<InputEvent>);

	void print_type(const Variant &p_variant) const;
};
