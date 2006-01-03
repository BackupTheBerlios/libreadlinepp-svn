CLEANFILES = html/*
MAINTAINERCLEANFILES = Makefile.in Doxyfile *~
EXTRA_DIST = Doxyfile.in header.html footer.html doxygen.css

doxygen: Doxyfile
	@rm -fr html
	@doxygen
