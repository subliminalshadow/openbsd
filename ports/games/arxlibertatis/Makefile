# $OpenBSD$

COMMENT=	open source port of Arx Fatalis

V=		1.1.2
DISTNAME=	arx-libertatis-${V}
PKGNAME=	arxlibertatis-${V}
HOMEPAGE=	http://arx-libertatis.org/
MASTER_SITES =	${MASTER_SITE_SOURCEFORGE:=arx/}
EXTRACT_SUFX =	.tar.xz

CATEGORIES=	games

NO_TEST=	Yes

WANTLIB = GL GLEW SDL c pthread freetype m openal stdc++ z
MODULES=	devel/cmake
RUN_DEPENDS=	audio/openal \
		graphics/glew \
		devel/sdl

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
CONFIGURE_ARGS = -DBUILD_CRASHREPORTER=off
CONFIGURE_ENV = CXX="g++ -lpthread" \
		CC="gcc -lpthread"
do-install:
	cp /usr/ports/pobj/${PKGNAME}/arx-libertatis-${V}/scripts/arx-install-data /usr/local/bin
	${INSTALL_PROGRAM} /usr/ports/pobj/${PKGNAME}/build-${ARCH}/arx ${PREFIX}/bin
	${INSTALL_PROGRAM} /usr/ports/pobj/${PKGNAME}/build-${ARCH}/arxsavetool ${PREFIX}/bin
	${INSTALL_PROGRAM} /usr/ports/pobj/${PKGNAME}/build-${ARCH}/arxunpak ${PREFIX}/bin
	${INSTALL_DATA}	/usr/ports/pobj/${PKGNAME}/arx-libertatis-${V}/data/man/arx.6 /usr/local/man/man6
	${INSTALL_DATA}	/usr/ports/pobj/${PKGNAME}/arx-libertatis-${V}/data/man/arxsavetool.1 /usr/local/man/man1
	${INSTALL_DATA}	/usr/ports/pobj/${PKGNAME}/arx-libertatis-${V}/data/man/arxunpak.1 /usr/local/man/man1
.include <bsd.port.mk>
