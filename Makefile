TARGET=.

main:
	prep -D string_name=cstring -D char_type=char -i src/string.h -o $(TARGET)/cstring.h
	prep -D string_name=wstring -D char_type=wchar_t -i src/string.h -o $(TARGET)/wstring.h
	cp src/vector.h $(TARGET)/vector.h
	cp src/hashmap.h $(TARGET)/hashmap.h
