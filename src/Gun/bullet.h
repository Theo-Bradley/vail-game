#pragma once

#include "godot_cpp/classes/area3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"

using namespace godot;

class Bullet : public Area3D {
	GDCLASS(Bullet, Area3D)

protected:
	static void _bind_methods();
	float bullet_speed = 0.0f;
	void set_bullet_speed(float val);
	float get_bullet_speed();
	float inital_damage = 0.0f;
	void set_inital_damage(float val);
	float get_inital_damage();
	bool hit = false;
	float damage = 0.0f;
	RigidBody3D* rb = nullptr;
	void set_rb(RigidBody3D* ref);
	RigidBody3D* get_rb();

public:
	Bullet() = default;
	~Bullet() override = default;

	void _ready();
	void _physics_process(double delta);
	void body_entered_area(Node3D* body);

	void print_type(const Variant &p_variant) const;
};
