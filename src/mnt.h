#ifndef SRC_MNT_H_
#define SRC_MNT_H_

#define FUSE_USE_VERSION 30
#define SFS_DATA ((struct sfs_state *) fuse_get_context()->private_data)

#include "common.h"

#include <dirent.h>
#include <errno.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#ifdef HAVE_SYS_XATTR_H
#include <sys/xattr.h>
#endif

int enc_main(const int argc, const char *argv[]);

#endif /* SRC_MNT_H_ */
