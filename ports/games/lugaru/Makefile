# $OpenBSD$

COMMENT =		rabbit fighting game

V =			rev269
DISTNAME =		lugaru-$V-src
PKGNAME =		lugaru-1.0
CATEGORIES=		games
EXTRACT_SUFX =		.tar.bz2

HOMEPAGE =		http://www.wolfire.com/lugaru/
MASTER_SITES =		https://lugaru.googlecode.com/files/

# GPLv2 or later
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES =		devel/cmake

WANTLIB =		c ogg m pthread vorbis vorbisfile SDL GL GLU ICE SM X11 Xext stdc++ z png openal jpeg

LIB_DEPENDS =		audio/libvorbis \
			devel/sdl \
			graphics/png \
			graphics/jpeg \
			audio/openal

NO_TEST=	Yes
post-install:
	echo "cd /usr/local/lugaru\n/usr/local/lugaru/lugaru\ncd -" > /usr/local/bin/lugaru
	chmod +x /usr/local/bin/lugaru

.include <bsd.port.mk>
