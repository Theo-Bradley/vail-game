#include "ai_manager.h"

void AiManager::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &AiManager::print_type);

	ClassDB::bind_method(D_METHOD("set_tick_rate", "val"), &AiManager::set_tick_rate);
	ClassDB::bind_method(D_METHOD("get_tick_rate"), &AiManager::get_tick_rate);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Ai Tick Rate"), "set_tick_rate", "get_tick_rate");

	ADD_SIGNAL(MethodInfo("_ai_tick"));
}

void AiManager::_ready()
{
	interval = calculate_interval();
}

void AiManager::_process(double delta)
{
	interval -= delta;
	if (interval <= 0.0f)
	{
		emit_signal("_ai_tick", delta);
		interval = calculate_interval();
	}
}

float AiManager::calculate_interval()
{
	return 1.0f/tick_rate;
}

int AiManager::get_tick_rate()
{
	return tick_rate;
}

void AiManager::set_tick_rate(int val)
{
	tick_rate = val;
	interval = calculate_interval(); //recalc interval to first tick doesn't wait for last tick at old interval
}

void AiManager::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}
