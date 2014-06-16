.PHONY: clean

CHAPTERS = \
	chap/toc.md \
	chap/preface.md \
	chap/intro.md \
	chap/hello.md \
	chap/cli_tools.md \
	chap/symbol.md \
	chap/strings.md \
	chap/hashes.md \
	chap/vars.md \
	chap/classes_modules.md \
	chap/methods.md \
	chap/gems.md \
	chap/ref.md \
	chap/colophon.md

mruby_cookbook.html: layout/TOP.html main.html layout/BOTTOM.html
	cat $(.ALLSRC) > $(.TARGET)

main.html: main.md
	rdiscount $(.ALLSRC) > $(.TARGET)

main.md: $(CHAPTERS)
	cat $(.ALLSRC) > $(.TARGET)

clean:
	rm -f main.html main.md mruby_cookbook.html
