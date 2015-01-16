# $OpenBSD$

COMMENT =	freespace 2 open, space simulator

V =		3_7_2_RC4
DISTNAME = 	fs2_open_$V_src
PKGNAME =	fs2_open-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tgz
WRKDIST=${WRKDIR}/fs2_open_$V
WRKSRC=${WRKDIR}/fs2_open_$V

HOMEPAGE =	http://scp.indiegames.us/
MASTER_SITES =	http://swc.fs2downloads.com/builds/

# GPLv2
PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes
NO_TEST=	Yes

WANTLIB =	GL SDL c m pthread stdc++ GLU X11-xcb X11 Xau Xdamage Xdmcp Xext \
		Xfixes Xxf86vm drm glapi pthread-stubs sndio usbhid iconv jansson \
		xcb-dri2 xcb-glx xcb z lua5.1 ogg openal png theora vorbis vorbisfile \
		jpeg

BUILD_DEPENDS = devel/autoconf/2.69 \
                devel/automake/1.10 \
		devel/sdl \
		devel/jansson \
		audio/libvorbis \
		multimedia/libtheora \
		graphics/png \
		graphics/jpeg \
		audio/openal \
		lang/lua/5.1

RUN_DEPENDS =	devel/sdl \
		devel/jansson \
		audio/libvorbis \
		multimedia/libtheora \
		graphics/png \
		graphics/jpeg \
		audio/openal \
		lang/lua/5.1

AUTOCONF_VERSION=2.69
AUTOMAKE_VERSION=1.10
CONFIGURE_STYLE = gnu

pre-configure:
		cd ${WRKDIST} && ./autogen.sh

.include <bsd.port.mk>
