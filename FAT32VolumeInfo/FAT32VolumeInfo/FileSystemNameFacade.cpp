#include "pch.h"
#include "FAT32VolumeInfo.h"

string FileSystemNameFacade::getVolumeFileSystem() {
	char lpVolumeNameBuffer[MAX_PATH];
	DWORD lpVolumeSerialNumber;
	DWORD lpMaximumComponentLength;
	DWORD lpFileSystemFlags;
	char lpFileSystemNameBuffer[MAX_PATH];

	bool dataReceived = GetVolumeInformationA(
		(diskName + ":\\").c_str(),
		lpVolumeNameBuffer,
		sizeof(lpVolumeNameBuffer),
		&lpVolumeSerialNumber,
		&lpMaximumComponentLength,
		&lpFileSystemFlags,
		lpFileSystemNameBuffer,
		sizeof(lpFileSystemNameBuffer)
	);

	if (!dataReceived) return "";

	std::cout << "Volume name: " << lpVolumeNameBuffer << std::endl;
	std::cout << "Volume file system: " << lpFileSystemNameBuffer << std::endl;

	return lpFileSystemNameBuffer;
}