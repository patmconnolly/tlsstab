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

#include <string>

#include "stab.hpp"
#include "function.hpp"
#include "curl/curl.h"

// Add function defenitions here.
namespace stab {
    auto buildHandle(std::string exec_header, std::string exec_url){
        std::string fullURL = exec_header + exec_url;
        function::debug("Building URL into handle: ", fullURL);
        auto handle = curl_easy_init();
        curl_easy_setopt(handle, CURLOPT_URL, fullURL.c_str());
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //Follow redirects
        curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L); //Enable verbose to collect SSL expiry date exactly.
        curl_easy_setopt(handle, CURLOPT_DEBUGFUNCTION, stab::debug_function);
        curl_easy_setopt(handle, CURLOPT_DEBUGDATA, &stab::stderr_buffer);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, stab::discard_data);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, nullptr);
        return handle;
    }

    bool insecure(){
        bool passfail = true;
        auto handle = stab::buildHandle(function::HTTP, function::URL);
        curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_3);
        passfail = stab::executeStab(handle, "HTTP");
        stab::stderr_buffer = "";
        return passfail;
    }

	bool secure(long minPROTOCOL, std::string protocolNAME){
        bool passfail = true;
        auto handle = stab::buildHandle(function::HTTPS, function::URL);
        curl_easy_setopt(handle, CURLOPT_SSLVERSION, (long)minPROTOCOL);
        passfail = stab::executeStab(handle, protocolNAME);
        stab::stderr_buffer = "";
        return passfail;
    }
    bool secure(long minPROTOCOL, long maxPROTOCOL, std::string protocolNAME){
        bool passfail = true;
        auto handle = stab::buildHandle(function::HTTPS, function::URL);
        curl_easy_setopt(handle, CURLOPT_SSLVERSION, minPROTOCOL | maxPROTOCOL);
        passfail = stab::executeStab(handle, protocolNAME);
        stab::stderr_buffer = "";
        return passfail;
    }



    bool executeStab(auto handle, std::string protocolNAME){
        CURLcode res;

        res = curl_easy_perform(handle);

        curl_easy_cleanup(handle);

        function::debug(stab::stderr_buffer);

        if (stab::stderr_buffer.contains(stab::FAILTEXT_a) or stab::stderr_buffer.contains(stab::FAILTEXT_b) or stab::stderr_buffer.contains(stab::FAILTEXT_c)) {
            function::info("Protocol ", protocolNAME, " not supported!");
            return false;
        }
        else if (stab::stderr_buffer.contains(stab::SUCCESSTEXT_a + protocolNAME) and stab::stderr_buffer.contains(stab::SUCCESSTEXT_b)) {
            function::info("Protocol ", protocolNAME, " is supported.");
            return true;
        }
        else {
            function::error("Unexpected error occured in stab protocol ", protocolNAME, "!");
            //function::debug(stab::stderr_buffer);
        }
        return false;
    }

	//Discard HTML data as that is not needed.
	size_t discard_data(void* buffer, size_t size, size_t nmemb, void* userp) {
		return size * nmemb;
	}

    // Collect the verbose curl output as string instead of file.
    int debug_function(CURL* handle, curl_infotype type, char* data, size_t size, void* userp) {
        std::string* buffer = static_cast<std::string*>(userp);
        if (type == CURLINFO_TEXT) {
            buffer->append(data, size);
        }
        return 0;
    }

    std::string stderr_buffer = "";
	
}