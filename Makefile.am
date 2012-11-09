AUTOMAKE_OPTIONS = foreign subdir-objects

lib_LTLIBRARIES = libepd.la

CXXFLAGS = -Wall -pedantic -g
libepdinclude_HEADERS = $(wildcard hdr/*h)
libepd_la_SOURCES = $(shell find src -name "*.cpp")
libepdincludedir = $(includedir)/EPD

#libedp_LIBRARIES = libedp.a
#libedp_a_SOURCE = $(shell find src -name "*.cpp")
