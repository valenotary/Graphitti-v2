/**
 *	@file simulator.hpp
 *
 *	@brief Graphitti Simulator static class.
 *
 *	@ingroup Graphitti/Core/
 *
 */

#ifndef GRAPHITTI_MAIN_SIMULATOR_HPP
#define GRAPHITTI_MAIN_SIMULATOR_HPP

#include <utility>
#include <vector>

namespace graphitti {
    namespace main {
        class Simulator final { // no one should try to inherit from this...
            public:
            Simulator() = delete;
            Simulator(const Simulator &) = delete;
            Simulator &operator=(const Simulator &) = delete;
            Simulator(const Simulator &&) = delete;
            Simulator &operator=(Simulator &&) = delete;
            ~Simulator() = default;

            private:
        };

        template <typename T>
        struct Vertex {};

        struct Vertex911 final : Vertex<Vertex911> {
            size_t num_callers_;
            std::pair<size_t, size_t> min_max_callers_;
        };

        std::vector<Vertex911> vertices;

        template <typename T>
        struct Graph {
            template <typename U>
            struct Node {};
        };

        struct DerivedGraph final : Graph<DerivedGraph> {
            struct DerivedNode final : Node<DerivedNode> {};
        };
    } // namespace main
} // namespace graphitti

#endif
