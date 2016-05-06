VPATH := cpp2tex/source/basic:cpp2tex/source/io:cpp2tex/source/main:cpp2tex/source
VPATH += source/flow:source/string:source/other:source/NT:source/geom:source/struct

.PHONY: all

all: reference.pdf

REFERENCESOURCE:=$(notdir $(wildcard source/*/*.cpp))
REFERENCE=$(REFERENCESOURCE:%.cpp=build/%.tex)
REFERENCETOCOPYTEX:=$(notdir $(wildcard source/*/*.tex))
REFERENCETOCOPYPS:=$(notdir $(wildcard source/*/*.ps))
REFERENCETOCOPY:=$(REFERENCETOCOPYTEX:%.tex=build/%.tex) $(REFERENCETOCOPYPS:%.ps=build/%.ps)
LIB:= build/cpp2tex.o build/abstract_data.o build/byte_array.o build/exception.o build/generic_exception.o build/string.o build/utilities.o build/buffer.o build/file.o build/iodevice.o build/ioexception.o build/printer.o build/scanner.o build/string_stream.o 

build :
	mkdir -p build

$(LIB) : | build


build/cpp2tex.exe: $(LIB)
	echo "linking [$@]..."
	g++ -O2 -Wall -o $@ $(LIB)
                                           
$(LIB) : build/%.o : %.cpp
	echo "compiling [$*]..."
	g++ -O2 -Wall -c -o $@ $<

$(REFERENCE) : | build

$(REFERENCE:%.tex=%.cutted) : build/%.cutted: %.cpp | build
	awk 'BEGIN {pr = 0;} \
    	/ *\/\/ *END *ALGO/ {pr = 0;}\
        ! / *\/\/ *NOT *ALGO/ { if (pr) print $0;}\
        / *\/\/ *BEGIN *ALGO/ {pr = 1;}' $^  | sed -e "s@/\*BOXNEXT\*/@@g"| sed -e "s@\\\\emph{\(.*\)}@\1@g" >$@

$(REFERENCE): build/%.tex: build/%.cutted build/cpp2tex.exe
	echo "cpp2tex [$*]"
	./build/cpp2tex.exe $< -o $@ -s $*

$(REFERENCETOCOPY) : build/% : %
	# cp --no-preserve=timestamp $^ $@
	cp $^ $@

#build/all.tex : |build
#	rm -f build/all.tex
#	$(foreach tmp,$(REFERENCE:build/%.tex=%),echo \\include{$(tmp)} >>build/all.tex;echo \newpage >>build/all.tex;)

build/nb.dvi: tex/nb.tex olymp.sty $(REFERENCE) $(REFERENCETOCOPY) tex/all.tex
	echo "latex [nb]"
#	latex -output-directory build/ -include-directory tex/ $< 
#	latex -output-directory build/ -include-directory tex/ $<
	latex -output-directory build/ $< 
	latex -output-directory build/ $<

reference.pdf: build/nb.dvi
	echo "dvipdf [reference]"
	dvipdfm -p a4 $< && mv nb.pdf reference.pdf

clean:
	rm -rf build reference.pdf

