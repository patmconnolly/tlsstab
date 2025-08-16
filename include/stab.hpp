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
}

#endif // STAB_H