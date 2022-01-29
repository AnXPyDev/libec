#\include <string.h>
#\include <wchar.h>
#\include <malloc.h>

mute()

ifnset(`char_type', `pushs(`char_type', `\\char')')
ifnset(`string_name', `pushs(`string_name', `\\string')')

pushs(`char_t', `#char_type')
pushs(`string_t', `#string_name\_t')
pushs(`string', `#string_name')


ifnset(`strlen_f', `
	ifeq(`#char_type', `char', `pushs(`strlen_f', `strlen')')
	ifeq(`#char_type', `wchar_t', `pushs(`strlen_f', `wcslen')')
')

unmute()

const char_t NULL_CHAR = 0;

typedef struct {
	char_t *data;
	unsigned int size;
	unsigned int capacity;
} string_t;

string_t string\_create_blank(unsigned int capacity) {
	string_t result;
	result.data = malloc(sizeof(char_t) * capacity);
	result.data[0] = NULL_CHAR;
	result.size = 0;
	result.capacity = 0;

	return result;
}

int string\_init_blank(string_t *string, unsigned int capacity) {
	string\->data = malloc(sizeof(char_t) * capacity);
	string\->data[0] = NULL_CHAR;
	string\->size = 0;
	string\->capacity = 0;
	
	return 0;
}

string_t string\_create(const char_t *source_string) {
	string_t result;
	result.size = strlen_f(source_string);
	result.capacity = result.size * 1.5;
	result.data = malloc(sizeof(char_t) * (result.capacity + 1));
	memcpy(result.data, source_string, sizeof(char_t) * (result.size + 1));

	return result;
}

int string\_init(string_t *string, const char_t *source_string) {
	string\->size = strlen_f(source_string);
	string\->capacity = string\->size * 1.5;
	string\->data = malloc(sizeof(char_t) * (string\->capacity + 1));
	memcpy(string\->data, source_string, sizeof(char_t) * (string\->size + 1));
	
	return 0;
}

string_t string\_create_copy(const string_t *source) {
	string_t result;
	result.size = source->size;
	result.capacity = source->capacity;
	result.data = malloc(sizeof(char_t) * (result.capacity + 1));
	memcpy(result.data, source->data, sizeof(char_t) * (result.size + 1));
	
	return result;
}

int string\_init_copy(string_t *string, const string_t *source) {
	string\->size = source->size;
	string\->capacity = source->capacity;
	string\->data = malloc(sizeof(char_t) * (string\->capacity + 1));
	memcpy(string\->data, source->data, sizeof(char_t) * (string\->size + 1));

	return 0;
}

int string\_destroy(string_t *string) {
	if ( string\->data != NULL ) {
		free(string\->data);
		string\->data = NULL;
	}
	string\->size = 0;
	string\->capacity = 0;

	
	return 0;
}

int string\_resize(string_t *string, unsigned int new_capacity) {
	char_t *new_data = malloc(sizeof(char_t) * (new_capacity + 1));

	if ( string\->size + 1 > new_capacity ) {
		memcpy(new_data, string\->data, sizeof(char_t) * (new_capacity - 1));
		new_data[new_capacity - 1] = NULL_CHAR;
		string\->size = new_capacity;
	} else {
		memcpy(new_data, string\->data, sizeof(char_t) * (string\->size + 1));
	}

	free(string\->data);
	string\->data = new_data;
	string\->capacity = new_capacity;

	return 0;
}

int string\_putwc(string_t *string, char_t wc) {
	if ( string\->size + 1 > string\->capacity ) {
		string\_resize(string, (string\->capacity + 1) * 1.5);
	}

	string\->data[string\->size] = wc;
	string\->size++;
	string\->data[string\->size] = NULL_CHAR;

	return 0;
}

int string\_cat(string_t *string, const string_t *other) {
	if ( string\->size + other->size > string\->capacity ) {
		string\_resize(string, string\->capacity + other->capacity);
	}
	memcpy(string\->data + string\->size, other->data, other->size + 1);
	string\->size += other->size;

	return 0;
}

int string\_cat_raw(string_t *string, const char_t *other) {
	unsigned int other_size = strlen_f(other);
	if ( string\->size + other_size > string\->capacity ) {
		string\_resize(string, string\->capacity + other_size);
	}
	memcpy(string\->data + string\->size, other, other_size + 1);
	string\->size += other_size;

	return 0;
}

int string\_set_size(string_t *string, unsigned int size) {
	string\->size = size;
	string\->data[string\->size] = NULL_CHAR;
	return 0;
}

int string\_reload_size(string_t *string) {
	string\->size = strlen_f(string\->data);
	return 0;
}

int string\_contains(const string_t *string, char_t wc) {
	for ( unsigned int i = 0; i < string\->size; i++ ) {
		if ( string\->data[i] == wc ) {
			return 1;
		}
	}

	return 0;
}

int string\_equal(const string_t *string, const string_t *other) {
	if ( string\->size != other->size ) {
		return 0;
	}

	for ( unsigned int i = 0; i < string\->size; i++ ) {
		if ( string\->data[i] != other->data[i] ) {
			return 0;
		}
	}
	
	return 1;
}

int string\_strip_trailing(string_t *string, char_t wc) {
	unsigned int new_size = string\->size;

	while ( 1 ) {
		if ( string\->data[new_size - 1] == wc ) {
			new_size--;
		} else {
			break;
		}
	}

	string\_set_size(string, new_size);
	return 0;
}


