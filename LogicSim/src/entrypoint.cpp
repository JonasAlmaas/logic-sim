#include "app.hpp"
#include <elm.hpp>
#include <elm/core/entypoiny.hpp>

namespace elm {

	application* application::create(struct application_command_line_args args)
	{
		elm::application_specification spec;
		spec.name = "LogicSim";
		return new app(spec, args);
	}
}
