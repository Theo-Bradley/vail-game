extends StaticBody3D

@export var moveSpeed = 1.0;
var initalized = false;

func _process(_delta: float) -> void:
	if (!initalized): #calculate the global velocity for constant_linear_velocity
		var t = transform;
		t.origin = Vector3.ZERO;
		constant_linear_velocity = (t * Vector3(0.0, 0.0, -moveSpeed));
		initalized = true;

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	translate_object_local(Vector3(0.0, 0.0, -moveSpeed * delta)); #move the object along local -z
