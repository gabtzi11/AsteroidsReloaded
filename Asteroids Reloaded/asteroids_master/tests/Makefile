compile:
	gcc -std=gnu99 -o asteroid_test.o asteroid_test.c ../src/asteroid.c ../src/ship.c ../src/saucers.c ../src/collisions.c ../src/bullet.c ./unity_src/unity.c -lm -I../src/include/
	gcc -std=gnu99 -o ship_test.o ship_test.c ../src/ship.c ./unity_src/unity.c -lm -I../src/include/
	gcc -std=gnu99 -o saucers_test.o saucers_test.c ../src/saucers.c ../src/ship.c ../src/collisions.c ./unity_src/unity.c -lm -I../src/include/
	gcc -std=gnu99 -o collisions_test.o collisions_test.c ../src/collisions.c ./unity_src/unity.c -lm -I../src/include/