#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/character_body3d.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/core/gdvirtual.gen.inc"

using namespace godot;

class PlayerMove : public CharacterBody3D {
	GDCLASS(PlayerMove, CharacterBody3D)

protected:
	static void _bind_methods();

public:
	PlayerMove() = default;
	~PlayerMove() override = default;
	void _process(double delta) override;
	GDVIRTUAL1(_process, double);
	void _physics_process(double delta) override;
	GDVIRTUAL1(_physics_process, double);

	void print_type(const Variant &p_variant) const;

private:
	Vector2 moveDirection;
	float moveSpeed = 6.0f;
	float get_moveSpeed();
	void set_moveSpeed(float val);
	float moveAccel = 60.0f;
	float get_moveAccel();
	void set_moveAccel(float val);
	float moveFriction = 8.0f;
	float get_moveFriction();
	void set_moveFriction(float val);
	Node3D* playerLook = nullptr;
	void set_playerLook(Node3D* ref);
	Node3D* get_playerLook();
};
