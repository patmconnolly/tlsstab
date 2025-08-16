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
#include <algorithm>
#include <cctype>

#include "function.hpp"
#include "version.hpp"

// Add function defenitions here.
namespace function {
	std::string toLower(std::string input)
	{
		std::string lowercase_string = input; // 1. Create a copy
		std::transform(lowercase_string.begin(), lowercase_string.end(), lowercase_string.begin(), [](unsigned char c) { return std::tolower(c); }); // 2. Transform the copy in place
		return lowercase_string;
	}

	void replace_prefix(std::string& primaryString) {
		if (primaryString.compare(0, function::HTTP.length(), function::HTTP) == 0)
		{
			function::debug("Stripping http:// from URL provided.");
			primaryString.replace(0, function::HTTP.length(), "");
		}
		else if (primaryString.compare(0, function::HTTPS.length(), function::HTTPS) == 0)
		{
			function::debug("Stripping https:// from URL provided.");
			primaryString.replace(0, function::HTTPS.length(), "");
		}
	}

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
		std::cout << " > tlsstab [flags...] <url>" << std::endl;
		std::cout << "===============================================================================================================================" << std::endl;
		std::cout << "Flags" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " -h, --help             Displays this help screen and exits." << std::endl;
		std::cout << " -v, --version          Displays the version number and exits." << std::endl;
		std::cout << " -d, --debug            Displays logs as they occur to stdout, still logs to log file." << std::endl;
		std::cout << "" << std::endl;
		std::cout << " -i, --insecure      " << std::endl;
		std::cout << " --sslall     " << std::endl;
		std::cout << " --tlsall     " << std::endl;
		std::cout << " --ssl20     " << std::endl;
		std::cout << " --ssl30     " << std::endl;
		std::cout << " --tls10     " << std::endl;
		std::cout << " --tls11     " << std::endl;
		std::cout << " --tls12     " << std::endl;
		std::cout << " --tls13     " << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Example Usage" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " > tlsstab --insecure --sslall --tlsall https://example.com" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Notes" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " Default behavior is to check insecure, all SSL versions, and all TLS versions." << std::endl;
		std::cout << " Selecting a behavior flag overrides this behavior and only runs the versions explicetly called." << std::endl;
		std::cout << " HTTP/HTTPS is removed from the URL specified and readded for the secure/insecure options." << std::endl;
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
				function::debug("DEBUG FLAG SET, VERBOSE OUTPUT SENT TO STDOUT.");
			}
			else if (function::toLower(arg) == "--insecure" || function::toLower(arg) == "-i") {
				function::INSECURE = true;
				function::debug("Set to check HTTP.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--sslall") {
				function::SSL20 = true;
				function::debug("Set to check SSL 2.0.");
				function::SSL30 = true;
				function::debug("Set to check SSL 3.0.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--tlsall") {
				function::TLS10 = true;
				function::debug("Set to check TLS 1.0.");
				function::TLS11 = true;
				function::debug("Set to check TLS 1.1.");
				function::TLS12 = true;
				function::debug("Set to check TLS 1.2.");
				function::TLS13 = true;
				function::debug("Set to check TLS 1.3.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--ssl20") {
				function::SSL20 = true;
				function::debug("Set to check SSL 2.0.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--ssl30") {
				function::SSL30 = true;
				function::debug("Set to check SSL 3.0.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--tls10") {
				function::TLS10 = true;
				function::debug("Set to check TLS 1.0.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--tls11") {
				function::TLS11 = true;
				function::debug("Set to check TLS 1.1.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--tls12") {
				function::TLS12 = true;
				function::debug("Set to check TLS 1.2.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if (function::toLower(arg) == "--tls13") {
				function::TLS13 = true;
				function::debug("Set to check TLS 1.3.");
				function::FULL = false;
				function::debug("Set to not do a complete check automatically.");
			}
			else if ((*i) == argc - 1) {
				function::URL = arg;
				function::replace_prefix(function::URL);
				function::debug("Set URL to: ", function::URL);
			}
			else {
				function::error("Invalid flags passed! Please check your command and try again.");
				function::error("+============================================================+");
				function::HELP = true;
				function::KILL = true;
				function::EXITCODE = 1;
			}
		}

		if (function::URL == function::INVALID_URL) {
			function::error("Invalid URL passed in! Please check your command and try again.");
			function::error("+=============================================================+");
			function::HELP = true;
			function::KILL = true;
			function::EXITCODE = 1;
		}
	}

	// Global Variables for Determining Execution
	bool HELP = false;                // If helpmessage is going to be displayed.
	bool CHECKVERSION = false;        // If version information is going to be displayed.
	bool DEBUG = false;               // Global variable for debugging.
	bool KILL = false;                // Determines if end should occur as soon as possible.
	int EXITCODE = 0;             // Return code of the program.

	std::string URL = function::INVALID_URL;

	// Global Variables for Execution Mode
	bool INSECURE = false; // Checks if no SSL/TLS is supported.
	bool SSL20 = false;    // Checks for SSL2.0 support.
	bool SSL30 = false;    // Checks for SSL3.0 support.
	bool TLS10 = false;    // Checks for TLS1.0 support.
	bool TLS11 = false;    // Checks for TLS1.1 support.
	bool TLS12 = false;    // Checks for TLS1.2 support.
	bool TLS13 = false;    // Checks for TLS1.3 support.
	bool FULL = true;      // Checks all version support. Default action.
}