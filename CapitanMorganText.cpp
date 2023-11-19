#include "CapitanMorganText.h"

void CapitanMorganText::ReadData(const char* filename)
{
	BinaryReader* m_reader = new BinaryReader(filename);

	header.Magic = m_reader->ReadNullTerminatedString();
	header.Version = m_reader->ReadInt32();
	header.FileName = m_reader->ReadNullTerminatedString();
	header.NumOfEntries = m_reader->ReadUint32();
	header.LKEYTableStart = m_reader->ReadUint32();
	header.LSTRTableStart = m_reader->ReadUint64();
	header.LKEYMagic = m_reader->ReadFixedLengthString(4);
	header.LKEYTableSize = m_reader->ReadUint32();

	//read entries
	for (int i = 0; i < header.NumOfEntries; i++)
	{
		Entry entry{};
		entry.ID = m_reader->ReadUint32();
		entry.Offset = m_reader->ReadUint32();
		size_t savePos = m_reader->Position();
		m_reader->SeekBeg(header.LSTRTableStart + entry.Offset);
		entry.LString = m_reader->ReadNullTerminatedString();
		m_reader->SeekBeg(savePos);
		entries.push_back(entry);
	}

	//read LSTR header
	m_reader->SeekBeg(header.LKEYTableSize + header.LKEYTableStart);
	EntryHeader entryHeader{};
	entryHeader.Magic = m_reader->ReadFixedLengthString(4);
	entryHeader.LSTRTableSize = m_reader->ReadUint32();
	header.entryHeader = entryHeader;
	
}

void CapitanMorganText::WriteData(const char* filename)
{
	// Get the extension of the file
	std::filesystem::path path(filename);
	std::string extension = path.extension().string();

	std::filesystem::path filename_no_extention = std::filesystem::path(filename).replace_extension();
	std::filesystem::path new_binary_filename = StringHelpers::ReplaceExtention(filename_no_extention.string().c_str(), "dat.new");

	this->ReadData(filename_no_extention.string().c_str());

	BinaryWriter m_writer(new_binary_filename.string());
	m_writer.WriteNullTerminatedString(this->header.Magic);
	m_writer.WriteUint32(this->header.Version);
	m_writer.WriteNullTerminatedString(this->header.FileName);
	m_writer.WriteUint32(this->header.NumOfEntries);
	m_writer.WriteUint32(this->header.LKEYTableStart);
	m_writer.WriteUint64(this->header.LSTRTableStart);
	m_writer.WriteFixedLengthString(this->header.LKEYMagic);
	m_writer.WriteUint32(this->header.LKEYTableSize);

	//now need to make a new string table vector
	std::ifstream inputFile(filename);
	std::string line;
	std::vector<Entry> new_entries;
	int offset = 0;

	while (std::getline(inputFile, line)) {

		std::stringstream liner(line);
		std::string token;
		uint32_t lineID;

		std::getline(liner, token, '=');
		std::istringstream(token) >> std::hex >> lineID;

		std::getline(liner, token);
		std::string lineText = StringHelpers::ReplaceToBinary(token);

		Entry entry{};
		entry.ID = lineID;
		entry.LString = lineText;
		entry.Offset = offset;
		offset += lineText.length() + 1;
	
		new_entries.push_back(entry);
	}

	for (Entry entry : new_entries) {
		m_writer.WriteUint32(entry.ID);
		m_writer.WriteUint32(entry.Offset);
	}

	//write LSTR Text Header
	header.entryHeader.LSTRTableSize = offset;
	m_writer.WriteFixedLengthString(header.entryHeader.Magic);
	m_writer.WriteInt32(header.entryHeader.LSTRTableSize); //write size of text this is only temporary

	//write LSRT entries
	for (Entry entry : new_entries) {
		m_writer.WriteNullTerminatedString(entry.LString);
	}

}
