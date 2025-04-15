#include "game_layer.hpp"

#include "simulation/sim_graph.hpp"

namespace logic_sim {

	game_layer::game_layer(void)
		: layer("GameLayer")
	{
	}

	void game_layer::on_attach(void)
	{
		sim_graph sg;
		auto p1 = sg.create_node();
		auto p2 = sg.create_node();
		sg.map_nodes(p1, p2);

		sg.node_state_override(p1, false);

		bool result = sg.evaluate_node(p2);
	}

	void game_layer::on_detach(void)
	{
	}

	void game_layer::on_update(elm::timestep ts)
	{
	}

	void game_layer::on_event(elm::event &e)
	{
	}

	void game_layer::on_imgui_render(void)
	{
	}
}
