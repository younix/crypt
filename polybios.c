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

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int
main(int argc, char**argv)
{
	int c, x, y;
	char table[5][5] = {	{'a', 'b', 'c', 'd', 'e'},
				{'f', 'g', 'h', 'i', 'k'},
				{'l', 'm', 'n', 'o', 'p'},
				{'q', 'r', 's', 't', 'u'},
				{'v', 'w', 'x', 'y', 'z'}};

	while (feof(stdin) == 0) {
		c = getchar();
		if (isalpha(c)) {
			c = tolower(c);
			if (c > 'i')
				c--;

			x = (c - 'a') % 5;
			y = (c - 'a') / 5;

			printf("%d%d", x, y);
		} else	{
			putchar(c);
		}
	}

	return EXIT_FAILURE;
}
