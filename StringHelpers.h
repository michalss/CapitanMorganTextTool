#pragma once
#include <string>
#include <filesystem>

class StringHelpers
{

private:
	static void ReplaceString(std::string& str, const std::string& from, const std::string& to);

public:
	static std::string ReplaceFromBinary(std::string& line);
	static std::string ReplaceToBinary(std::string& line);
	static std::string ReplaceExtention(const char* input_path, const char* ext);
};

