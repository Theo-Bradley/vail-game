#include "bullet.h"

void Bullet::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Bullet::print_type);

	ClassDB::bind_method(D_METHOD("set_bullet_speed", "val"), &Bullet::set_bullet_speed);
	ClassDB::bind_method(D_METHOD("get_bullet_speed"), &Bullet::get_bullet_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Bullet Speed"), "set_bullet_speed", "get_bullet_speed");

	ClassDB::bind_method(D_METHOD("set_inital_damage", "val"), &Bullet::set_inital_damage);
	ClassDB::bind_method(D_METHOD("get_inital_damage"), &Bullet::get_inital_damage);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Inital Damage"), "set_inital_damage", "get_inital_damage");

	ClassDB::bind_method(D_METHOD("set_lifetime", "val"), &Bullet::set_lifetime);
	ClassDB::bind_method(D_METHOD("get_lifetime"), &Bullet::get_lifetime);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Lifetime"), "set_lifetime", "get_lifetime");

	ClassDB::bind_method(D_METHOD("set_rb", "ref"), &Bullet::set_rb);
	ClassDB::bind_method(D_METHOD("get_rb"), &Bullet::get_rb);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "RigidBody", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rb", "get_rb");

	ClassDB::bind_method(D_METHOD("body_entered_area", "body"), &Bullet::body_entered_area);
	GDVIRTUAL_BIND(_ready);
	GDVIRTUAL_BIND(_physics_process, "delta");
}

void Bullet::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

void Bullet::_ready()
{
	damage = inital_damage;
	connect("body_entered", Callable(this, "body_entered_area"));
	if (rb != nullptr)
	{
		rb->set_gravity_scale(0.0f);
	}
}

void Bullet::_physics_process(double delta)
{
	//f=m*a
	//v=u+at
	if (!hit && rb != nullptr)
	{
		float a = -(bullet_speed - rb->get_linear_velocity().length()) / delta; //calc acceleration to get to bullet_speed in 1 frame
		rb->apply_central_force(rb->get_transform().get_basis().xform(Vector3(0.0f, 0.0f, rb->get_mass() * a))); //apply to local z
	}
	lifetime -= delta;
	if (lifetime <= 0 && valid)
	{
		valid = false;
		get_parent()->queue_free();
	}
}

void Bullet::body_entered_area(Node3D* body)
{
	hit = true;
	if (body->get_meta("hittable", false) == Variant(true))
		body->call("_on_hit", damage);
		damage *= 0.9; //replace with penetration calc
}

float Bullet::get_bullet_speed()
{
	return bullet_speed;
}

void Bullet::set_bullet_speed(float val)
{
	 bullet_speed = val;
}

float Bullet::get_inital_damage()
{
	return inital_damage;
}

void Bullet::set_inital_damage(float val)
{
	inital_damage = val;
}

void Bullet::set_rb(RigidBody3D* ref)
{
	rb = ref;
}

RigidBody3D* Bullet::get_rb()
{
	return rb;
}

void Bullet::set_lifetime(float val)
{
	lifetime = val;
}

float Bullet::get_lifetime()
{
	return lifetime;
}