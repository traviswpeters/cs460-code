# NOTES:
# - STATES.txt contains all 50 states (a solution to the stategame).
# - TEST.txt contains a subset of the states (to simulate a user attempt at the stategame).
# - readline(.h/.c) are just support files for reading lines from stdin in a sane way.

CC     =  gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb #-save-temps
PROG   = stategame
OBJS   = stategame.o readline.o
LIBS   = -lm

.PHONY: play check test testdups testvalgrind clean

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

stategame.o: readline.h
readline.o: readline.h

# allow a user to play the stategame; store results in a file named 'guess'.
play:
	@echo "---------------------------------------------------------------------------------"
	@echo " *** State Game! *** (Enter each state on a separate line. Press ctrl+d to exit) "
	@echo "---------------------------------------------------------------------------------"
	@./$(PROG) > guess
	@cat guess

# use vimdiff to compare 2 files (most recent attempt with a complete solution)
check:
	tail -n +2 guess > guess_clean # remove header (line 1)
	tr '[A-Z]' '[a-z]' < STATES.txt > guess_compare # solution (normalized)
	vimdiff guess_clean guess_compare

# use input from a test file to simulate user input.
test:
	cat TEST.txt | ./$(PROG) > guess
	cat guess

# same as test, but include a bunch of duplicate entries to test that we remove those correctly.
testdups:
	cat TEST.txt TEST.txt | ./$(PROG) > guess
	cat guess

# test with `myvalgrind`
testvalgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) < TEST.txt > guess
	cat guess

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	rm -f guess*
