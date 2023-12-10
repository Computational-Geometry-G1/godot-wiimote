extends Node3D

@onready var _camera := $Camera3D


func _ready() -> void:
	Input.set_mouse_mode(2)

func _input(event: InputEvent) -> void:
	if event is InputEventMouseMotion && Input.get_mouse_mode() == 2:
		_camera.rotate_x(deg_to_rad(-event.relative.y * 0.1))
		rotate_y(deg_to_rad(-event.relative.x * 0.1))
		_camera.rotation_degrees.x = clamp(_camera.rotation_degrees.x,-89.9,89.9)
	
