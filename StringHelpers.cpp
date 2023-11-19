#include "StringHelpers.h"


void StringHelpers::ReplaceString(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

std::string StringHelpers::ReplaceFromBinary(std::string& value)
{
	ReplaceString(value, "\r", "<cr>");
	ReplaceString(value, "\n", "<lf>");
	ReplaceString(value, "\r\n", "<cf>");

	return value;
}

std::string StringHelpers::ReplaceToBinary(std::string& value)
{
	ReplaceString(value, "<cr>", "\r");
	ReplaceString(value, "<lf>", "\n");
	ReplaceString(value, "<cf>", "\r\n");

	return value;
}

std::string StringHelpers::ReplaceExtention(const char* input_path, const char* ext)
{
	std::filesystem::path replaced_path = std::filesystem::path(input_path).replace_extension(ext);
	return replaced_path.string();
}
