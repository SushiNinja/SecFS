#include "common.h"
#include "enc.h"
#include "mnt.h"

int main(int argc, char* argv[]) {
	if (argc < 4) {
		printUsage();
		return 1;
	}

	if (strcmp(argv[1], "-enc") != 0 && strcmp(argv[1], "-mnt") != 0) {
		printUsage();
		return 1;
	}

	char *action = argv[1];

	int innerargc = argc - 1;
	char *innerargv[innerargc];
	int innerargnum = 0;
	int argnum;
	for (argnum = 0; argnum < argc; argnum++) {
		if (argnum != 1) {
			innerargv[innerargnum++] = argv[argnum];
		}
	}

	if (strcmp(action, "-mnt") == 0) {
		return mount_main(innerargc, innerargv);
	}

	if(strcmp(action, "-enc") == 0) {
		return enc_main(innerargc, innerargv);
	}

	return 1;
}
