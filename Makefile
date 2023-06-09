TARGET = 3DViewer_v1.0
TEST = test
DIST_NAME = 3DViewer-v1.0

OS := $(shell uname -s)

RM = rm -f
MKDIR = mkdir -p
RMDIR = rm -rf
CP = cp -rf

VIEWER_PATHES = ./viewer/src \
                ./viewer/include \
                ./viewer/Makefile
VIEWER_TESTS_PATHES = ./viewer_tests/src \
                      ./viewer_tests/include \
                      ./viewer_tests/Makefile
VIEWER_GUI_PATHES = ./viewer_gui/C8_3DViewer_SRC.pro \
                    ./viewer_gui/main.cpp \
                    ./viewer_gui/mainwindow.cpp \
                    ./viewer_gui/mainwindow.h \
                    ./viewer_gui/mainwindow.ui \
                    ./viewer_gui/oglwindow.cpp \
                    ./viewer_gui/oglwindow.h \
					./viewer_gui/gifLib
             
all: $(TARGET)

$(TEST):
	make -sC ./viewer_tests/ all

install: $(TARGET)
	$(RMDIR) build
	mkdir build
ifeq ($(OS), Linux)
	mv viewer_gui/C8_3DViewer_SRC build
endif
ifeq ($(OS), Darwin)
	mv viewer_gui/C8_3DViewer_SRC.app build
endif

uninstall:
	rm -rf build

$(TARGET): viewer_gui/Makefile
	make -sC ./viewer/ all
	make -sC ./viewer_gui/ all
	
viewer_gui/Makefile:
	cd viewer_gui && qmake6

gcov_report:
	make -sC ./viewer_tests/ gcov_report
	gcov ./viewer/gcov_obj/*/*.gcno
	mkdir -p coverage
	mv *.gcov ./coverage
	lcov -c  -t lcove-coverage -o coverage/coverage.info -d viewer/gcov_obj
	genhtml -o coverage coverage/coverage.info
	
dist:
	@$(MKDIR) $(DIST_NAME) $(DIST_NAME)/viewer \
			  $(DIST_NAME)/viewer_gui $(DIST_NAME)/viewer_tests
	$(CP) $(VIEWER_PATHES) $(DIST_NAME)/viewer
	$(CP) $(VIEWER_TESTS_PATHES) $(DIST_NAME)/viewer_tests
	$(CP) $(VIEWER_GUI_PATHES) $(DIST_NAME)/viewer_gui
	$(CP) misc Makefile $(DIST_NAME)
	tar -czvf $(DIST_NAME).tar.gz $(DIST_NAME)
	$(RMDIR) $(DIST_NAME)

dvi: ./misc/docs/3DViewer.texi
	texi2dvi $<
	$(RM) 3DViewer.aux 3DViewer.cp 3DViewer.log 3DViewer.toc 3DViewer.cps
#	dvipdfmx 3DViewer.dvi
#	open 3DViewer.pdf 

clean: viewer_gui/Makefile
	make -sC ./viewer/ clean
	make -sC ./viewer_tests/ clean
	make -sC ./viewer_gui/ clean
	$(RM) ./viewer_gui/.qmake.stash
	@$(RM) ./viewer_gui/C8_3DViewer_SRC
	@$(RM) ./viewer_gui/Makefile
	$(RM) -r ./coverage
	$(RM) $(DIST_NAME).tar.gz
	$(RMDIR) build
	$(RM) 3DViewer.dvi 3DViewer.pdf

re: clean all

format:
	make -sC ./viewer/ format
	make -sC ./viewer_tests/ format

.PHONY: all clean re format test dist install uninstall dvi

