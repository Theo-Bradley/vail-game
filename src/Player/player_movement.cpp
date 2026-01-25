#include "Player/player_movement.h"

void PlayerMove::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PlayerMove::print_type);

	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &PlayerMove::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "val"), &PlayerMove::set_moveSpeed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Max Speed"), "set_moveSpeed", "get_moveSpeed");

	ClassDB::bind_method(D_METHOD("get_moveAccel"), &PlayerMove::get_moveAccel);
	ClassDB::bind_method(D_METHOD("set_moveAccel", "val"), &PlayerMove::set_moveAccel);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Acceleration"), "set_moveAccel", "get_moveAccel");

	ClassDB::bind_method(D_METHOD("get_moveFriction"), &PlayerMove::get_moveFriction);
	ClassDB::bind_method(D_METHOD("set_moveFriction", "val"), &PlayerMove::set_moveFriction);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Friction"), "set_moveFriction", "get_moveFriction");

	ClassDB::bind_method(D_METHOD("get_playerLook"), &PlayerMove::get_playerLook);
	ClassDB::bind_method(D_METHOD("set_playerLook", "ref"), &PlayerMove::set_playerLook);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Player Look", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_playerLook", "get_playerLook");

	GDVIRTUAL_BIND(_process, "delta");
	GDVIRTUAL_BIND(_physics_process, "delta");
}

void PlayerMove::_process(double delta)
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

void PlayerMove::_physics_process(double delta)
{
	Vector3 u = get_real_velocity(); //inital velocity
	Basis basis = get_basis(); //get basis so we can make forces local
	if (playerLook != nullptr) //if we have playerlook, we can get it's basis instead
		basis = playerLook->get_basis(); //this makes the forces local to the PlayerLook instead of this class
	Vector3 am = basis.xform(moveAccel * Vector3(moveDirection.x, 0.0f, -moveDirection.y)); //movement acceleration (-y because +z is into the camera)
	Vector3 af = u.length_squared() > 0.1f ? -u.normalized() * moveFriction * Vector3(1.0f, 0.0f, 1.0f) : Vector3(0.f, 0.f, 0.f); //friction accel (no y friction)
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

float PlayerMove::get_moveSpeed()
{
	return moveSpeed;
}

void PlayerMove::set_moveSpeed(float val)
{
	moveSpeed = val;
}


float PlayerMove::get_moveAccel()
{
	return moveAccel;
}

void PlayerMove::set_moveAccel(float val)
{
	moveAccel = val;
}

float PlayerMove::get_moveFriction()
{
	return moveFriction;
}

void PlayerMove::set_moveFriction(float val)
{
	moveFriction = val;
}

void PlayerMove::set_playerLook(Node3D* ref)
{
	playerLook = ref;
}

Node3D* PlayerMove::get_playerLook()
{
	return playerLook;
}

void PlayerMove::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
