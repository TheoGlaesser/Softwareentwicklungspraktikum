# info@stce.rwth-aachen.de

all :
	cd sphere && make
	cd sphere/visualization && make
	cd sphere/ad && make
	cd hilbert && make
	cd hilbert/visualization && make
	cd hilbert/ad && make
	cd tridiagonal && make
	cd tridiagonal/visualization && make
	cd tridiagonal/ad && make
	cd diagDominant && make
	cd diagDominant/visualization && make
	cd diagDominant/ad && make


test :
	cd sphere && make test
	cd sphere/ad && make test
	cd hilbert && make test
	cd hilbert/ad && make test
	cd tridiagonal && make test
	cd tridiagonal/ad && make test
	cd diagDominant && make test
	cd diagDominant/ad && makde test

depend :
	cd sphere && make depend
	cd sphere/visualization && make depend
	cd sphere/ad && make depend
	cd hilbert && make depend
	cd hilbert/visualization && make depend
	cd hilbert/ad && make depend
	cd tridiagonal && make depend
	cd tridiagonal/visualization && make depend
	cd tridiagonal/ad && make depend
	cd diagDominant && make depend
	cd diagDominant/visualization && make depend
	cd diagDominant/ad && make depend


clean :
	cd sphere && make clean
	cd sphere/visualization && make clean
	cd sphere/ad && make clean
	cd hilbert && make clean
	cd hilbert/visualization && make clean
	cd hilbert/ad && make clean
	cd tridiagonal && make clean
	cd tridiagonal/visualization && make clean
	cd tridiagonal/ad && make clean
	cd diagDominant && make clean
	cd diagDominant/visualization && make clean
	cd diagDominant/ad && make clean


.PHONY: all test depend clean
