#pragma once

namespace file
{
	// i believe this may actually be some kind of MemoryBlock struct and fileaccessor somehow inherits from mem::DataBlock
	struct FileData
	{
		unsigned long file_size;
		void *file_data;
	};
	
	class FileAccessor
	{
		unsigned long unk;
	public:
		FileAccessor(const char *path, bool unk);
		bool isLoaded() const;
		FileData block() const;
	};
}