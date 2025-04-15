#pragma once

#include <elm.hpp>

namespace logic_sim {

	struct app : elm::application
	{
		app(const elm::application_specification &spec,
			elm::application_command_line_args args);
	};
}
