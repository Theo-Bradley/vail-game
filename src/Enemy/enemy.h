#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/navigation_agent3d.hpp"
#include "godot_cpp/core/gdvirtual.gen.inc"
#include "ai_manager.h"

using namespace godot;

class Enemy : public Node3D {
	GDCLASS(Enemy, Node3D)

protected:
	static void _bind_methods();
	AiManager* manager = nullptr;
	NavigationAgent3D* nav_agent = nullptr;
	float physics_delta = 0.0f;

public:
	Enemy() = default;
	~Enemy() override = default;

	virtual void _enter_tree() override;
	virtual void _init_logic();
	GDVIRTUAL0(_init_logic);
	virtual void _ai_tick(double delta);
	GDVIRTUAL1(_ai_tick, double);
	virtual void _physics_process(double delta) override;
	GDVIRTUAL1(_physics_process, double);
	void _on_velocity_computed(Vector3 safe_velocity);

	void print_type(const Variant &p_variant) const;

	float speed = 3.0f;
	float turn_speed = Math::deg_to_rad(130.f);
	Vector3 next_pos;
	Node3D* target = nullptr;
	Node3D* get_target();
	void set_target(Node3D* ref);
	NavigationAgent3D* get_nav_agent();
	void set_nav_agent(NavigationAgent3D* ref);
};
