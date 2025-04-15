#pragma once

#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <limits>
#include <memory>

namespace logic_sim {

	struct sim_node {
		bool state = false;
		bool invalid = true;
	};

	struct sim_graph {

		bool evaluate_node(uint32_t id) const
		{
			// TODO: Think about recursion

			if (!this->nodes.contains(id)) {
				throw; // TODO
			}

			auto &node = this->nodes.at(id);
			if (!node->invalid) {
				return node->state;
			}

			if (!this->node_map_rl.contains(id)) {
				throw; // TODO
			}
			const auto &pns = this->node_map_rl.at(id);
			if (pns.size()!=1) {
				throw; // TODO
			}

			bool state = evaluate_node(pns[0]);
			node->invalid = false;
			node->state = state;
			return state;
		}

		void node_state_override(uint32_t id, bool state)
		{
			if (!this->nodes.contains(id)) {
				throw; // TODO
			}

			auto &node = this->nodes.at(id);
			node->invalid = false;
			node->state = state;
		}

		//template<typename T>
		uint32_t create_node(void)
		{
			uint32_t id = next_id++;
			//nodes[id] = std::make_unique<T>();
			nodes[id] = std::make_unique<sim_node>();
			return id;
		}

		bool remove_node(uint32_t id)
		{
			if (!nodes.contains(id)) {
				return false;
			}

			if (node_map_rl.contains(id)) {
				const auto &list = node_map_rl[id];
				for (auto &el : list) {
					auto &lr = node_map_lr[el];
					auto ix = std::find(lr.begin(), lr.end(), id) - lr.begin();
					lr.erase(std::next(lr.begin(), ix));
				}
				node_map_rl.erase(id);
			}

			if (node_map_lr.contains(id)) {
				const auto &list = node_map_lr[id];
				for (auto &el : list) {
					auto &rl = node_map_rl[el];
					auto ix = std::find(rl.begin(), rl.end(), id) - rl.begin();
					rl.erase(std::next(rl.begin(), ix));
				}
				node_map_lr.erase(id);
			}
		}

		bool map_nodes(uint32_t left, uint32_t right)
		{
			if (!nodes.contains(left) || !nodes.contains(right)) {
				return false;
			}

			node_map_rl[right].emplace_back(left);
			node_map_lr[left].emplace_back(right);

			return true;
		}

	private:
		uint32_t next_id = 1u;

		std::unordered_map<uint32_t, std::unique_ptr<sim_node>> nodes;
		std::unordered_map<uint32_t, std::vector<uint32_t>> node_map_rl; // Right to left
		std::unordered_map<uint32_t, std::vector<uint32_t>> node_map_lr; // Left to right
	};
}
