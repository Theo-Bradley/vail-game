#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

class AiManager : public Node {
	GDCLASS(AiManager, Node)

protected:
	static void _bind_methods();
	float calculate_interval();
	float interval = 0;

public:
	AiManager() = default;
	~AiManager() override = default;
	void _ready() override;
	void _process(double delta) override;

	int tick_rate = 60;
	void set_tick_rate(int val);
	int get_tick_rate();

	void print_type(const Variant &p_variant) const;
};
