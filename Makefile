CXX=g++
LD=g++
CFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb
OBJECTS=ui_form.o ui_menu.o ui_window.o ftp_commander.o ftp_thread.o ftp_core.o local_panel.o remote_panel.o main.o


all: doc compile

main.o: src/main.cpp src/ui_menu.h src/ui_window_intestines.h src/ftp_commander.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ui_form.o: src/ui_form.cpp src/ui_form.h src/ui_window_intestines.h
	$(CXX) $(CFLAGS) -lform -c -o $@ $<

ui_menu.o: src/ui_menu.cpp src/ui_menu.h src/ui_window_intestines.h
	$(CXX) $(CFLAGS) -lncurses -lmenu -c -o $@ $<

local_panel.o: src/local_panel.cpp src/functions.h src/local_panel.h src/ui_window.h src/ui_window_intestines.h
	$(CXX) $(CFLAGS) -lncurses -lmenu -c -o $@ $<

remote_panel.o: src/remote_panel.cpp src/functions.h src/ftp_commander.h src/local_panel.h src/ui_window.h src/ui_window_intestines.h
	$(CXX) $(CFLAGS) -lncurses -c -o $@ $<

ui_window.o: src/ui_window.cpp src/ui_window.h src/ui_window_intestines.h
	$(CXX) $(CFLAGS) -lncurses -c -o $@ $<

functions.o: src/functions.cpp src/functions.h
	$(CXX) $(CFLAGS) -lncurses -c -o $@ $<

ftp_core.o: src/ftp_core.cpp src/ftp_core.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ftp_commander.o: src/ftp_commander.cpp src/ftp_commander.h src/ftp_thread.h src/ftp_core.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ftp_thread.o: src/ftp_thread.cpp src/ftp_thread.h src/ftp_core.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ftp_main.o: src/ftp_main.cpp src/ftp_commander.h src/ftp_core.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ftp-main: ftp_main.o ftp_commander.o ftp_core.o ftp_thread.o 
	$(LD) $(CFLAGS) -lpthread -o ftp-main ftp_commander.o ftp_core.o ftp_thread.o ftp_main.o

compile: $(OBJECTS) 
	$(LD) $(CFLAGS) -lpthread -lform -lmenu -o suslasam $(OBJECTS)

valgrind:
	valgrind --leak-check=yes --log-file=valgrind.log -v ./suslasam

run:
	./suslasam

clean:
	rm -rf ui_form.o ui_menu.o ui_window.o ftp_commander.o ftp_core.o ftp_thread.o local_panel.o remote_panel.o main.o suslasam ftp_main.o doc valgrind.log

doc:
	doxygen Doxyfile

count:
	cat src/*.cpp src/*.h | awk 'BEGIN {counter=0}{ if ( length($0) != 0 ){counter++}} END {print "Number of lines in your project is: " counter}'

