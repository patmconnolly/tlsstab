// Main class for TLSStab
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
#include <curl/curl.h>

#include "include/function.hpp"
#include "include/stab.hpp"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		//Checks if no arguments were passed, other than the program name.
		//Fails the program if so.
		std::cout << "Invalid flags passed! You need to pass at least one argument." << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl << std::endl;
		function::help_message();
		return 1;
	}

	int* i = new int(0);
	function::parseOptions(argc, argv, i);
	if (function::CHECKVERSION) { function::version_message(); function::KILL = true; }
	if (function::HELP) { function::help_message(); function::KILL = true; }

	if (not function::KILL) {
		function::debug("Beginning stab.");
		//Commenting out insecure and SSL versions.
		//Limited support paths.
		/*if (function::INSECURE || function::FULL)
		{
			function::debug("-Executing Insecure.");
			stab::insecure();
		}*/
		/*if (function::SSL20 || function::FULL)
		{
			function::debug("-Executing SSLv2.0.");
			stab::secure(CURL_SSLVERSION_SSLv2, "SSLv2.0");
		}*/
		/*if (function::SSL30 || function::FULL)
		{
			function::debug("-Executing SSLv3.0.");
			stab::secure(CURL_SSLVERSION_SSLv3, "SSLv3.0");
		}*/
		if (function::TLS10 || function::FULL)
		{
			function::debug("-Executing TLSv1.0.");
			stab::secure(CURL_SSLVERSION_TLSv1_0, CURL_SSLVERSION_MAX_TLSv1_0, "TLSv1.0");
		}
		if (function::TLS11 || function::FULL)
		{
			function::debug("-Executing TLSv1.1.");
			stab::secure(CURL_SSLVERSION_TLSv1_1, CURL_SSLVERSION_MAX_TLSv1_1, "TLSv1.1");
		}
		if (function::TLS12 || function::FULL)
		{
			function::debug("-Executing TLSv1.2.");
			stab::secure(CURL_SSLVERSION_TLSv1_2, CURL_SSLVERSION_MAX_TLSv1_2, "TLSv1.2");
		}
		if (function::TLS13 || function::FULL)
		{
			function::debug("-Executing TLSv1.3.");
			stab::secure(CURL_SSLVERSION_TLSv1_3, CURL_SSLVERSION_MAX_TLSv1_3, "TLSv1.3");
		}
		function::debug("Stab complete.");
	}

	return function::EXITCODE;
}