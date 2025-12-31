#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/character_body3d.hpp"
#include "godot_cpp/classes/input.hpp"

using namespace godot;

class PlayerMovement : public Node3D {
	GDCLASS(PlayerMovement, Node3D)

protected:
	static void _bind_methods();

public:
	PlayerMovement() = default;
	~PlayerMovement() override = default;
	void _process(double delta);
	void _physics_process(double delta);

	CharacterBody3D* pc = nullptr;
	CharacterBody3D* get_pc();
	void set_pc(CharacterBody3D* ptr);

	void print_type(const Variant &p_variant) const;

private:
	Vector2 moveDirection;
	float moveSpeed = 0.0f;
	float get_moveSpeed();
	void set_moveSpeed(float val);
	float moveAccel = 1.0f;
	float get_moveAccel();
	void set_moveAccel(float val);
	float moveFriction = 0.8f;
	float get_moveFriction();
	void set_moveFriction(float val);
};
