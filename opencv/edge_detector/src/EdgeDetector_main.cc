/**
 *       @file  HoughCircles_main.cc
 *      @brief  The HoughCircles BarbequeRTRM application
 *
 * Description: This program demonstrates circle finding with the Hough transform.
 *
 *     @author  Benkhoris Ayoub, ayoub.benkhoris@gmail.com
 *
 *     Company  Politecnico di Milano
 *   Copyright  Copyright (c) 2020, Ayoub Benkhoris
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */

#include <cstdio>
#include <iostream>
#include <random>
#include <cstring>
#include <memory>

#include <libgen.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "version.h"
#include "EdgeDetector_exc.h"
#include <bbque/utils/utility.h>
#include <bbque/utils/logging/logger.h>

// Setup logging
#undef  BBQUE_LOG_MODULE
#define BBQUE_LOG_MODULE "EdgeDetector"

namespace bu = bbque::utils;
namespace po = boost::program_options;

/**
 * @brief A pointer to an EXC
 */
std::unique_ptr<bu::Logger> logger;

/**
 * @brief A pointer to an EXC
 */
typedef std::shared_ptr<BbqueEXC> pBbqueEXC_t;

/**
 * The decription of each EdgeDetector parameters
 */
po::options_description opts_desc("EdgeDetector Configuration Options");

/**
 * The map of all EdgeDetector parameters values
 */
po::variables_map opts_vm;

/**
 * The services exported by the RTLib
 */
RTLIB_Services_t *rtlib;

/**
 * @brief The application configuration file
 */
std::string conf_file = BBQUE_PATH_PREFIX "/" BBQUE_PATH_CONF "/EdgeDetector.conf" ;

/**
 * @brief The recipe to use for all the EXCs
 */
std::string recipe;

/**
 * @brief The image file to process
 */
std::string filename;

/**
 * @brief The EXecution Context (EXC) registered
 */
pBbqueEXC_t pexc;


void ParseCommandLine(int argc, char *argv[]) {
	// Parse command line params
	try {
	po::store(po::parse_command_line(argc, argv, opts_desc), opts_vm);
	} catch(...) {
		std::cout << "Usage: " << argv[0] << " [options]\n";
		std::cout << opts_desc << std::endl;
		::exit(EXIT_FAILURE);
	}
	po::notify(opts_vm);

	// Check for help request
	if (opts_vm.count("help")) {
		std::cout << "Usage: " << argv[0] << " [options]\n";
		std::cout << opts_desc << std::endl;
		::exit(EXIT_SUCCESS);
	}

	// Check for version request
	if (opts_vm.count("version")) {
		std::cout << "EdgeDetector (ver. " << g_git_version << ")\n";
		std::cout << "Copyright (C) 2020 Politecnico di Milano\n";
		std::cout << "\n";
		std::cout << "Built on " <<
			__DATE__ << " " <<
			__TIME__ << "\n";
		std::cout << "\n";
		std::cout << "This is free software; see the source for "
			"copying conditions.  There is NO\n";
		std::cout << "warranty; not even for MERCHANTABILITY or "
			"FITNESS FOR A PARTICULAR PURPOSE.";
		std::cout << "\n" << std::endl;
		::exit(EXIT_SUCCESS);
	}
}

int main(int argc, char *argv[]) {

	opts_desc.add_options()
		("help,h", "print this help message")
		("version,v", "print program version")

		("conf,C", po::value<std::string>(&conf_file)->
			default_value(conf_file),
			"EdgeDetector configuration file")

		("recipe,r", po::value<std::string>(&recipe)->
			default_value("EdgeDetector"),
			"recipe name (for all EXCs)")

		("filename,f", po::value<std::string>(&filename)-> 
			default_value("fruits.jpg"), 
			"Image to process")
	;

	// Setup a logger
	bu::Logger::SetConfigurationFile(conf_file);
	logger = bu::Logger::GetLogger("edgedetector");

	ParseCommandLine(argc, argv);

	// Welcome screen
	logger->Info(".:: EdgeDetector (ver. %s) ::.", g_git_version);
	logger->Info("Built: " __DATE__  " " __TIME__);

	// Initializing the RTLib library and setup the communication channel
	// with the Barbeque RTRM
	logger->Info("STEP 0. Initializing RTLib, application [%s]...",
			::basename(argv[0]));

	if ( RTLIB_Init(::basename(argv[0]), &rtlib) != RTLIB_OK) {
		logger->Fatal("Unable to init RTLib (Did you start the BarbequeRTRM daemon?)");
		return RTLIB_ERROR;
	}

	assert(rtlib);
	logger->Info("STEP 1. Registering EXC with recipe <%s>...", recipe.c_str());
	pexc = std::make_shared<EdgeDetector>("EdgeDetector", recipe, rtlib, filename);
	if (!pexc->isRegistered()) {
		logger->Fatal("Registering failure.");
		return RTLIB_ERROR;
	}


	logger->Info("STEP 2. Starting EXC control thread...");
	pexc->Start();


	logger->Info("STEP 3. Waiting for EXC completion...");
	pexc->WaitCompletion();


	logger->Info("STEP 4. Disabling EXC...");
	pexc = NULL;

	logger->Info("===== EdgeDetector DONE! =====");
	return EXIT_SUCCESS;

}

