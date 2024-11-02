all: wireminnow
    
wireminnow-part6: wireminnow.c includes/minnow_helpers.h
	gcc -o wireminnow wireminnow.c includes/minnow_helpers.h

.PHONY: clean

clean: 
	rm -f wireminnow

