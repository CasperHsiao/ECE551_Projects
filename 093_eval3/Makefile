myProgam: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1: cyoa-step1.cpp cyoa.o page.o
	g++ -o cyoa-step1 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step1.cpp cyoa.o page.o
cyoa-step2: cyoa-step2.cpp cyoa.o page.o
	g++ -o cyoa-step2 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step2.cpp cyoa.o page.o
cyoa-step3: cyoa-step3.cpp cyoa.o page.o
	g++ -o cyoa-step3 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step3.cpp cyoa.o page.o
cyoa-step4: cyoa-step4.cpp cyoa.o page.o
	g++ -o cyoa-step4 -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa-step4.cpp cyoa.o page.o
cyoa.o: cyoa.cpp cyoa.hpp
	g++ -o cyoa.o -c -ggdb3 -Wall -Werror -pedantic -std=gnu++98 cyoa.cpp
page.o: page.cpp page.hpp
	g++ -o page.o -c -ggdb3 -Wall -Werror -pedantic -std=gnu++98 page.cpp

.PHONY: clean

clean:
	rm -f *.o *~ cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
