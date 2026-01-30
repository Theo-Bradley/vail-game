class_name MousePosNode
extends Node3D

@export var main_cam: Camera3D;

func _process(delta: float) -> void:
	position = main_cam.project_position(main_cam.get_viewport().get_mouse_position(), main_cam.position.y);
