#include "gun.h"

void Gun::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Gun::print_type);
	
	ClassDB::bind_method(D_METHOD("get_muzzle"), &Gun::get_muzzle);
	ClassDB::bind_method(D_METHOD("set_muzzle", "ref"), &Gun::set_muzzle);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Muzzle", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_muzzle", "get_muzzle");
	ClassDB::bind_method(D_METHOD("get_bullet"), &Gun::get_bullet);
	ClassDB::bind_method(D_METHOD("set_bullet", "ref"), &Gun::set_bullet);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Bullet", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_bullet", "get_bullet");
}

void Gun::Shoot()
{
	Node3D* new_bullet = nullptr;
	#ifdef _DEBUG
	try
	{
		new_bullet = dynamic_cast<Node3D*>(bullet->duplicate());
	}
	catch (std::bad_cast)
	{
		UtilityFunctions::push_warning("Error std::bad_cast on Gun::Shoot::new_bullet!");
	}
	catch (const std::exception& e)
	{
		UtilityFunctions::push_error("Unhandled Exception: " + String((e.what())));
		throw(e);
	}
	#else
	new_bullet = dynamic_cast<Node3D*>(bullet->duplicate());
	#endif
	get_tree()->get_current_scene()->add_child(new_bullet);
	if (muzzle != nullptr)
	{
		new_bullet->set_position(muzzle->get_position());
		new_bullet->set_rotation(muzzle->get_rotation());
	}
	else
	{
		UtilityFunctions::push_warning("Failed to set bullet position! Gun::muzzle is nullptr!");
	}
}

void Gun::_process(double delta)
{
	if (Input::get_singleton()->is_action_just_pressed("Shoot"))
	{
		Shoot();
	}
}

void Gun::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

void Gun::set_muzzle(Node3D* ref)
{
	muzzle = ref;
}

Node3D* Gun::get_muzzle()
{
	return muzzle;
}

void Gun::set_bullet(Node3D* ref)
{
	bullet = ref;
}

Node3D* Gun::get_bullet()
{
	return bullet;
}
