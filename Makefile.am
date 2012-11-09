AUTOMAKE_OPTIONS = foreign subdir-objects

#lib_LTLIBRARIES = libepd.la

CXXFLAGS = -Wall -pedantic -g
libepdinclude_HEADERS = $(shell find hdr -name "*.h")
#libepd_la_SOURCES = $(shell find src -name "*.cpp")
libepdincludedir = $(includedir)/EPD
libepddir = src
libepd_LIBRARIES = libepd.a
libepd_a_SOURCE = $(shell find src -name "*.cpp")
