#include "player_look.h"

void PlayerLook::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PlayerLook::print_type);
	GDVIRTUAL_BIND(_ready);
	GDVIRTUAL_BIND(_process, "delta");
	GDVIRTUAL_BIND(_input, "p_event");
}

void PlayerLook::_input(const Ref<InputEvent>& p_event)
{
	if (p_event->get_class() == "InputEventMouseMotion")
	{
		Vector2 sensitivity = get_node<Node>(NodePath("/root/Globals"))->get("sensitivity"); //get mouse sensitivity from Globals.gd
		yaw += ((Ref<InputEventMouseMotion>)p_event)->get_screen_relative().x * sensitivity.x * -1.f; //increment pitch and yaw
		pitch += ((Ref<InputEventMouseMotion>)p_event)->get_screen_relative().y * sensitivity.y * -1.f; //..
	}
}

void PlayerLook::_ready()
{
	Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}

void PlayerLook::_process(double delta)
{
	Vector3 old = get_rotation_degrees();
	set_rotation_degrees(Vector3(old.x + pitch, old.y + yaw, 0.0f)); //rotate by pitch and yaw
	pitch = 0.0f; //reset for next frame
	yaw = 0.0f;
	if (Input::get_singleton()->is_action_just_pressed("Release_Mouse"))
	{
		Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
	}
}

void PlayerLook::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
