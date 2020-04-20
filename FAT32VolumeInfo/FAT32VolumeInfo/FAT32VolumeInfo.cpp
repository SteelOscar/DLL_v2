#include "pch.h"
#include <iostream>
#include <windows.h>
#include "FAT32VolumeInfo.h"

void execute(std::string diskName) {

	FileSystemNameFacade facade = FileSystemNameFacade(diskName);
	FileSystemFactory factory = FileSystemFactory(diskName);

	BaseFileSystem* fileSystem = factory.create(facade.getVolumeFileSystem());

	fileSystem->showFS();
}