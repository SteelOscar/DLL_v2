#include "pch.h"
#include "FAT32VolumeInfo.h"

void FAT32FS::printFSData(BYTE* buffer) {

	FAT32 volume = *reinterpret_cast<FAT32*>(buffer);

	printf("OEM in ASCII: %s\n", volume.OEM_ASCII);
	printf("The number of bytes in the sector: %d\n", volume.sectorSize);
	printf("Cluster factor: %d\n", volume.clusterFactor);
	printf("Cluster size: %d bytes\n", calculateClusterSize(volume));
	printf("The number of clusters in FS : %d\n", calculateClusterCnt(volume));
	printf("First sector FAT: %d\n", calculateFirstSectorFAT(volume));
	printf("First sector root directory: %d\n", calculateFirstSectorRootDir(volume));
	printf("Reserved area size: %d sectors\n", volume.reservedAreaSize);
	printf("Number of copies FAT: %d\n", volume.copyFATCnt);
	printf("Media type (0xF8 - stationary, 0xF0 - removable) 0x%X\n", volume.mediaType);
	printf("The number of sectors in the track: %d\n", volume.sectorsPerTrack);
	printf("The number of heads: %d\n", volume.headsCnt);
	printf("The number of sectors before the start of the section: %d\n", volume.sectorsBeforeStartSection);
	printf("The number of sectors in the file system: %d\n", volume.sectorsCnt32);
}

int FAT32FS::calculateClusterSize(FAT32 volume) {

	return volume.sectorSize * volume.clusterFactor;
}

int FAT32FS::calculateClusterCnt(FAT32 volume) {

	return volume.sectorsCnt32 / volume.clusterFactor;
}

int FAT32FS::calculateFirstSectorFAT(FAT32 volume) {

	return volume.reservedAreaSize + 1;
}

int FAT32FS::calculateFirstSectorRootDir(FAT32 volume) {

	return volume.sizeFAT32 * volume.copyFATCnt + volume.reservedAreaSize;
}