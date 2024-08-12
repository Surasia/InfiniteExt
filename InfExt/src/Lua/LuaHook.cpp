#include "LuaHook.hpp"
#include "../HavokScript/HavokScript.hpp"

void LuaVM::ProcessCommand() {
	std::string command = "";

	std::cout << "> ";
	std::getline(std::cin, command);

	if (command.rfind("/dofile ", 0) == 0) {
		std::string filepath = command.substr(8);
		if (!filepath.empty()) {
			if (Hks::DoFile(filepath.c_str())) {
				std::cerr << "Error: Failed to load file: " << filepath << std::endl;
			}
		}
		else {
			std::cerr << "Error: No filepath specified for /dofile command."
				<< std::endl;
		}
	}
	else {
		if (Hks::DoString(command.c_str())) {
			std::cerr << "Error: Failed to load string: " << command << std::endl;
		}
	}
}
