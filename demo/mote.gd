extends GDWiimote

var gdwiimote
var num_connected
# Called when the node enters the scene tree for the first time.
func _ready():
	#gdwiimote = GDWiimote.new()
	print("connecting....")
	num_connected = wiimote_connect(5)
	set_x_sensitivity(0.5)
	set_y_sensitivity(0.5)
	set_z_sensitivity(0.5)
	print("turn on your wiimote now....")
	# pass # Replace with function body.
	if num_connected == 0:
		print("none connected")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if num_connected > 0:
		poll()
	else:
		simulate_data(delta)
		
	print(delta)
	print(position)
	print(get_position())
	print(get_global_position())
	set_global_position(get_position())
	print(get_x())
	print(get_y())
	print(get_x())
	print()
