extends GDWiimote

var gdwiimote
var num_connected
# Called when the node enters the scene tree for the first time.
func _ready():
	#gdwiimote = GDWiimote.new()
	print("connecting....")
	num_connected = wiimote_connect(5)
	set_x_sensitivity(0.05)
	set_y_sensitivity(0.05)
	set_z_sensitivity(0.2)
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
		
	#print(delta)
	#print(get_position())
	#print()
	
	
func _input(event: InputEvent) -> void:
	if event.is_action_pressed("calibrate"):
		if num_connected > 0:
			calibrate()
