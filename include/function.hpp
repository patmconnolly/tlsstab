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

#ifndef FUNCITON_H
#define FUNCTION_H

#include <string>

// Add function declarations here.
namespace function {
	// Global Variables for Determining Execution
	extern bool HELP;                // If helpmessage is going to be displayed.
	extern bool CHECKVERSION;        // If version information is going to be displayed.
	extern bool DEBUG;               // Global variable for debugging.
	extern bool KILL;                // Determines if end should occur as soon as possible.
	extern int EXITCODE;             // Return code of the program.
	const bool SILENT = false;       // Const silent flag, leaving in case a silent mode is desired in the future.

	// Global Variables for Execution Mode
	extern bool INSECURE; // Checks if no SSL/TLS is supported.
	extern bool SSL20;    // Checks for SSL2.0 support.
	extern bool SSL30;    // Checks for SSL3.0 support.
	extern bool TLS10;    // Checks for TLS1.0 support.
	extern bool TLS11;    // Checks for TLS1.1 support.
	extern bool TLS12;    // Checks for TLS1.2 support.
	extern bool TLS13;    // Checks for TLS1.3 support.
	extern bool FULL;     // Checks all version support. Default action.

	extern std::string URL; // Target URL
	
	// String headers for LOG, WARN, and ERROR.
	const std::string HEADER_INFO = "   [INFO] - ";
	const std::string HEADER_DEBU = "  [DEBUG] - ";
	const std::string HEADER_WARN = "[WARNING] - ";
	const std::string HEADER_ERRR = "  [ERROR] - ";

	const std::string HTTP = "http://";
	const std::string HTTPS = "https://";
	const std::string INVALID_URL = "httpx://invalid";

	// Following funcitons prepend their message before the log sent to the console.
	void info(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console.
	void debug(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console if debug is set.
	void error(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console.
	void warning(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console if debug is set.

	std::string toLower(std::string input); //Inputs a string and converts it to lowercase.
	void replace_prefix(std::string& primaryString); //Inputs the URL, strips the prefix.

	void help_message();
	void version_message();
	void parseOptions(int argc, char* argv[], int* i);
}

#endif // FUNCTION_H