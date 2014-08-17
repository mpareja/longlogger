/*
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * 1999-02-22 Arkadiusz Miśkiewicz <misiek@pld.ORG.PL>
 * - added Native Language Support
 * Sun Mar 21 1999 - Arnaldo Carvalho de Melo <acme@conectiva.com.br>
 * - fixed strerr(errno) in gettext calls
 * 2014-08-15 Mario Pareja <pareja.mario@gmail.com>
 * - only support stdin, remove size limit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <getopt.h>

#define LLVERSION "longlogger 0.0.1"

static void usage(FILE *out)
{
	fputs("\nUsage:\n", out);
	fputs(" longlogger -t <tag> [options] [<message>]\n", out);

	fputs("\nRequired:\n", out);
	fputs(" -t, --tag <tag>       mark every line with this tag\n", out);

	fputs("\nOptions:\n", out);
	fputs(" -h, --help     display this help and exit\n", out);
	fputs(" -V, --version  output version information and exit\n", out);
}

int main(int argc, char **argv)
{
	int ch;
	char *tag = NULL;
	char *msg;
	char buf[8096];

	static const struct option longopts[] = {
		{ "tag",	required_argument,  0, 't' },
		{ "version",	no_argument,	    0, 'V' },
		{ "help",	no_argument,	    0, 'h' },
		{ NULL,		0, 0, 0 }
	};

	while ((ch = getopt_long(argc, argv, "f:i::p:st:u:dTn:P:Vh",
					    longopts, NULL)) != -1) {
		switch (ch) {
			case 't':
				tag = optarg;
				break;
			case 'h':
				usage(stdout);
				exit(EXIT_SUCCESS);
			case 'V':
				printf(LLVERSION);
				exit(EXIT_SUCCESS);
			case '?':
			default:
				usage(stderr);
				exit(EXIT_FAILURE);
		}
	}

	if (tag == NULL) {
		usage(stderr);
		exit(EXIT_FAILURE);
	}

	openlog(tag, 0, 0);

	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		int len = strlen(buf);

		/* some glibc versions are buggy, they add an additional
		 * newline which is removed here.  */
		if (0 < len && buf[len - 1] == '\n')
			buf[len - 1] = '\0';

		msg = buf;
		syslog(LOG_NOTICE, "%s", msg);
	}

	closelog();
	return EXIT_SUCCESS;
}
