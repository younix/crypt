/*
 * Copyright (c) 2013 Jan Klemkow <j.klemkow@wemelug.de>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void
gen_table(char table[26][26], char rtable[26][26])
{
	char *abc = "abcdefghijklmnopqrstuvwxyz";

	for (int y = 0; y < 26; y++) {
		for (int x = 0; x < 26; x++) {
			table[y][x]  = abc[x + y < 26 ? x + y: x + y - 26];
			rtable[y][x] = abc[x - y >= 0 ? x - y: x - y + 26];
		}
	}
}

void
usage(void)
{
	fprintf(stderr, "usage: polybios [-dh] {-p PASSWORD | -t}\n"
			"\n"
			"OPTIONS\n"
			"\t-d\tdecode\n"
			"\t-p\tpassword\n"
			"\t-t\tprint lookup table\n"
			"\t-h\tshow this help message\n");

	exit(EXIT_FAILURE);
}

int
main(int argc, char**argv)
{
	int c, p, decode_flag = 0, ch;
	char *password = NULL;
	char table[26][26], rtable[26][26];

	gen_table(table, rtable);

	while ((ch = getopt(argc, argv, "dp:th")) != -1) {
		switch (ch) {
		case 'd':
			decode_flag = 1;
			break;
		case 'p':
			password = strdup(optarg);
			for (int i = 0; i < strlen(password); i++) {
				if (isalpha(password[i])) {
					password[i] = tolower(password[i]);
				} else {
					fprintf(stderr,
					    "wrong charater in password!\n");
					return EXIT_FAILURE;
				}
			}
			break;
		case 't':
			for (int y = 0; y < 26; y++) {
				for (int x = 0; x < 26; x++) 
					printf("%c ", table[y][x]);

				printf("\n");
			}
			return EXIT_SUCCESS;
		case 'h':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (password == NULL)
		usage();

	printf("pass: %s\n", password);

	while ((c = getchar()) != EOF) {
		if (!decode_flag && isalpha(c)) {	/* encoding */
			c = table[tolower(password[p]) - 'a'][tolower(c) - 'a'];
			printf("%c", c);
			p++;
		} else if (decode_flag && isalpha(c)) {	/* decoding */
			c = rtable[tolower(password[p]) - 'a'][tolower(c) -'a'];
			printf("%c", c);
			p++;
		} else	{
			putchar(c);
		}

		if (p > strlen(password) - 1)
			p = 0;
	}

	return EXIT_SUCCESS;
}
