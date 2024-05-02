#pragma once

namespace file
{
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