/*
 * SPDX-FileCopyrightText: 2014-2025 Sébastien Helleu <flashcode@flashtux.org>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This file is part of WeeChat, the extensible chat client.
 *
 * WeeChat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WeeChat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WeeChat.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Test directory/file functions */

#include "CppUTest/TestHarness.h"

extern "C"
{
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "src/core/core-dir.h"
#include "src/core/core-string.h"

extern void dir_remove_trailing_separators (char *path);
}

TEST_GROUP(CoreDir)
{
};

/*
 * Tests functions:
 *   dir_get_temp_dir
 */

TEST(CoreDir, GetTempDir)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_mkdir_home
 *   dir_mkdir
 *   dir_mkdir_parents
 */

TEST(CoreDir, Mkdir)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_unlink_cb
 *   dir_rmtree
 */

TEST(CoreDir, Rmtree)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_set_home_path
 */

TEST(CoreDir, SetHomePath)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_create_home_temp_dir
 */

TEST(CoreDir, CreateHomeTempDir)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_find_xdg_dirs
 */

TEST(CoreDir, FindXdgDirs)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_find_home_dirs
 */

TEST(CoreDir, FindHomeDirs)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_remove_trailing_separators
 */

TEST(CoreDir, RemoveTrailingSeparators)
{
    char path[128];

    dir_remove_trailing_separators (NULL);

    path[0] = '\0';
    dir_remove_trailing_separators (path);
    STRCMP_EQUAL("", path);

    snprintf (path, sizeof (path), "/");
    dir_remove_trailing_separators (path);
    STRCMP_EQUAL("/", path);

    snprintf (path, sizeof (path), "///");
    dir_remove_trailing_separators (path);
    STRCMP_EQUAL("/", path);

    snprintf (path, sizeof (path), "/tmp");
    dir_remove_trailing_separators (path);
    STRCMP_EQUAL("/tmp", path);

    snprintf (path, sizeof (path), "/tmp/");
    dir_remove_trailing_separators (path);
    STRCMP_EQUAL("/tmp", path);

    snprintf (path, sizeof (path), "/tmp///////");
    dir_remove_trailing_separators (path);
    STRCMP_EQUAL("/tmp", path);
}

/*
 * Tests functions:
 *   dir_create_home_dir
 */

TEST(CoreDir, CreateHomeDir)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_create_home_dirs
 */

TEST(CoreDir, CreateHomeDirs)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_remove_home_dirs
 */

TEST(CoreDir, RemoveHomeDirs)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_get_string_home_dirs
 */

TEST(CoreDir, GetStringHomeDirs)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_exec_on_files
 */

TEST(CoreDir, ExecOnFiles)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_search_full_lib_name_ext
 *   dir_search_full_lib_name
 */

TEST(CoreDir, SearchFullLibName)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_file_get_content
 *   dir_file_copy
 */

TEST(CoreDir, FileGetContentCopy)
{
    char *path1, *path2, *content, *content_read1, *content_read2;
    const char *content_small = "line 1\nline 2\nend";
    int length, i;
    FILE *f;

    /* file not found */
    LONGS_EQUAL(0, dir_file_copy (NULL, NULL));
    LONGS_EQUAL(0, dir_file_copy ("", ""));
    LONGS_EQUAL(0, dir_file_copy ("/tmp/does/not/exist.xyz", "/tmp/test.txt"));

    path1 = string_eval_path_home ("${weechat_data_dir}/test_content_file1.txt",
                                   NULL, NULL, NULL);
    path2 = string_eval_path_home ("${weechat_data_dir}/test_content_file2.txt",
                                   NULL, NULL, NULL);

    /* small file */
    length = strlen (content_small);
    f = fopen (path1, "wb");
    fwrite (content_small, 1, length, f);
    fclose (f);
    LONGS_EQUAL(1, dir_file_copy (path1, path2));
    content_read1 = dir_file_get_content (path1);
    content_read2 = dir_file_get_content (path2);
    STRCMP_EQUAL(content_small, content_read1);
    MEMCMP_EQUAL(content_read1, content_read2, length);
    free (content_read1);
    free (content_read2);
    unlink (path1);
    unlink (path2);

    /* bigger file: 26 lines of 5000 bytes */
    length = 26 * 5001;
    content = (char *)malloc (length + 1);
    CHECK(content);
    for (i = 0; i < 26; i++)
    {
        memset (content + (i * 5001), 'a' + i, 5000);
        content[(i * 5001) + 5000] = '\n';
    }
    content[26 * 5001] = '\0';
    f = fopen (path1, "wb");
    fwrite (content, 1, length, f);
    fclose (f);
    LONGS_EQUAL(1, dir_file_copy (path1, path2));
    content_read1 = dir_file_get_content (path1);
    content_read2 = dir_file_get_content (path2);
    STRCMP_EQUAL(content, content_read1);
    MEMCMP_EQUAL(content_read1, content_read2, length);
    free (content_read1);
    free (content_read2);
    unlink (path1);
    unlink (path2);
    free (content);
}

/*
 * Tests functions:
 *   dir_file_compress_gzip
 */

TEST(CoreDir, FileCompressGzip)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_file_compress_zstd
 */

TEST(CoreDir, FileCompressZstd)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_file_compress
 */

TEST(CoreDir, FileCompress)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   dir_file_compare
 */

TEST(CoreDir, FileCompare)
{
    char *path1, *path2, *content;
    const char *content_small = "line 1\nline 2\nend";
    int length, i;
    FILE *f;

    /* file not found */
    LONGS_EQUAL(2, dir_file_compare (NULL, NULL));
    LONGS_EQUAL(2, dir_file_compare ("", ""));
    LONGS_EQUAL(2, dir_file_compare ("/tmp/does/not/exist1.xyz", "/tmp/does/not/exist2.xyz"));

    path1 = string_eval_path_home ("${weechat_data_dir}/test_compare_file1.txt",
                                   NULL, NULL, NULL);
    path2 = string_eval_path_home ("${weechat_data_dir}/test_compare_file2.txt",
                                   NULL, NULL, NULL);

    /* small file */
    length = strlen (content_small);
    f = fopen (path1, "wb");
    fwrite (content_small, 1, length, f);
    fclose (f);
    f = fopen (path2, "wb");
    fwrite (content_small, 1, length, f);
    fclose (f);
    LONGS_EQUAL(0, dir_file_compare (path1, path2));
    f = fopen (path1, "ab");
    fwrite ("A", 1, 1, f);
    fclose (f);
    f = fopen (path2, "ab");
    fwrite ("B", 1, 1, f);
    fclose (f);
    LONGS_EQUAL(1, dir_file_compare (path1, path2));

    /* bigger file: 26 lines of 5000 bytes + 1 byte */
    length = 26 * 5001;
    content = (char *)malloc (length + 1);
    CHECK(content);
    for (i = 0; i < 26; i++)
    {
        memset (content + (i * 5001), 'a' + i, 5000);
        content[(i * 5001) + 5000] = '\n';
    }
    content[26 * 5001] = '\0';
    f = fopen (path1, "wb");
    fwrite (content, 1, length, f);
    fclose (f);
    f = fopen (path2, "wb");
    fwrite (content, 1, length, f);
    fclose (f);
    LONGS_EQUAL(0, dir_file_compare (path1, path2));
    f = fopen (path1, "ab");
    fwrite ("A", 1, 1, f);
    fclose (f);
    f = fopen (path2, "ab");
    fwrite ("B", 1, 1, f);
    fclose (f);
    LONGS_EQUAL(1, dir_file_compare (path1, path2));

    unlink (path1);
    unlink (path2);
}
