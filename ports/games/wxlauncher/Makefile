# $OpenBSD$

COMMENT =	freespace 2 wxlauncher

V =		0.9.4
DISTNAME = 	wxlauncher-$V
PKGNAME =	wxlauncher-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tar.gz

HOMEPAGE =	https://code.google.com/p/wxlauncher/
MASTER_SITES =  http://wxlauncher.googlecode.com/files/	

# GPLv2
PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes
NO_TEST=	Yes

WANTLIB +=	GL SDL X11 c m pthread stdc++ z
BUILD_DEPENDS = devel/cmake \
		devel/sdl \
	      	lang/python/2.7 \
	      	x11/wxWidgets \
	      	textproc/markdown

CONFIGURE_ARGS = ${WRKSRC} \
		-DPYTHON_EXECUTABLE=/usr/local/bin/python2.7 \
		-DUSE_OPENAL=1 \
		-DCMAKE_INSTALL_PREFIX=${PREFIX}

pre-configure:
	cd ${WRKSRC} \
	&& cmake ${CONFIGURE_ARGS}

.include <bsd.port.mk>
