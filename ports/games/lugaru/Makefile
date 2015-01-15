# $OpenBSD$

COMMENT =		rabbit fighting game

V =			269
DISTNAME =		lugaru-rev$V-src
PKGNAME =		lugaru-$V
CATEGORIES=		games
EXTRACT_SUFX =		.tar.bz2

HOMEPAGE =		http://www.wolfire.com/lugaru/
MASTER_SITES =		https://lugaru.googlecode.com/files/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES =		devel/cmake

WANTLIB =		c ogg m pthread vorbisfile SDL GL GLU ICE SM X11 Xext stdc++ z png openal jpeg

LIB_DEPENDS =		audio/libvorbis \
			devel/sdl \
			graphics/png \
			graphics/jpeg \
			audio/openal

NO_TEST=	Yes

pre-configure:
	cp ${FILESDIR}/wrapper.sh ${WRKSRC}
post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/wrapper.sh ${PREFIX}/bin/lugaru
.include <bsd.port.mk>
