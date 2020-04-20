#pragma once
#include "pch.h"
#include <iostream>

#ifdef FAT32VOLUMEINFO_EXPORTS
#define FAT32VOLUMEINFO_API __declspec(dllexport)
#else
#define FAT32VOLUMEINFO_API __declspec(dllimport)
#endif

using namespace std;

#pragma pack(1)
typedef struct {
	BYTE emptyBytes[3];
	BYTE OEM_ASCII[8];
	WORD sectorSize;
	BYTE clusterFactor;
	WORD reservedAreaSize;
	BYTE copyFATCnt;
	WORD maxCntRecordsFAT1216;
	WORD sectorsCnt16;
	BYTE mediaType;
	WORD sizeFAT1216;
	WORD sectorsPerTrack;
	WORD headsCnt;
	DWORD sectorsBeforeStartSection;
	DWORD sectorsCnt32;
	DWORD sizeFAT32;
} FAT32;
#pragma pack()

class BaseFileSystem {

	public: 

		BaseFileSystem(string diskName) {

			this->diskName = diskName;
		};

		void showFS() {

			fillFSData();
		}

	private:

		string diskName;

		void fillFSData();

		virtual void printFSData(BYTE* buffer) = 0;
};

class FAT32FS : public BaseFileSystem {

	public:

		FAT32FS(string diskName) : BaseFileSystem(diskName) {}

	private:

		virtual void printFSData(BYTE* buffer) override;

		int calculateClusterSize(FAT32 volume);
		int calculateClusterCnt(FAT32 volume);
		int calculateFirstSectorFAT(FAT32 volume);
		int calculateFirstSectorRootDir(FAT32 volume);

};

class FileSystemFactory {

	public:

		FileSystemFactory(string diskName) {

			this->diskName = diskName;
		};

		BaseFileSystem* create(std::string fsName);

	private:

		string diskName;
};

class FileSystemNameFacade {

	public:

		FileSystemNameFacade(string diskName) {

			this->diskName = diskName;
		};

		string getVolumeFileSystem();

	private:

		string diskName;
};

extern "C++" FAT32VOLUMEINFO_API void execute(std::string diskName);