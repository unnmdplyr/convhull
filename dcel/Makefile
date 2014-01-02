.PHONY:  all
all:
	$(MAKE) -C  src

.PHONY:  alltest
alltest:
	$(MAKE) -C  test

.PHONY:  clean
clean:
	$(MAKE) -C  src  clean

.PHONY:  cleantest
cleantest:
	$(MAKE) -C  test  clean


.PHONY:  test
test:
	$(MAKE) -C	src		test
	$(MAKE) -C	test	test
