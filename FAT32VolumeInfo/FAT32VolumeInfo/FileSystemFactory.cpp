#include "pch.h"
#include "FAT32VolumeInfo.h"

BaseFileSystem* FileSystemFactory::create(std::string fsName)  {

	if (fsName.find("FAT32") != -1) {
		return new FAT32FS(diskName);
	}
	else {
		std::cout << "Данная файловая система еще не поддерживается" << std::endl;
	}
}