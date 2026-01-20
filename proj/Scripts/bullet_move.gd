extends Area3D

@export var moveSpeed = 1.0;
@export var inital_damage: float = 0.0;
var damage = 0.0;
var hit: bool = false;


func _ready() -> void:
		#var t = transform;
		#t.origin = Vector3.ZERO;
		#constant_linear_velocity = (t * Vector3(0.0, 0.0, -moveSpeed));
		damage = inital_damage;
		connect("body_entered", body_entered_area);

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	if (!hit):
		translate_object_local(Vector3(0.0, 0.0, -moveSpeed * delta)); #move the object along local -z

func body_entered_area(body: Node3D):
	hit = true;
	if (body.get_meta("hittable", false) == true):
		body.call("_on_hit", damage);
		damage -= 0.1; #replace with penetration calc
