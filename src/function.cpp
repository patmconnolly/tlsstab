// Library of functions to use as to not clutter up main.
// Copyright(C) 2025 Patrick Connolly
//
// This program is free software : you can redistribute it and /or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 3 of the License.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.

#include <iostream>
#include <string>
#include <fstream>

#include "function.hpp"
#include "version.hpp"

// Add function defenitions here.
namespace function {
	void info(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_INFO + str + str2 + str3;
		if (not function::SILENT) {
			std::cout << output << std::endl;
		}
	}

	void debug(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_DEBU + str + str2 + str3;
		if (not function::SILENT) {
			if (function::DEBUG) { std::cerr << output << std::endl; }
		}
	}

	void error(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_ERRR + str + str2 + str3;
		if (not function::SILENT) {
			std::cerr << output << std::endl;
		}
	}

	void warning(std::string str, std::string str2, std::string str3)
	{
		std::string output = function::HEADER_WARN + str + str2 + str3;
		if (not function::SILENT) {
			if (function::DEBUG) { std::cerr << output << std::endl; }
		}
	}

	void version_message() {
		function::KILL = true;
		function::debug("Displaying Version Information");
		std::cout << "Compiled and packaged on " << COMPILE_DATE << " at " << COMPILE_TIME << " UTC from the " << COMPILE_BRANCH << " branch." << std::endl;
		std::cout << "TLSStab version: " << COMPILE_BRANCH << "-" << COMPILE_DATE << std::endl;
		return;
	}

	void help_message() {
		function::KILL = true;
		function::debug("Displaying Help Message");
		std::cout << "TLSStab Copyright (C) 2025 Patrick Connolly" << std::endl;
		std::cout << "This program comes with ABSOLUTELY NO WARRANTY." << std::endl;
		std::cout << "This is free software, and you are welcome to redistribute it under certain conditions." << std::endl;
		std::cout << "You should have received a copy of the GNU General Public License v3 along with this program." << std::endl;
		std::cout << "If not, see <https://www.gnu.org/licenses/>." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "TLSStab Usage" << std::endl;
		std::cout << "===============================================================================================================================" << std::endl;
		std::cout << "Flags" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " -h, --help             Displays this help screen and exits." << std::endl;
		std::cout << " -v, --version          Displays the version number and exits." << std::endl;
		std::cout << " -d, --debug            Displays logs as they occur to stdout, still logs to log file." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Example Usage" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Notes" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "" << std::endl;
		return;
	}

	void parseOptions(int argc, char* argv[], int* i)
	{
		std::string arg = "";

		while (*i < argc - 1 and not function::KILL) {
			(*i)++;
			arg = argv[*i];
			if (arg == "-h" || arg == "--help") {
				function::HELP = true;
			}
			else if (arg == "-v" || arg == "--version") {
				function::CHECKVERSION = true;
			}
			else if (arg == "-d" || arg == "--debug") {
				function::DEBUG = true;
				function::info("DEBUG FLAG SET, VERBOSE OUTPUT SENT TO STDOUT.");
			}
			else {
				function::error("Invalid flags passed! Please check your command and try again.");
				function::error("+============================================================+");
				function::HELP = true;
				function::KILL = true;
				function::EXITCODE = 1;
			}
		}
	}

	// Global Variables for Determining Execution
	bool HELP = false;                // If helpmessage is going to be displayed.
	bool CHECKVERSION = false;        // If version information is going to be displayed.
	bool DEBUG = false;               // Global variable for debugging.
	bool KILL = false;                // Determines if end should occur as soon as possible.
	int EXITCODE = 0;             // Return code of the program.
}