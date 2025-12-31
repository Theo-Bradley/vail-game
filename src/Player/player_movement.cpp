#include "Player/player_movement.h"

void PlayerMovement::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PlayerMovement::print_type);

	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &PlayerMovement::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "val"), &PlayerMovement::set_moveSpeed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Move Speed"), "set_moveSpeed", "get_moveSpeed");

	ClassDB::bind_method(D_METHOD("get_moveAccel"), &PlayerMovement::get_moveAccel);
	ClassDB::bind_method(D_METHOD("set_moveAccel", "val"), &PlayerMovement::set_moveAccel);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Move Acceleration"), "set_moveAccel", "get_moveAccel");

	ClassDB::bind_method(D_METHOD("get_moveFriction"), &PlayerMovement::get_moveFriction);
	ClassDB::bind_method(D_METHOD("set_moveFriction", "val"), &PlayerMovement::set_moveFriction);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Friction"), "set_moveFriction", "get_moveFriction");

	ClassDB::bind_method(D_METHOD("get_pc"), &PlayerMovement::get_pc);
	ClassDB::bind_method(D_METHOD("set_pc", "ptr"), &PlayerMovement::set_pc);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Player Controller", PROPERTY_HINT_NODE_TYPE, "CharacterBody3D"), "set_pc", "get_pc");
}

void PlayerMovement::_process(double delta)
{
	#define input Input::get_singleton()

	moveDirection = Vector2(0, 0);
	if (input->is_action_pressed("Left"))
	{
		moveDirection += Vector2(-1, 0);
	}

	if (input->is_action_pressed("Right"))
	{
		moveDirection += Vector2(1, 0);
	}
}

void PlayerMovement::_physics_process(double delta)
{
	if (pc != nullptr)
	{
		//make sure v is never greater than moveSpeed
		/*
		float v = u + moveAccel * moveDirection.x * delta;
		v = Math::clamp(v, -moveSpeed, moveSpeed);
		float a = ((v * Math::abs(moveDirection.x)) - u)/delta;
		print_line("V: ", v, " U: ", u);
		pc->set_velocity(Vector3(u + (a * delta), 0.f, 0.f)); //apply force
		pc->move_and_slide();
		*/
		Vector3 u = pc->get_real_velocity();
		Vector3 a = moveAccel * Vector3(moveDirection.x, -9.81, 0.0f);
		Vector3 af = -u.normalized() * moveFriction * moveAccel;
		if (u.x == 0.0f)
			af.x = 0.0f;
		Vector3 v = u + (a + af) * (float)delta;
		pc->set_velocity(Vector3(Math::clamp(v.x, -moveSpeed, moveSpeed), v.y, Math::clamp(v.z, -moveSpeed, moveSpeed)));
		pc->move_and_slide();
		print_line("A: ", a, " Af ", af, " U: ", u);
	}
}

CharacterBody3D* PlayerMovement::get_pc()
{
	return pc;
}

void PlayerMovement::set_pc(CharacterBody3D* ptr)
{
	pc = ptr;
}

float PlayerMovement::get_moveSpeed()
{
	return moveSpeed;
}

void PlayerMovement::set_moveSpeed(float val)
{
	moveSpeed = val;
}


float PlayerMovement::get_moveAccel()
{
	return moveAccel;
}

void PlayerMovement::set_moveAccel(float val)
{
	moveAccel = val;
}

float PlayerMovement::get_moveFriction()
{
	return moveFriction;
}

void PlayerMovement::set_moveFriction(float val)
{
	moveFriction = val;
}

void PlayerMovement::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
