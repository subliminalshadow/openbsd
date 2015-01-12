# $OpenBSD: Makefile.template,v 1.54 2008/01/13 16:43:57 espie Exp $

COMMENT =	wide character CRT screen handling and optimization package

DISTNAME =	ncurses-5.7
PKGNAME =	ncursesw-5.7

NC_LIBVER =	0.0
.for _lib in formw menuw ncursesw panelw
SHARED_LIBS +=	${_lib} ${NC_LIBVER}
.endfor

CATEGORIES =	devel

HOMEPAGE =	http://www.gnu.org/software/ncurses/

# GPL
PERMIT_PACKAGE_CDROM =	Yes
PERMIT_PACKAGE_FTP =	Yes
PERMIT_DISTFILES_FTP =	Yes

WANTLIB =	c

MASTER_SITES =	${MASTER_SITE_GNU:=ncurses/}

CONFIGURE_STYLE =	gnu
CONFIGURE_ARGS +=	--with-shared \
			--enable-widec \
			--without-xterm-new \
			--without-progs
CONFIGURE_ENV =		NC_MAJOR=${NC_LIBVER:R} NC_MINOR=${NC_LIBVER:E}

NO_TEST =	Yes

MAKE_FLAGS =	NC_MAJOR=${NC_LIBVER:R} NC_MINOR=${NC_LIBVER:E}

post-install:
	@rm -f ${PREFIX}/lib/*.so ${PREFIX}/lib/*.so.${NC_LIBVER:R}

.include <bsd.port.mk>
