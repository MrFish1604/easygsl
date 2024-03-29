lib/easy_gsl.a: lib/ lib/easy_vector.o lib/vect3.o lib/easy_matrix.o lib/vect2.o
	ar rvs lib/easy_gsl.a lib/easy_vector.o lib/vect3.o lib/vect2.o lib/easy_matrix.o

lib/:
	mkdir lib

lib/easy_vector.o: lib
	g++ -c src/easy_vector.cpp -Iinclude/ -o lib/easy_vector.o

lib/vect3.o: lib
	g++ -c src/vect3.cpp -Iinclude/ -o lib/vect3.o

lib/vect2.o: lib
	g++ -c src/vect2.cpp -Iinclude/ -o lib/vect2.o

lib/easy_matrix.o: lib
	g++ -c src/easy_matrix.cpp -Iinclude/ -o lib/easy_matrix.o

install: lib/easy_gsl.a /usr/include/easy_gsl/ /usr/lib/easy_gsl/
	cp include/* /usr/include/easy_gsl
	cp lib/easy_gsl.a /usr/lib/easy_gsl/

/usr/include/easy_gsl/ /usr/lib/easy_gsl/:
	mkdir /usr/include/easy_gsl/ /usr/lib/easy_gsl/

uninstall:
	rm /usr/include/easy_gsl/*
	rm /usr/lib/easy_gsl/*