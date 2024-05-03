# info@stce.rwth-aachen.de

all :
	cd sphere && make
	cd sphere/visualization && make
	cd sphere/ad && make
	cd polynomial && make
	cd polynomial/visualization && make
	cd polynomial/ad && make

test :
	cd sphere && make test
	cd sphere/ad && make test
	cd polynomial && make test
	cd polynomial/ad && make test
depend :
	cd sphere && make depend
	cd sphere/visualization && make depend
	cd sphere/ad && make depend
	cd polynomial && make depend
	cd polynomial/visualization && make depend
	cd polynomial/ad && make depend

clean :
	cd sphere && make clean
	cd sphere/visualization && make clean
	cd sphere/ad && make clean
	cd polynomial && make clean
	cd polynomial/visualization && make clean
	cd polynomial/ad && make clean


.PHONY: all test depend clean
