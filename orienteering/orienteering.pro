TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cli.cpp \
    main.cpp \
    parser.cpp \
    routes.cpp

HEADERS += \
    routes.hh \
    cli.hh \
    parser.hh
