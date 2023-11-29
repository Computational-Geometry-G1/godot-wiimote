extends Camera3D

var gdwiimote
var num_connected
# Called when the node enters the scene tree for the first time.
func _ready():
	gdwiimote = GDWiimote.new()
	print("connecting....")
	num_connected = gdwiimote.wiimote_connect(5)
	gdwiimote.set_x_sensitivity(0.5)
	gdwiimote.set_y_sensitivity(0.5)
	gdwiimote.set_z_sensitivity(0.5)
	print("turn on your wiimote now....")
	# pass # Replace with function body.
	if num_connected == 0:
		print("none connected")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if num_connected > 0:
		gdwiimote.poll()
	else:
		gdwiimote.simulate_data(delta)
	#print(gdwiimote.get_x())
	#print(gdwiimote.get_y())
	#print(gdwiimote.get_z())
	#print()
	#print(gdwiimote.x)
	#print(gdwiimote.y)
	#print(gdwiimote.z)
	adjust_camera(gdwiimote.get_x(), gdwiimote.get_y(), gdwiimote.get_z(), true)

var mouse_sens = 0.05
var camera_anglev=0

func adjust_camera(x,y,z, absolute=false):
	if not absolute:
		self.global_position = Vector3(self.global_position.x+x, self.global_position.y+y, self.global_position.z+z)
	else:
		self.global_position = Vector3(x, y, z)
