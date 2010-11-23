include(../../shared.pri)

TEMPLATE = lib
CONFIG += create_pc create_prl
TARGET = QtSparql
DESTDIR = $$QT_BUILD_TREE/lib
DEFINES += QT_BUILD_SPARQL_LIB
DEFINES += QT_NO_USING_NAMESPACE
QT += network

DEFINES += QT_NO_CAST_FROM_ASCII

install_headers.path = $$QTSPARQL_INSTALL_HEADERS
install_headers.files = 

include($$QT_BUILD_TREE/include/QtSparql/headers.pri)

include_headers.files = $$SYNCQT.HEADER_FILES
include_headers.path = $$QTSPARQL_INSTALL_HEADERS
INSTALLS += include_headers

class_headers.files = $$SYNCQT.HEADER_CLASSES
class_headers.path = $$QTSPARQL_INSTALL_HEADERS
INSTALLS += class_headers

install_prf.path = $$[QT_INSTALL_DATA]/mkspecs/features
install_prf.files = \
    $$QT_BUILD_TREE/mkspecs/features/qtsparql.prf
install_prf.commands = \
    sed "\"s,QTSPARQL_INSTALL_HEADERS,$$QTSPARQL_INSTALL_HEADERS,g;s,QTSPARQL_INSTALL_LIBS,$$QTSPARQL_INSTALL_LIBS,g\"" $$QT_SOURCE_TREE/mkspecs/features/qtsparql.prf.in > $$QT_BUILD_TREE/mkspecs/features/qtsparql.prf

include(kernel/kernel.pri)
include(drivers/drivers.pri)
include(models/models.pri)

INSTALLS += \
        target \
        install_headers \
        install_prf
target.path = $$QTSPARQL_INSTALL_LIBS

QMAKE_PKGCONFIG_REQUIRES = QtCore QtNetwork
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_CFLAGS = -I$$QTSPARQL_INSTALL_HEADERS

coverage {
	LIBS += -lgcov
	QMAKE_CXXFLAGS += -ftest-coverage -fprofile-arcs -fno-elide-constructors
	QMAKE_EXTRA_TARGETS += coverage
	coverage.commands  = lcov -d . --capture --output-file all.cov -b . &&
	coverage.commands += lcov -e all.cov '*/*/src/sparql/*/*.cpp' -e all.cov '*/*/src/sparql/*/*.h' -o src.cov &&
	coverage.commands += genhtml -o coverage src.cov
}
