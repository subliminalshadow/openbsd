# $OpenBSD

COMMENT =	extra plugins for compiz

V =		0.8.8
DISTNAME =	compiz-plugins-extra-${V}
REVISION =	0

MASTER_SITES =	http://releases.compiz.org/${V}/

USE_GMAKE =	Yes

LIBTOOL_FLAGS =	--tag=disable-static

BUILD_DEPENDS = x11/compiz/bcop \
		x11/compiz/core
RUN_DEPENDS =	x11/compiz/core

CONFIGURE_STYLE = gnu
CONFIGURE_ENV =	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"

post-install:
	@rm -f ${PREFIX}/lib/compiz/*.la

.include <bsd.port.mk>
