.PHONY:  all  alltest  clean  cleantest  test

all:
	$(MAKE) -C  src

alltest:
	$(MAKE) -C  test

clean:
	$(MAKE) -C  src  clean

cleantest:
	$(MAKE) -C  test  clean


DIR_NAME = dcel
ARCHIVE  = dcel

DATE	=	$(shell date +"_%G%m%d_%H%M%S")


zip:  clean  cleantest
	@rm  -frv  ../$(ARCHIVE).zip
	cd ..  &&  zip  -9 -r  $(ARCHIVE)$(DATE).zip  $(DIR_NAME)/

unzip:
	unzip  $(ARCHIVE).zip  -d .
