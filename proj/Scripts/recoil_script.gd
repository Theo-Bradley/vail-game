extends Node3D
class_name RecoilScript

@export var recoil = 2.0; # per bullet
@export var recoil_decay = 4.0; # per second
var current_recoil = 0.0;

func _process(delta: float) -> void:
	current_recoil -= recoil_decay * delta;
	current_recoil = clamp(current_recoil, 0.0, Globals.MAX_PITCH/Globals.recoil_strength); #clamp(0, 89.5 degrees)
	
func _on_shoot() -> Array[Vector2]:
	var result: Array[Vector2];
	current_recoil = clamp(current_recoil + recoil, 0.0, Globals.MAX_PITCH/Globals.recoil_strength); #add recoil and clamp
	result.push_back(Vector2(0.0, current_recoil * Globals.recoil_strength)); #calc bullet angle offset
	return result; #in radians
