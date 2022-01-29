TARGET=build

main: target_dir cstring.h wstring.h rest

target_dir:
	mkdir -p $(TARGET)

cstring.h: target_dir
	prep -D string_name=cstring -D char_type=char -i src/string.h -o $(TARGET)/cstring.h

wstring.h: target_dir
	prep -D string_name=wstring -D char_type=wchar_t -i src/string.h -o $(TARGET)/wstring.h

rest: target_dir
	cp src/vector.h $(TARGET)/vector.h
	cp src/hashmap.h $(TARGET)/hashmap.h
