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
	
	// String headers for LOG, WARN, and ERROR.
	const std::string HEADER_INFO = "   [INFO] - ";
	const std::string HEADER_DEBU = "  [DEBUG] - ";
	const std::string HEADER_WARN = "[WARNING] - ";
	const std::string HEADER_ERRR = "  [ERROR] - ";

	// Following funcitons prepend their message before the log sent to the console.
	void info(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console.
	void debug(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console if debug is set.
	void error(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console.
	void warning(std::string str, std::string str2 = "", std::string str3 = ""); //Logs a string to the console if debug is set.

	void help_message();
	void version_message();
	void parseOptions(int argc, char* argv[], int* i);
}

#endif // FUNCTION_H