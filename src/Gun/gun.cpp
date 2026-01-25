#include "gun.h"
#include "godot_cpp/classes/resource_loader.hpp"

void Gun::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Gun::print_type);
	
	ClassDB::bind_method(D_METHOD("get_muzzle"), &Gun::get_muzzle);
	ClassDB::bind_method(D_METHOD("set_muzzle", "ref"), &Gun::set_muzzle);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Muzzle", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_muzzle", "get_muzzle");

	ClassDB::bind_method(D_METHOD("get_bullet_res"), &Gun::get_bullet_res);
	ClassDB::bind_method(D_METHOD("set_bullet_res", "res"), &Gun::set_bullet_res);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Bullet Resource", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_bullet_res", "get_bullet_res");

	ClassDB::bind_method(D_METHOD("shoot"), &Gun::shoot);
	GDVIRTUAL_BIND(_process, "delta");
}

void Gun::shoot()
{
	if (bullet_res == nullptr)
	{
		#ifdef _DEBUG
		UtilityFunctions::push_warning("Error nullptr Gun::Shoot::bullet_res!");
		#endif
		return;
	}
	Array shots = get_child(0)->call("_on_shoot");
	
	TypedArray<Vector2>::Iterator it;
	for (it = shots.begin(); it != shots.end(); ++it) //loop over result from recoil script
	{
		//spawn bullet
		Node3D* new_bullet = nullptr;
		#ifdef _DEBUG
		try
		{
			new_bullet = dynamic_cast<Node3D*>(bullet_res->instantiate()); //copy bullet_res
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
		new_bullet = dynamic_cast<Node3D*>(bullet_res->instantiate()); //copy bullet_res
		#endif
		get_tree()->get_current_scene()->add_child(new_bullet); //add new bullet to scene root
		if (muzzle != nullptr)
		{
			//set bullet pos rot to muzzle pos rot
			new_bullet->set_position(muzzle->get_global_position());
			new_bullet->set_rotation(muzzle->get_global_rotation() + Vector3(Vector2(*it).y, Vector2(*it).x, 0.0f));
		}
		#ifdef _DEBUG
		else
		{
			UtilityFunctions::push_warning("Failed to set bullet position! Gun::muzzle is nullptr!");
		}
		#endif
	}
}

void Gun::_process(double delta)
{
	if (Input::get_singleton()->is_action_just_pressed("Shoot"))
	{
		shoot();
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

Ref<PackedScene> Gun::get_bullet_res()
{
	return bullet_res;
}

void Gun::set_bullet_res(Ref<PackedScene> res)
{
	bullet_res = res;
}