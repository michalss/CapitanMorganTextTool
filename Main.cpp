#include <iostream>
#include <fstream>
#include <vector>
#include "BinaryHelper/BinaryReader.h"
#include "CapitanMorganText.h"
#include <filesystem>
#include "Main.h"
#include "StringHelpers.h"


void Unpack(const char* binary_filename, const char* output_text_filename)
{
	std::cout << "Start reading the input file!" << std::endl;
	std::ofstream outputfile(output_text_filename);

	CapitanMorganText* capitanMorgan = new CapitanMorganText;
	capitanMorgan->ReadData(binary_filename);

	for (Entry entry : capitanMorgan->entries) {
		outputfile << "0x" << std::hex << entry.ID << "=" << StringHelpers::ReplaceFromBinary(entry.LString) << '\n';
	}
	outputfile.close();
}

void Pack(const char* text_filename)
{
	std::cout << "Start writing the input file!" << std::endl;
	CapitanMorganText* capitanMorgan = new CapitanMorganText;
	capitanMorgan->WriteData(text_filename);

}

void PrintHelp() {
	std::cout << "\n========================================" << std::endl;
	std::cout << "Capitan Morgan Text Tool v.1.0 (2023)" << std::endl;
	std::cout << "Created @by Michalss (https://reshax.com)" << std::endl;
	std::cout << "==========================================" << std::endl;
	std::cout << "Arguments:" << std::endl;
	std::cout << "      -u, u     = unpack text" << std::endl;
	std::cout << "      -p, p     = pack text" << std::endl;
	std::cout << "      -h, h, /? = print help" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "     CapitanMorganTextTool.exe -u [binary_file] " << std::endl;
	std::cout << "     CapitanMorganTextTool.exe -p [text_file] " << std::endl;
	std::cout << "\n" << std::endl;
}

int main(int argc, char* argv[]) {

	if (argv[1] != nullptr) {
		// unpack
		if ((std::string)argv[1] == "-h" || (std::string)argv[1] == "h" || (std::string)argv[1] == "/?") {
			PrintHelp();
			return 1;
		} else if ((std::string)argv[1] == "-u" || (std::string)argv[1] == "u") {
			if (argv[2] != nullptr) {
				std::string input_file = (std::string)argv[2];
				if (std::filesystem::exists(input_file)) {
					std::string text_filepath = StringHelpers::ReplaceExtention(argv[2], "dat.txt");
					Unpack(input_file.c_str(), text_filepath.c_str());
					std::cout << "Unpack completed...\n" << std::endl;
				}
				else {
					PrintHelp();
					std::cout << "Input file:" << input_file << "does not exist!!" << std::endl;
					return 1;
				}
			}
		}
		else if ((std::string)argv[1] == "-p" || (std::string)argv[1] == "p") {
			//pack
			if (argv[2] != nullptr) {
				std::string input_file = (std::string)argv[2];
				if (std::filesystem::exists(input_file)) {
					Pack(input_file.c_str());
					std::cout << "Pack completed...\n" << std::endl;
				}
				else {
					PrintHelp();
					std::cout << "Input file does not exist!!" << std::endl;
					return 1;
				}
			}

		}
		else {
			PrintHelp();
			std::cout << "Not correct argument supplied..." << std::endl;
			return 1;
		}

	}
	else {
		PrintHelp();
		std::cout << "Not any option was selected" << std::endl;
		return 1;
	}
}

