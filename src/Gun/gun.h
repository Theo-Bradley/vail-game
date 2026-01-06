#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/input.hpp"

using namespace godot;

class Gun : public Node3D {
	GDCLASS(Gun, Node3D)

protected:
	static void _bind_methods();

public:
	Gun() = default;
	~Gun() override = default;
	void Shoot();
	void _process(double delta);

	Node3D* muzzle = nullptr;
	Node3D* get_muzzle();
	void set_muzzle(Node3D* ref);
	Node3D* bullet = nullptr;
	Node3D* get_bullet();
	void set_bullet(Node3D* ref);

	void print_type(const Variant &p_variant) const;
};
