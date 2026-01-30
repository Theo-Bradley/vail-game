extends Node3D
var manager: AiManager;

var safe_velocity: Vector3;
@export var speed: float = 3.0;
@export var target: MousePosNode;
@export var turn_speed: float = deg_to_rad(130);
var physics_delta = 0.0;
var next_pos: Vector3;

#init
func _enter_tree() -> void:
	manager = get_node("%AiManager");
	manager.connect("_ai_tick", _ai_tick);
	(get_child(0) as NavigationAgent3D).target_position = Vector3(0.0, 1.0, 0.0);
	(get_child(0) as NavigationAgent3D).max_speed = speed;
	(get_child(0) as NavigationAgent3D).velocity_computed.connect(Callable(_on_velocity_computed));

#on _ai_tick update the target pos
func _ai_tick() -> void:
	(get_child(0) as NavigationAgent3D).target_position = target.position;
			
#Update player
func _physics_process(delta: float) -> void:
	var nav = (get_child(0) as NavigationAgent3D);
	physics_delta = delta; #used for _on_velocity_computed
	if (nav.is_navigation_finished() != true):
		next_pos = nav.get_next_path_position(); #get next pos
		var dir = next_pos - global_position; #get direction
		dir = dir.normalized();
		
		if (dir.length() > 0):
			var old_forward = (transform.basis * Vector3.FORWARD).normalized();
			var new_forward = (next_pos - position).normalized();
			var total_angle: float = old_forward.angle_to(new_forward); #get unsigned angle between
			var rot_dir = old_forward.cross(new_forward).y; # -1 if cw +1 if ccw
			if (rot_dir != 0): #stop div by 0 error
				rot_dir = rot_dir/abs(rot_dir); #normalize
			var delta_angle = min(total_angle, turn_speed * delta) * rot_dir;
			rotate_y(delta_angle);

			#calc velocity and either set it (let avoidance call velocity_computed signal) or manually call _on_velocity_computed
			var velocity = dir * speed;
			if (nav.avoidance_enabled):
				nav.set_velocity(velocity);
			else:
				_on_velocity_computed(velocity);

func _on_velocity_computed(vel: Vector3) -> void:
	if ((get_child(0) as NavigationAgent3D).is_navigation_finished() != true):
		global_position = global_position.move_toward(next_pos + vel, speed * physics_delta);
