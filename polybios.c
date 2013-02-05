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

void
usage(void)
{
	fprintf(stderr, "usage: polybios [-1dh]\n"
			"\n"
			"OPTIONS\n"
			"\t-1\tcoordinates from 1 to 5\n"
			"\t-d\tdecode\n"
			"\t-h\tshow this help message\n");

	exit(EXIT_FAILURE);
}

int
main(int argc, char**argv)
{
	int c, x, y;
	char table[5][5] = {	{'a', 'b', 'c', 'd', 'e'},
				{'f', 'g', 'h', 'i', 'k'},
				{'l', 'm', 'n', 'o', 'p'},
				{'q', 'r', 's', 't', 'u'},
				{'v', 'w', 'x', 'y', 'z'}};

	int decode_flag = 0, one_flag, ch;

	while ((ch = getopt(argc, argv, "1dh")) != -1) {
		switch (ch) {
		case '1':
			one_flag = 1;
			break;
		case 'd':
			decode_flag = 1;
			break;
		case 'h':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	while ((c = getchar()) != EOF) {
		if (!decode_flag && isalpha(c)) {	/* encoding */
			c = tolower(c);
			if (c > 'i')	/* i and j mapped at the same field */
				c--;

			x = (c - 'a') % 5;
			y = (c - 'a') / 5;

			if (one_flag) {
				x++;
				y++;
			}

			printf("%d%d", x, y);
		} else if (decode_flag && isdigit(c)) {		/* decoding */
			x = c - '0';
			y = getchar() - '0';

			if (one_flag) {
				x--;
				y--;
			}

			putchar(table[y][x]);
		} else	{
			putchar(c);
		}
	}

	return EXIT_SUCCESS;
}
