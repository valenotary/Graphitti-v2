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
    }
}

#endif
