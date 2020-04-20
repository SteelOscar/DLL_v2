#include "pch.h"
#include "FAT32VolumeInfo.h"

void BaseFileSystem::fillFSData() {

	BYTE lpBuffer[512];
	memset(lpBuffer, 0, 512);
	DWORD nNumberOfBytesToRead(0);

	std::string diskNameFormat = "\\\\.\\" + this->diskName + ":";

	HANDLE hFile = CreateFileA(
		diskNameFormat.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE |
		FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) return ;

	if (!ReadFile(hFile, lpBuffer, 512, &nNumberOfBytesToRead, NULL)) return ;

	CloseHandle(hFile);

	printFSData(lpBuffer);
}