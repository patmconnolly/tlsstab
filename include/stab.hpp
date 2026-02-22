// Library to execute commands to check if TLS/SSL Versions are Allowed.
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

#ifndef STAB_H
#define STAB_H

#include <string>
#include <curl/curl.h>

// Add function declarations here.
namespace stab {
	const std::string RESULT_HEADER = "Results of check for ";
	const std::string TLS_HEADER = "TLSv";
	const std::string SSL_HEADER = "SSLv";
	const std::string v10 = "1.0: ";
	const std::string v11 = "1.1: ";
	const std::string v12 = "1.2: ";
	const std::string v13 = "1.3: ";
	const std::string v20 = "2.0: ";
	const std::string v30 = "3.0: ";
	const std::string ENABLED = "ENABLED";
	const std::string DISABLED = "DISABLED";
	extern std::string stderr_buffer;

	const std::string FAILTEXT_a = "SSL routines::no protocols available";
	const std::string FAILTEXT_b = "TLS alert, handshake failure";
	const std::string FAILTEXT_c = "SSL routines::unsupported protocol";
	const std::string SUCCESSTEXT_a = "SSL connection using ";
	const std::string SUCCESSTEXT_b = "ALPN: server accepted";

	//Function Definitions
	// URL in Global Variable, just need SSL/TLS and version.
	auto buildHandle(std::string exec_header, std::string exec_url);
	bool executeStab(auto handle, std::string protocolNAME);
	bool insecure();
	bool secure(long minPROTOCOL, std::string protocolNAME);
	bool secure(long minPROTOCOL, long maxPROTOCOL, std::string protocolNAME);


	//Discard HTML data as that is not needed. For CURL Calls.
	size_t discard_data(void* buffer, size_t size, size_t nmemb, void* userp);

	// Collect the verbose curl output as string instead of file.
	static int debug_function(CURL* handle, curl_infotype type, char* data, size_t size, void* userp);
}

#endif // STAB_H