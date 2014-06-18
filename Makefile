.PHONY: clean code clean-code pristine

MARKDOWN = rdiscount

CHAPTERS = \
	chap/toc.md \
	chap/preface.md \
	chap/intro.md \
	chap/hello.md \
	chap/cli_tools.md \
	chap/strings.md \
	chap/symbol.md \
	chap/hashes.md \
	chap/range.md \
	chap/vars.md \
	chap/classes_modules.md \
	chap/methods.md \
	chap/err.md \
	chap/booleans.md \
	chap/gems.md \
	chap/ref.md \
	chap/colophon.md

mruby_book.html: layout/TOP.html main.html layout/BOTTOM.html
	cat $(.ALLSRC) > $(.TARGET)

main.html: main.md
	$(MARKDOWN) $(.ALLSRC) > $(.TARGET)

main.md: $(CHAPTERS)
	cat $(.ALLSRC) > $(.TARGET)

code:
	(cd code && make all)

clean:
	rm -f main.html main.md mruby_book.html

clean-code:
	(cd code && make clean)

pristine: clean clean-code
