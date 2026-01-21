#include "Player/player_movement.h"

void PlayerMovement::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PlayerMovement::print_type);

	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &PlayerMovement::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "val"), &PlayerMovement::set_moveSpeed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Max Speed"), "set_moveSpeed", "get_moveSpeed");

	ClassDB::bind_method(D_METHOD("get_moveAccel"), &PlayerMovement::get_moveAccel);
	ClassDB::bind_method(D_METHOD("set_moveAccel", "val"), &PlayerMovement::set_moveAccel);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Acceleration"), "set_moveAccel", "get_moveAccel");

	ClassDB::bind_method(D_METHOD("get_moveFriction"), &PlayerMovement::get_moveFriction);
	ClassDB::bind_method(D_METHOD("set_moveFriction", "val"), &PlayerMovement::set_moveFriction);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Friction"), "set_moveFriction", "get_moveFriction");

	ClassDB::bind_method(D_METHOD("get_playerLook"), &PlayerMovement::get_playerLook);
	ClassDB::bind_method(D_METHOD("set_playerLook", "ref"), &PlayerMovement::set_playerLook);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Player Look", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_playerLook", "get_playerLook");
}

void PlayerMovement::_process(double delta)
{
	#define input Input::get_singleton()

	moveDirection = Vector2(0, 0);
	if (input->is_action_pressed("Left"))
	{moveDirection += Vector2(-1, 0);}
	if (input->is_action_pressed("Right"))
	{moveDirection += Vector2(1, 0);}
	if (input->is_action_pressed("Forward"))
	{moveDirection += Vector2(0, 1);}
	if (input->is_action_pressed("Backward"))
	{moveDirection += Vector2(0, -1);}
}

void PlayerMovement::_physics_process(double delta)
{
	Vector3 u = get_real_velocity(); //inital velocity
	Basis basis = get_basis();
	if (playerLook != nullptr)
		basis = playerLook->get_basis();
	Vector3 am = basis.xform(moveAccel * Vector3(moveDirection.x, 0.0f, -moveDirection.y)); //movement acceleration (-y because +z is into the camera)
	Vector3 af = u.length_squared() > 0.1f ? -u.normalized() * moveFriction * moveAccel * Vector3(1.0f, 0.0f, 1.0f) : Vector3(0.f, 0.f, 0.f); //friction accel (no y friction)
	//if not moving -> no friction
	if (u.x == 0.0f)
		af.x = 0.0f;
	if (u.y == 0.0f)
		af.y = 0.0f;
	if (u.z == 0.0f)
		af.z = 0.0f;
	
	Vector3 v = u + (am + af + get_gravity()) * delta; //calulate v = u + at (where a = am+af+g)
	v = Vector3(Math::clamp(v.x, -moveSpeed, moveSpeed), v.y, Math::clamp(v.z, -moveSpeed, moveSpeed)); //clamp to movespeed on horizontal axis
	set_velocity(v); //set velocity
	move_and_slide(); //move
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

void PlayerMovement::set_playerLook(Node3D* ref)
{
	playerLook = ref;
}

Node3D* PlayerMovement::get_playerLook()
{
	return playerLook;
}

void PlayerMovement::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
