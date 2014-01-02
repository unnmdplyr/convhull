.PHONY:  all
all:
	$(MAKE) -C  dcel

.PHONY:  alltest
alltest:
	$(MAKE) -C  dcel  alltest

.PHONY:  clean
clean:
	$(MAKE) -C  dcel  clean

.PHONY:  cleantest
cleantest:
	$(MAKE) -C  dcel  cleantest



DIR_NAME = convhull
ARCHIVE  = convhull

DATE	=	$(shell date +"_%G%m%d_%H%M%S")


.PHONY:  zip
zip:  clean  cleantest
	@rm  -frv  ../$(ARCHIVE).zip
	cd ..  &&  zip  -9 -r  $(ARCHIVE)$(DATE).zip  $(DIR_NAME)/

.PHONY:  unzip
unzip:
	unzip  $(ARCHIVE).zip  -d .



.PHONY:  test
test:
	$(MAKE) -C	dcel	test
