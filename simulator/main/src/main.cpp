//#include <sycl.hpp>
//#include <cxxopts.hpp>
//#include <spdlog/spdlog.h>
//#include <array>
//#include <iostream>
//#include <typeinfo>
//#include <string>
//#include <core_test.hpp>
//#include <veque.hpp>
//#include <filesystem>
//#if FPGA || FPGA_EMULATOR
//#include <sycl/ext/intel/fpga_extensions.hpp>
//#endif
//
//using namespace sycl;
//
//
//class CUDASelector : public sycl::device_selector {
//    public:
//    int operator()(const sycl::device &Device) const override {
//        using namespace sycl::info;
//        const std::string DriverVersion = Device.get_info<sycl::info::device::driver_version>();
//
//        if (Device.is_gpu() && (DriverVersion.find("CUDA") != std::string::npos)) {
//            std::cout << " CUDA device found " << std::endl;
//            return 1;
//        };
//        return -1;
//    }
//};
//
//// Array size for this example.
//size_t array_size = 10000;
//
//// Create an exception handler for asynchronous SYCL exceptions
//static auto exception_handler = [](sycl::exception_list e_list) {
//    for (std::exception_ptr const &e : e_list) {
//        try { std::rethrow_exception(e); }
//        catch (std::exception const &e) {
//#if _DEBUG
//			std::cout << "Failure" << std::endl;
//#endif
//            std::terminate();
//        }
//    }
//};
//
////************************************
//// Vector add in DPC++ on device: returns sum in 4th parameter "sum".
////************************************
//void VectorAdd(queue &q, const int *a, const int *b, int *sum, size_t size) {
//    // Create the range object for the arrays.
//    range<1> num_items{size};
//
//    // Use parallel_for to run vector addition in parallel on device. This
//    // executes the kernel.
//    //    1st parameter is the number of work items.
//    //    2nd parameter is the kernel, a lambda that specifies what to do per
//    //    work item. the parameter of the lambda is the work item id.
//    // DPC++ supports unnamed lambda kernel by default.
//    auto e = q.parallel_for(num_items, [=](auto i) { sum[i] = a[i] + b[i]; });
//
//    // q.parallel_for() is an asynchronous call. DPC++ runtime enqueues and runs
//    // the kernel asynchronously. Wait for the asynchronous call to complete.
//    e.wait();
//}
//
////************************************
//// Initialize the array from 0 to array_size - 1
////************************************
//void InitializeArray(int *a, size_t size) { for (size_t i = 0; i < size; i++) a[i] = i; }
//
////************************************
//// Demonstrate vector add both in sequential on CPU and in parallel on device.
////************************************
//int main(int argc, char *argv[]) {
//    // Change array_size if it was passed as argument
//    if (argc > 1) array_size = std::stoi(argv[1]);
//
//    veque::veque<int> test_veque;
//
//    spdlog::info("whats up my dudes");
//    cxxopts::Options parser("graphitti", "an accelerated general graph simulator");
//    parser.add_options()
//        ("f,filename", "Input model parameters file", cxxopts::value<std::string>()->default_value("fkasldj"))
//        ("h,help", "Print usage");
//    std::cout << return5() << '\n';
//    try {
//        const auto parser_result = parser.parse(argc, argv);
//        if (parser_result.count("help")) {
//            std::cout << parser.help() << '\n';
//            std::exit(0);
//        }
//
//        std::cout << parser_result["filename"].as<std::string>() << '\n';
//    }
//    catch (cxxopts::OptionException &e) { std::cout << e.what() << '\n'; }
//    // Create device selector for the device of your interest.
//#if FPGA_EMULATOR
//  // DPC++ extension: FPGA emulator selector on systems without FPGA card.
//	ext::intel::fpga_emulator_selector d_selector;
//#elif FPGA
//  // DPC++ extension: FPGA selector on systems with FPGA card.
//	ext::intel::fpga_selector d_selector;
//#else
//    // The default device selector will select the most performant device.
//    CUDASelector d_selector{};
//#endif
//
//    std::cout << typeid(CUDASelector).name() << '\n';
//
//    try {
//        queue q(d_selector, exception_handler);
//
//        // Print out the device information used for the kernel code.
//        std::cout << "Running on device: "
//            << q.get_device().get_info<info::device::name>() << "\n";
//        std::cout << "Vendor: " << q.get_device().get_info<info::device::vendor_id>() << '\n';
//        std::cout << "Vector size: " << array_size << "\n";
//
//        // Create arrays with "array_size" to store input and output data. Allocate
//        // unified shared memory so that both CPU and device can access them.
//        int *a = malloc_shared<int>(array_size, q);
//        int *b = malloc_shared<int>(array_size, q);
//        int *sum_sequential = malloc_shared<int>(array_size, q);
//        int *sum_parallel = malloc_shared<int>(array_size, q);
//
//        if ((a == nullptr) || (b == nullptr) || (sum_sequential == nullptr) ||
//            (sum_parallel == nullptr)) {
//            if (a != nullptr) free(a, q);
//            if (b != nullptr) free(b, q);
//            if (sum_sequential != nullptr) free(sum_sequential, q);
//            if (sum_parallel != nullptr) free(sum_parallel, q);
//
//            std::cout << "Shared memory allocation failure.\n";
//            return -1;
//        }
//
//        // Initialize input arrays with values from 0 to array_size - 1
//        InitializeArray(a, array_size);
//        InitializeArray(b, array_size);
//
//        // Compute the sum of two arrays in sequential for validation.
//        for (size_t i = 0; i < array_size; i++) sum_sequential[i] = a[i] + b[i];
//
//        // Vector addition in DPC++.
//        VectorAdd(q, a, b, sum_parallel, array_size);
//
//        // Verify that the two arrays are equal.
//        for (size_t i = 0; i < array_size; i++) {
//            if (sum_parallel[i] != sum_sequential[i]) {
//                std::cout << "Vector add failed on device.\n";
//                return -1;
//            }
//        }
//
//        int indices[]{0, 1, 2, (static_cast<int>(array_size) - 1)};
//        constexpr size_t indices_size = sizeof(indices) / sizeof(int);
//
//        // Print out the result of vector add.
//        for (int i = 0; i < indices_size; i++) {
//            int j = indices[i];
//            if (i == indices_size - 1) std::cout << "...\n";
//            std::cout << "[" << j << "]: " << j << " + " << j << " = "
//                << sum_sequential[j] << "\n";
//        }
//
//        free(a, q);
//        free(b, q);
//        free(sum_sequential, q);
//        free(sum_parallel, q);
//    }
//    catch (exception const &e) {
//        std::cout << "An exception is caught while adding two vectors.\n";
//        std::cout << e.what() << '\n';
//        std::terminate();
//    }
//
//    std::cout << "Vector add successfully completed on device.\n";
//    return 0;
//}

