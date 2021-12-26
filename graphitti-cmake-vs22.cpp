// graphitti-cmake-vs22.cpp : Defines the entry point for the application.
//

#include "graphitti-cmake-vs22.h"
#include <sycl.hpp>
#include <sqlite3.h>

// Create an exception handler for asynchronous SYCL exceptions
static auto exception_handler = [](sycl::exception_list e_list) {
	for (std::exception_ptr const &e : e_list) {
		try {
			std::rethrow_exception(e);
		} catch (std::exception const &e) {
#if _DEBUG
			std::cout << "Failure" << std::endl;
#endif
			std::terminate();
		}
	}
};

int main() {
	std::cout << sqlite3_libversion() << '\n';

	try {
		const sycl::queue q(sycl::default_selector{}, exception_handler);

		// Print out the device information used for the kernel code.
		std::cout << "Running on device: "
			<< q.get_device().get_info<sycl::info::device::name>() << "\n";
		std::cout << "Vendor: " << q.get_device().get_info<sycl::info::device::vendor_id>() << '\n';
	} catch (sycl::exception const &e) {
		std::cout << "An exception is caught while adding two vectors.\n";
		std::cout << e.what() << '\n';
		std::terminate();
	}
	sycl::queue myQueue{sycl::gpu_selector{}};
	return 0;
}
