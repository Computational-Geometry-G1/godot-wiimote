extends GDWiimote



@onready var _camera := $Camera3D

var gdwiimote
var num_connected
# Called when the node enters the scene tree for the first time.
func _ready():
	#gdwiimote = GDWiimote.new()
	print("connecting....")
	num_connected = wiimote_connect(5)
	set_x_sensitivity(0.02)
	set_y_sensitivity(0.02)
	set_z_sensitivity(0.02)
	print("turn on your wiimote now....")
	# pass # Replace with function body.
	if num_connected == 0:
		print("none connected - falling back to mouse data")
		Input.set_mouse_mode(2)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if num_connected > 0:
		poll()
	
		
		print(delta)
		print(get_position())
		print()


func _input(event: InputEvent) -> void:
	if num_connected == 0:
		if event is InputEventMouseMotion && Input.get_mouse_mode() == 2:
			_camera.rotate_x(deg_to_rad(-event.relative.y * 0.1))
			rotate_y(deg_to_rad(-event.relative.x * 0.1))
			_camera.rotation_degrees.x = clamp(_camera.rotation_degrees.x,-89.9,89.9)
	
