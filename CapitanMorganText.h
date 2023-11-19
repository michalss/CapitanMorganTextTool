#pragma once
#include <string>
#include "BinaryHelper/BinaryReader.h"
#include "BinaryHelper/BinaryWriter.h"
#include "StringHelpers.h"
#include "vector"
#include <filesystem>
#include <iostream>
#include <fstream>

typedef struct EntryHeader {
	std::string Magic;
	std::uint32_t LSTRTableSize;
} ENTRYHEADER;

typedef struct Header {
	std::string Magic;
	uint32_t Version;
	std::string FileName;
	uint32_t NumOfEntries;
	uint32_t LKEYTableStart;
	uint32_t LSTRTableStart;
	uint32_t Unknown;
	std::string LKEYMagic;
	uint32_t LKEYTableSize;
	EntryHeader entryHeader;
} HEADER;

typedef struct Entry {
	uint32_t ID;
	uint32_t Offset;
	uint32_t pos;
	std::string LString;
} ENTRY;


class CapitanMorganText
{

public:
	Header header{};
	std::vector<Entry> entries{};
	void ReadData(const char* filename);
	void WriteData(const char* filename);
};


