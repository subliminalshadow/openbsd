# $OpenBSD$

COMMENT =	emerald window decorator

V =		0.8.8
DISTNAME =	emerald-${V}
REVISION =	0

MASTER_SITES =	http://releases.compiz.org/${V}/

LIBTOOL_FLAGS =	--tag=disable-static

BUILD_DEPENDS = devel/libtool \
		devel/libwnck

RUN_DEPENDS =	x11/compiz/core

CONFIGURE_STYLE = gnu
CONFIGURE_ENV =	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib" \
		CC="gcc -liberty"

PKG_CREATE_NO_CHECKS=	Yes

.include <bsd.port.mk>