// vcpkg packages 
#include <spdlog/spdlog.h> // logging
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <cxxopts.hpp> // command line parsing
#include <veque.hpp> // vector alternative I wanna try out


// standard library stuff
#include <filesystem> // directory manipulation


/// <summary> Graphitti main entrypoint.</summary>
/// <param name="argc">Number of arguments provided from the command line.</param>
/// <param name="argv">String arguments provided from the command line.</param>
/// <returns> -1 in an event of a failure, 0 otherwise. </returns>
int main(int argc, char **argv) {

    const std::filesystem::path input_dir("../../input");
    const std::filesystem::path output_dir("../../output");
    const std::filesystem::path logs_dir(output_dir.string() + "/logs");

    try {
        // initialize loggers
        veque::veque<spdlog::sink_ptr> general_log_sinks;
        general_log_sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        general_log_sinks.push_back(
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(logs_dir.string() + "/general_logs.txt"));
        const auto combined_general_logger = std::make_shared<spdlog::logger>(
            "combined_general_logger", general_log_sinks.begin(), general_log_sinks.end());
        spdlog::register_logger(combined_general_logger);

        // TODO: create additional logger sinks for different aspects of simulator, such as vertices and edges 

        combined_general_logger->info("Initialized general logger.");
        combined_general_logger->info("Welcome to Graphitti!");

        // initialize command line parser
        cxxopts::Options parser("graphitti", "An accelerated general graph simulator");
        parser.add_options()("c,config", "Model parameters file, inside input/config/name.json",
                             cxxopts::value<std::string>())(
                "i,input-saved-run",
                "Resume the simulator with a serialized file that was generated previously from a config",
                cxxopts::value<std::string>()) //  if not defined, then we just do a fresh run
            ("s,output-saved-run", "Model parameters will be saved to input/saves/name.json",
             cxxopts::value<std::string>()->default_value(
                 "save_output.json")) //    TODO: dynamically generate a unique default name
            ("o,output", "Simulator results and logs will be saved to output/<results,logs>/name.<txt,hdf5>.",
             cxxopts::value<std::string>()->default_value("run_title"))
            //  TODO: dynamically generate a unique default name
            ("h,help", "Print usage");

        combined_general_logger->info("Parsing arguments");
        const auto parser_result = parser.parse(argc, argv);
        if (parser_result.count("help")) {
            //  print help message
            combined_general_logger->info("Only printing help. Exiting...");
            std::cout << parser.help() << '\n';
            return 0;
        }

        //  throw an exception if we cannot find a config flag
        if (!parser_result.count("config")) {
            combined_general_logger->error("No input config file found!");
            throw cxxopts::OptionSpecException("No input config file found.");
        }

        //  TODO: parse the rest of the arguments into appropriate variables

        // TODO: check if files truly exist; we will parse them with flatbuffers later

        // TODO: create flatbuffers schema for sample input 

        //  TODO: rename log files to unique run name, so that they do not rewrite one another with the same name


    }
    catch (const cxxopts::OptionException &ex) {
        std::cout << "Error parsing command line: " << ex.what() << '\n';
        return -1;
    }
    catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Error in log initialization: " << ex.what() << '\n';
        return -1;
    }
    return 0;
}
