#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "basic.h"
#include "fsapi.h"
#include "diagnostic.h"
#include "aes.c"



int main(){
	int disk = createSFS("test_disk", 64*BLOCK_SIZE);
	int k;
	char* data = (char*)malloc(100);
	char* file_data = (char*)malloc(50);
	char* out_data = (char*)malloc(50);

	strcpy(file_data, "this is first file");
	AES_ECB_encrypt((uint8_t*)file_data, (uint8_t*)"abcdefghijklmnop", (uint8_t*)out_data, 50);
	printf("%s\n",file_data );
	printf("Encyrpted Data:%s\n",out_data);
	writeFile(disk, "/a", out_data);
	//print_FileList(disk);
	
	print_inodeBitmaps(disk);
	print_dataBitmaps(disk);
	printf("Reading file:\n");
	k = readFile(disk, "/a", data);
	AES_ECB_decrypt((uint8_t*)data, (uint8_t*)"abcdefghijklmnop", (uint8_t*)out_data, 50);
	if(k==-5)
		printf("Does not exist\n");
	else printf("%s\n", out_data);

	
	deleteFile(disk,"/a");

	printf("Deleting file\n");
	printf("Reading file:\n");
	k = readFile(disk, "/bar", data);
	if(k==-5)
		printf("Does not exist\n");
	else printf("%s\n", data);

	print_inodeBitmaps(disk);
	print_dataBitmaps(disk);

	return 0;
}

