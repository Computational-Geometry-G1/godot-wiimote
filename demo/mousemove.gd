extends Camera3D


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


var mouse_sens = 0.05
var camera_anglev=0

func _input(event):         
	if event is InputEventMouseMotion:

		var x = -event.relative.x*mouse_sens
		var y = -event.relative.y*mouse_sens
		print(x)
		print(y)
		print()
		var z = 0
		self.global_position = Vector3(self.global_position.x+x, self.global_position.y+y, self.global_position.z+z)
