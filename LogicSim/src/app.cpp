#include "app.hpp"
#include "game_layer.hpp"

app::app(const elm::application_specification &spec, elm::application_command_line_args args)
	: elm::application(spec, args)
{
	push_layer(new game_layer());
}
