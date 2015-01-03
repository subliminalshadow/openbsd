# $OpenBSD$

COMMENT =	fast and fun First-Person-Shooter

V =		1.2.0.2
DISTNAME = 	AssaultCube_v$V
PKGNAME =	assaultcube-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tar.bz2

HOMEPAGE =	http://assault.cubers.net/

MASTER_SITES =	${MASTER_SITE_SOURCEFORGE:=actiongame/}

# zlib license
PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes

RUN_DEPENDS = devel/sdl-image \
		audio/libvorbis \
		audio/openal \
		net/enet

WRKSRC =	${WRKDIST}/source/src

NO_TEST =	Yes
USE_GMAKE =	Yes

MAKE_FLAGS +=	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib" \
		CXX="${CXX}"

DATADIR =	${PREFIX}/assaultcube

SUBST_VARS +=	DATADIR

pre-configure:
	cp ${FILESDIR}/assaultcube.sh ${WRKSRC}/
	${SUBST_CMD} ${WRKSRC}/assaultcube.sh
	sed -e 's!/libexec/assaultcube!&-server!' ${WRKSRC}/assaultcube.sh \
	    > ${WRKSRC}/assaultcube-server.sh

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/ac_client ${PREFIX}/libexec/assaultcube
	${INSTALL_PROGRAM} ${WRKSRC}/ac_server ${PREFIX}/libexec/assaultcube-server
	${INSTALL_SCRIPT} ${WRKSRC}/assaultcube.sh ${PREFIX}/bin/assaultcube
	${INSTALL_SCRIPT} ${WRKSRC}/assaultcube-server.sh ${PREFIX}/bin/assaultcube-server
	${INSTALL_DATA_DIR} ${DATADIR}
	cd ${WRKDIST} && pax -rw bot config packages ${DATADIR}
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/assaultcube
	${INSTALL_DATA} ${WRKDIST}/README.html ${PREFIX}/share/doc/assaultcube
	cd ${WRKDIST}/docs && pax -rw . ${PREFIX}/share/doc/assaultcube

.include <bsd.port.mk>
