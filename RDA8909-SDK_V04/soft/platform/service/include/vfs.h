/* Copyright (C) 2016 RDA Technologies Limited and/or its affiliates("RDA").
* All rights reserved.
*
* This software is supplied "AS IS" without any warranties.
* RDA assumes no responsibility or liability for the use of the software,
* conveys no license or title under any patent, copyright, or mask work
* right to the product. RDA reserves the right to make changes in the
* software without notification.  RDA also make no representation or
* warranty that such application will be suitable for the specified use
* without further testing or modification.
*/

#ifndef _VFS_H_
#define _VFS_H_

#include "cs_types.h"
#include <sys/dirent.h>
#include <sys/stat.h>
#include <sys/fnctl.h>
#include <sys/statvfs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VFS_PATH_MAX (192)

#ifndef SEEK_SET
#define SEEK_SET 0
#endif /* SEEK_SET */

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif /* SEEK_CUR */

#ifndef SEEK_END
#define SEEK_END 2
#endif /* SEEK_END */

int vfs_umount(const char *path);

int vfs_creat(const char *path, int mode);
int vfs_open(const char *path, int flags, ...);
int vfs_close(int fd);
ssize_t vfs_read(int fd, void *dst, size_t size);
ssize_t vfs_write(int fd, const void *data, size_t size);
long vfs_lseek(int fd, long offset, int mode);
int vfs_fstat(int fd, struct stat *st);
int vfs_stat(const char *path, struct stat *st);
int vfs_truncate(const char *path, long length);
int vfs_ftruncate(int fd, long length);
int vfs_link(const char *oldpath, const char *newpath); /* ENOSYS */
int vfs_unlink(const char *path);
int vfs_rename(const char *src, const char *dst);
int vfs_fsync(int fd);
int vfs_fnctl(int fd, int cmd, ...); /* ENOSYS */
int vfs_ioctl(int fd, int cmd, ...); /* ENOSYS */

DIR *vfs_opendir(const char *name);
struct dirent *vfs_readdir(DIR *pdir);
int vfs_readdir_r(DIR *pdir, struct dirent *entry, struct dirent **out_dirent);
long vfs_telldir(DIR *pdir);
void vfs_seekdir(DIR *pdir, long loc);
void vfs_rewinddir(DIR *pdir);
int vfs_closedir(DIR *pdir);
int vfs_mkdir(const char *name, int mode);
int vfs_rmdir(const char *name);

int vfs_chdir(const char *path); /* UNSAFE !!! */
char *vfs_getcwd(char *buf, size_t size);
char *vfs_realpath(const char *path, char *resolved_path);

int vfs_statvfs(const char *path, struct statvfs *buf);
int vfs_fstatvfs(int fd, struct statvfs *buf);

// safefile is abstract based on file. Typical use case is for configuration.
// At power off, it is required that either old version or new version will
// exists. And it is not permitted that both of them disappears, or the content
// is incomplete.
//
// Requirements:
// * On write, only support read/write the whole data.
// * "init" must be called before any other access (check and clean up power off garbage).
// * Maximum file name length is one byte shorter than normal file.
int vfs_sfile_init(const char *path);
ssize_t vfs_sfile_read(const char *path, void *dst, size_t size);
ssize_t vfs_sfile_write(const char *path, const void *data, size_t size);
ssize_t vfs_sfile_size(const char *path);

char *vfs_resolve_path(const char *base_path, const char *path, char *resolved_path);
ssize_t vfs_file_read(const char *path, void *dst, size_t size);
ssize_t vfs_file_write(const char *path, const void *data, size_t size);
ssize_t vfs_file_size(const char *path);

#ifdef __cplusplus
}
#endif

#endif // H
