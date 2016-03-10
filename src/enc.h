#ifndef SRC_ENC_H_
#define SRC_ENC_H_

#include <string.h>
#include <stdio.h>
#include <limits.h>

#include <dirent.h>
//has info such as this path is a directory, or this path is a file
#include <sys/stat.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

int enc_main(const int argc, const char *argv[]);

int enc_dir_recursive(const char *path);

#endif /* SRC_ENC_H_ */
