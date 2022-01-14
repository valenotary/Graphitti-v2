/**
 *  @file main.cpp
 *  @brief main entrypoint of the graphitti application.
 */

// vcpkg packages 
#include <spdlog/spdlog.h> // logging
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cxxopts.hpp> // command line parsing
#include <veque.hpp> // vector alternative I wanna try out


// standard library stuff
#include <filesystem> // directory manipulation

/**
 *  @brief Graphitti entrypoint. Initializes logger, parses CLA, initializes and runs simulator loop.
 *  
 *  @param argc Argument count detected by CLI
 *  @param argv String arguments passed from the CLI
 *
 *  @return -1 if any exceptions encountered, 0 otherwise
 */
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
        register_logger(combined_general_logger);

        // TODO: create additional logger sinks for different aspects of simulator, such as vertices and edges 

        combined_general_logger->info("Initialized general logger.");
        combined_general_logger->info("Welcome to Graphitti!");

        // initialize command line parser
        cxxopts::Options parser("graphitti", "An accelerated general graph simulator");
        parser.add_options()("c,config", "Model parameters file, inside input/configs/test-name/config.json",
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

        //  TODO: check if files truly exist; we will parse them with flatbuffers later

        //  TODO: create flatbuffers schema for sample input


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
