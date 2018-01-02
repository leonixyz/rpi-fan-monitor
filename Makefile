# Install WiringPi library http://wiringpi.com/
# build monitor.c and install new systemd unit
#

uninstall:
	git clone git://git.drogon.net/wiringPi;		\
	cd wiringPi;						\
	make uninstall;						\
	sudo rm /usr/sbin/fand;					\
	sudo rm /usr/lib/systemd/system/fand.service;		\
	sudo rm /etc/systemd/system/multi-user.target.wants/fand.service

clean:
	rm -fr wiringPi;					\
	rm fand

all:
	git clone git://git.drogon.net/wiringPi;		\
	cd wiringPi;						\
	./build;						\
	cd ..;							\
	gcc -Wall -o fand fand.c -lwiringPi

install:
	sudo cp fand /usr/sbin;					\
	sudo cp fand.service /usr/lib/systemd/system/
