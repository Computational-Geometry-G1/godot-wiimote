extends Node2D


func _on_targets_pressed():
	get_tree().change_scene_to_file("res://targets.tscn")

func _on_stadium_pressed():
	get_tree().change_scene_to_file("res://picture.tscn")

func _on_quit_pressed():
	get_tree().quit()
