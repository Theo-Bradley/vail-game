extends Node3D
## Calls [signal _hit] signal.
##
## Calls the [signal _hit] signal after [method _on_hit] is called.

## [signal _hit] signal is called when a body enters the Bullet area.
## Connect this signal to the parent's on hit logic.
signal _hit;

## [method _on_hit] is called when a [CollisionObject3D] with metadata [param hittable] = [code]true[/code] enters the area defined by [Bullet]
func _on_hit(damage: float):
	_hit.emit(damage);
