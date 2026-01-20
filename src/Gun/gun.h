#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/input.hpp"
#include"godot_cpp/classes/static_body3d.hpp"
#include "godot_cpp/classes/packed_scene.hpp"

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
	Ref<PackedScene> bullet_res;
	Ref<PackedScene> get_bullet_res();
	void set_bullet_res(Ref<PackedScene> res);

	void print_type(const Variant &p_variant) const;
};
