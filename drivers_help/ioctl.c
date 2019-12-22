/* simple ioctl utility for mfrc522_dev */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include "mfrc522_ioctl.h"

static const char *help = "******************************HELP******************************\n\n"
						  "-h, --help\n"
						  "	shows this help\n\n"
						  "-g, --get_addr\n"
						  "	prints current block address which will be read/write\n\n"
						  "-s, --set_addr <addr>\n"
						  "	sets block's address which will be read/write\n\n"
						  "-r, --get_block\n"
						  "	reads and prints block's data\n\n"
						  "-w, --set_block <data>\n"
						  "	writes data to block, data len 16 bytes, upper and lower\n"
						  "	cases are allowed, data should have the next format:\n"
						  "	XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX\n\n"
						  "-e, --get_used_key\n"
						  "	prints which key is used for read/write operations\n\n"
						  "-t, --set_used_keys <key>\n"
						  "	sets used key for read/write operations, available values\n"
						  "	are 'A' and 'B' (both cases are allowed)\n\n"
						  "-a, --get_key_a\n"
						  "-b, --get_key_b\n"
						  "	prints A or B keys respectively\n\n"
						  "-c, --set_key_a <key>\n"
						  "-d, --set_key_b <key>\n"
						  "	sets A or B key respectively, key len 6 bytes, upper and\n"
						  "	lower cases are allowed, data should have the next format:\n"
						  "	XX:XX:XX:XX:XX:XX\n\n"
						  "-n, --get_read_mode\n"
						  "	returns 0 - read function will return content of required block\n"
						  "	non-zero - read function will return UID only (used by default)\n\n"
						  "-m, --set_read_mode\n"
						  "	sets read operation mode\n";

static struct option long_options[] = {
		{"get_block",	 no_argument,		0, 'r'},
		{"set_block",	 required_argument, 0, 'w'},
		{"get_addr",	 no_argument,		0, 'g'},
		{"set_addr",	 required_argument,	0, 's'},
		{"get_used_key", no_argument,		0, 'e'},
		{"set_used_key", required_argument,	0, 't'},
		{"get_key_a",    no_argument,		0, 'a'},
		{"set_key_a", 	 required_argument,	0, 'c'},
		{"get_key_b",    no_argument,		0, 'b'},
		{"set_key_b", 	 required_argument,	0, 'd'},
		{"get_read_mode",no_argument,		0, 'n'},
		{"set_read_mode",required_argument,	0, 'm'},
		{"help",		 no_argument,		0, 'h'}
};

static void hexstring_to_hex(char *str, char *hex, int size)
{
	char tmp[3] = {0, 0, 0};
	for(int i = 0; i < size; i++) {
		memcpy(tmp, &str[i * 3], 2);
		hex[i] = strtol(tmp, NULL, 16);
	}
}

