#include "enemy.h"

void Enemy::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Enemy::print_type);
	
	ClassDB::bind_method(D_METHOD("get_target"), &Enemy::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "ref"), &Enemy::set_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Target", PROPERTY_HINT_NODE_TYPE, "MousePosNode"), "set_target", "get_target");
	ClassDB::bind_method(D_METHOD("get_nav_agent"), &Enemy::get_nav_agent);
	ClassDB::bind_method(D_METHOD("set_nav_agent", "ref"), &Enemy::set_nav_agent);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Nav Agent", PROPERTY_HINT_NODE_TYPE, "NavigationAgent3D"), "set_nav_agent", "get_nav_agent");

	ClassDB::bind_method(D_METHOD("_on_ai_tick"), &Enemy::_ai_tick);
	ClassDB::bind_method(D_METHOD("_on_velocity_computed"), &Enemy::_on_velocity_computed);
}

//on _ai_tick update the target pos
void Enemy::_ai_tick()
{
	if (nav_agent != nullptr && target != nullptr)
		nav_agent->set_target_position(target->get_global_position());
}

void Enemy::_enter_tree()
{
	if (nav_agent != nullptr)
	{
		nav_agent->set_target_position(Vector3(0.0, 1.0, 0.0));
		nav_agent->set_max_speed(speed);
		nav_agent->connect("velocity_computed", Callable(this, "_on_velocity_computed"));
	}
	#ifdef _DEBUG
	else
	{
		UtilityFunctions::push_warning("Warning! No NavigationAgent3D found! Enemy_enter_tree()::nav_agent.");
	}
	#endif
	manager = get_node<AiManager>("\045AiManager");
	#ifdef _DEBUG
	if (manager == nullptr)
	{
		UtilityFunctions::push_warning("Warning! No AiManager found!   Enemy_enter_tree()::manager.");
		return;
	}
	#endif
	manager->connect("_ai_tick", Callable(this, "_on_ai_tick"));
	next_pos = get_global_position();
}

void Enemy::_physics_process(double delta)
{
	physics_delta = delta; //used for _on_velocity_computed
	if (nav_agent != nullptr && nav_agent->is_navigation_finished() == false)
	{
		next_pos = nav_agent->get_next_path_position(); //get next position on path to player
		Vector3 dir = (next_pos - get_global_position()).normalized(); //get direction to next position
		if (dir.length() > 0)
		{
			Vector3 old_forward = (get_transform().basis.xform(Vector3(0.0f, 0.0f, -1.0f)).normalized());
			Vector3 new_forward = (next_pos - get_global_position()).normalized();
			float total_angle = old_forward.angle_to(new_forward); //get unsigned angle between forwards in radians
			float rot_dir = old_forward.cross(new_forward).y; //-1 if cw +1 if ccw
			if (rot_dir != 0) //stop div by 0 error
			{
				rot_dir = rot_dir/Math::abs(rot_dir); //normalize to +-1
			}
			
			float delta_angle = Math::min(total_angle, (float)delta * turn_speed) * rot_dir;
			rotate_y(delta_angle);

			//calc velocity and either set it(let avoidance call velocity_computed signal) or manually call _on_velocity_computed
			Vector3 velocity = dir * speed;
			if (nav_agent->get_avoidance_enabled())
				nav_agent->set_velocity(velocity); //this will call _on_velocity_computed once avoidance is complete
			else
				_on_velocity_computed(velocity); //no avoidance to call it so we do it ourselves
		}	
	}
}

void Enemy::_on_velocity_computed(Vector3 safe_velocity)
{
	if (nav_agent != nullptr && nav_agent->is_navigation_finished() == false)
		set_global_position(get_global_position().move_toward(next_pos + safe_velocity, speed * physics_delta));
}

void Enemy::set_target(Node3D* ref)
{
	target = ref;
}

Node3D* Enemy::get_target()
{
	return target;
}

void Enemy::set_nav_agent(NavigationAgent3D* ref)
{
	nav_agent = ref;
}

NavigationAgent3D* Enemy::get_nav_agent()
{
	return nav_agent;
}

void Enemy::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}