int main (int argc, char **argv)
{
	int longind;
	int opt;

	bool read_block = false;
	bool write_block = false;
	bool get_addr = false;
	bool set_addr = false;
	bool get_used_key = false;
	bool set_used_key = false;
	bool get_key_a = false;
	bool set_key_a = false;
	bool get_key_b = false;
	bool set_key_b = false;
	bool get_read_mode = false;
	bool set_read_mode = false;

	char block_data[MFRC522_BLOCK_SIZE];
	char set_key[MFRC522_KEY_SIZE];
	int bl_addr;
	int used_key;
	int read_mode;

	while((opt = getopt_long(argc, argv, "hrw:gs:et:ac:bd:m:n", long_options, &longind)) != -1) {
		switch(opt)
		{
			case 'h':
				printf("%s\n", help);
				exit(0);
				break;

			case 'r':
				read_block = true;
				break;

			case 'g':
				get_addr = true;
				break;

			case 'e':
				get_used_key = true;
				break;

			case 'a':
				get_key_a = true;
				break;

			case 'b':
				get_key_b = true;
				break;

			case 's':
				bl_addr = atoi(optarg);
				set_addr = true;
				break;

			case 'w':
				hexstring_to_hex(optarg, block_data, MFRC522_BLOCK_SIZE);
				write_block = true;
				break;

			case 't':
				used_key = toupper(optarg[0]) == 'A' ? MFRC522_KEY_A : MFRC522_KEY_B;
				set_used_key = true;
				break;

			case 'c':
				hexstring_to_hex(optarg, set_key, MFRC522_KEY_SIZE);
				set_key_a = true;
				break;


			case 'd':
				hexstring_to_hex(optarg, set_key, MFRC522_KEY_SIZE);
				set_key_b = true;
				break;

			case 'n':
				get_read_mode = true;
				break;

			case 'm':
				read_mode = atoi(optarg);
				set_read_mode = true;
				break;

			case '?':
			default:
				printf("unknown option: %c\n", optopt);
				break;

		}
	}

	if(argv[1] != NULL) {
		int fd = open("/dev/mfrc522_dev", O_RDWR);
		if(fd < 0) {
			printf("Can't open device file: %s\n", strerror(errno));
			return -1;
		}

		if(get_addr) {
			int blnum;

			if(ioctl(fd, MFRC522_IOCGBLADDR, &blnum) < 0) {
				printf("Read block address error!\n");
				return -1;
			}
			printf("Current block address: %d\n", blnum);
		}

		if(get_used_key) {
			int key_idx;

			if(ioctl(fd, MFRC522_IOCGKEY, &key_idx) < 0) {
				printf("Read used key error!\n");
				return -1;
			}
			printf("Current key: %s\n", key_idx == MFRC522_KEY_A ? "KEY A" : "KEY B");
		}

		if(get_key_a) {
			char key[MFRC522_KEY_SIZE];

			if(ioctl(fd, MFRC522_IOCGKEYA, key) < 0) {
				printf("Read KEY A error!\n");
				return -1;
			}
			printf("KEY A: ");
			for(int i = 0; i < MFRC522_KEY_SIZE - 1; i++)
				printf("%02x:", key[i]);
			printf("%02x\n", key[MFRC522_KEY_SIZE - 1]);
		}

		if(get_key_b) {
			char key[MFRC522_KEY_SIZE];

			if(ioctl(fd, MFRC522_IOCGKEYB, key) < 0) {
				printf("Read KEY B error!\n");
				return -1;
			}
			printf("KEY B: ");
			for(int i = 0; i < MFRC522_KEY_SIZE - 1; i++)
				printf("%02x:", key[i]);
			printf("%02x\n", key[MFRC522_KEY_SIZE - 1]);
		}

		if(get_read_mode) {
			int mode;
			if(ioctl(fd, MFRC522_IOCGROID, &mode) < 0) {
				printf("Get read mode error!\n");
				return -1;
			}
			printf("Read mode: %d\n", mode);
		}

		if(set_read_mode) {
			if(ioctl(fd, MFRC522_IOCSROID, &read_mode) < 0) {
				printf("Set read mode error!\n");
				return -1;
			}
			printf("Read mode was changed to: %d\n", read_mode);
		}

		if(set_addr) {
			if(ioctl(fd, MFRC522_IOCSBLADDR, &bl_addr) < 0) {
				printf("Set block address error!\n");
				return -1;
			}
			printf("Block address was changed to: %d\n", bl_addr);
		}

		if(set_used_key) {
			if(ioctl(fd, MFRC522_IOCSKEY, &used_key) < 0) {
				printf("Set used key error!\n");
				return -1;
			}
			printf("Used key was changed to: %s\n", used_key == MFRC522_KEY_A ? "KEY A" : "KEY B");
		}

		if(set_key_a) {
			if(ioctl(fd, MFRC522_IOCSKEYA, set_key) < 0) {
				printf("Set KEY A error!\n");
				return -1;
			}
			printf("KEY A was changed to: ");
			for(int i = 0; i < MFRC522_KEY_SIZE - 1; i++)
				printf("%02x:", set_key[i]);
			printf("%02x\n", set_key[MFRC522_KEY_SIZE - 1]);
		}

		if(set_key_b) {
			if(ioctl(fd, MFRC522_IOCSKEYB, set_key) < 0) {
				printf("Set KEY B error!\n");
				return -1;
			}
			printf("KEY B was changed to: ");
			for(int i = 0; i < MFRC522_KEY_SIZE - 1; i++)
				printf("%02x:", set_key[i]);
			printf("%02x\n", set_key[MFRC522_KEY_SIZE - 1]);
		}

		if(read_block) {
			char data[MFRC522_BLOCK_SIZE];
			ssize_t ret = read(fd, data, MFRC522_BLOCK_SIZE);
			if(ret == MFRC522_BLOCK_SIZE) {
				printf("Read data: ");
				for(int i = 0; i < MFRC522_BLOCK_SIZE - 1; i++)
					printf("%02x:", data[i]);
				printf("%02x\n", data[MFRC522_BLOCK_SIZE - 1]);
			} else if(ret > 0) {
				printf("Something went wrong, not all data was read!\n");
			} else {
				printf("Read error: %s\n", strerror(errno));
				return -1;
			}
		}

		if(write_block) {
			ssize_t ret = write(fd, block_data, MFRC522_BLOCK_SIZE);
			if(ret == MFRC522_BLOCK_SIZE) {
				printf("Data was written successfully\n");
			} else if(ret > 0) {
				printf("Something went wrong, not all data was written!\n");
			} else {
				printf("Write error: %s\n", strerror(errno));
				return -1;
			}
		}

		close(fd);
	} else {
		printf("No option was passed! To run help print: %s --help\n", argv[0]);
	}

	return 0;
}
