#include <iostream>
#include <stdio.h>
#include <expat.h>
#include <cstring>

#include "../include/names.h"

int Depth;

struct human_s {
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];

    human_s() {
        for (int i = 0; i < 10; i++) {
            phones[i][0] = 0;
        }
    }
};

struct phonebook_s {
    human_s *humans;
    size_t size;
    size_t capacity;
};

struct user_data_s {
    // phone book
    phonebook_s * phonebook;

    // tmp name, middle_name and family_name
    char * name;
    char * middle_name;
    char * family_name;

    // tmp string buffer
    char * buffer;

    // list of tmp phones and his size
    char phone[10][21];
    int cur_phone;

    // XML is correct
    int err;
};

// push human back in phonebook
void push_back_human(phonebook_s * book, human_s * human) {

    // if book size is equals book capacity
    if (book->size == book->capacity) {
        // increase capacity
        if (book->capacity) {
            book->capacity *= 2;
            book->humans = (human_s *)realloc(book->humans, book->capacity * sizeof(human_s));
        } else {
            book->capacity = 10;
            book->humans = (human_s *)malloc(book->capacity * sizeof(human_s));
        }
    }

    // add new person
    book->humans[book->size++] = *human;
}

// call if we meet an opening tag
void start(void * data, const char * elem, const char ** attr) {
    // increase level
    Depth++;

    // get pointer to user data
    user_data_s * user_data = (user_data_s *)data;

    // if we have already get error then we'll do nothing
    if (user_data->err) return;

    // if open tag is "phone"
    if (!strcmp(elem, "phone")) {

        // if we aint in level #3 then create error
        if (Depth != 3) user_data->err = 1;

        return;
    }

    // if open tag is "human"
    if (!strcmp(elem, "human")) {

        // if we aint in level #2 then create an error and exit
        if (Depth != 2) {
            user_data->err = 2;
            return;
        }

        // if we have not an attr or we have other attr
        if (!attr[0] || strcmp(attr[0], "name")) {
            user_data->err = 2;
            return;
        }

        // if we have no attr[1] or attr[1] is too big
        if (!attr[1] || strlen(attr[1]) >= 1024) {
            user_data->err = 2;
            return;
        }

        // if we have other attr
        if (attr[2]) {
            user_data->err = 2;
            return;
        }

        // copy name attr to buffer
        strncpy(user_data->buffer, attr[1], 1024);

        // get name
        user_data->name = strtok(user_data->buffer, " ");

        // if name is exist
        if (!user_data->name || strlen(user_data->name) > 255) {
            user_data->err = 2;
            return;
        }

        // get middle name
        user_data->middle_name = strtok(NULL, " ");

        // if middle is exist
        if (!user_data->middle_name || strlen(user_data->middle_name) > 255) {
            user_data->err = 2;
            return;
        }

        // get family_name
        user_data->family_name = strtok(NULL, " ");

        // if family_name is exist
        if (!user_data->family_name || strlen(user_data->family_name) > 255) {
            user_data->err = 2;
            return;
        }

        // if name attr has something else
        if (strtok(NULL, " ")) {
            user_data->err = 2;
            return;
        }

        return;
    }

    // if open tag is "phonebook"
    if (!strcmp(elem, "phonebook")) {

        // if we aint in level #3 then create an error
        if (Depth != 1) user_data->err = 3;

        return;
    }

    // if open tag has other name create an error
    user_data->err = 1;
}

// get human from user data
void get_human_from_user_data(human_s * human, user_data_s * user_data) {
    strcpy(human->name, user_data->name);
    strcpy(human->middle_name, user_data->middle_name);
    strcpy(human->family_name, user_data->family_name);

    for (int i = 0; i < 10; i++) {
        strcpy(human->phones[i], user_data->phone[i]);
        printf("%s\n", human->phones[i]);
    }
}

// call if we meet a closing tag
void end(void * data, const char * elem) {
    // decrease level
    Depth--;

    // is we aint at level #1
    if (Depth != 1) return;

    user_data_s * user_data = (user_data_s *)data;

    // if closing tag aint "human"
    if (strcmp(elem, "human")) {
        user_data->err = 2;
    }

    // if we already have error
    if (user_data->err) {
        return;
    }

    // create tmp human
    human_s * tmp_human = (human_s *)malloc(sizeof(human_s));

    // get user from user data
    get_human_from_user_data(tmp_human, user_data);

    // push human back to phonebook
    push_back_human(user_data->phonebook, tmp_human);

    // delete tmp human
    free(tmp_human);

    // prepare user data for new human
    user_data->cur_phone = 0;
    for (int i = 0; i < 10; i++) {
        user_data->phone[i][0] = 0;
    }
}

// check is str is phone
bool is_phone(const char * value, int len) {
    // if len == 0 or len > 20
    if (!len || len > 20) {
        return false;
    }

    for (std::size_t i = 0; i < len; i++) {

        // if symbol aint number then return false
        if (value[i] < '0' || value[i] > '9') {
            return false;
        }

    }

    return true;
}

// copy str with fix len into another str
void strcpy_wo_end(char * dist, const char * src, int len) {
    for (int i = 0; i < len; i++) {

        //copy symbol
        dist[i] = src[i];

    }

    // src has no end symbol
    dist[len] = 0;
}

// call if we are inside of tag
void value(void * data, const char * value, int len) {
    
    // if aint at level #3 return
    if (Depth != 3) return;
    
    printf("%d\n", len);

    user_data_s * user_data = (user_data_s *)data;

    // if we have already have an error -- return
    if (user_data->err) return;

    // check if value is phone
    if (!is_phone(value, len)) {
        user_data->err = 3;
        return;
    }

    if (user_data->cur_phone == 10) {
        user_data->err = 3;
        return;
    }
    
    strcpy_wo_end(user_data->phone[user_data->cur_phone], value, len);
    user_data->cur_phone += 1;
}

// init phonebook
void init_phonebook(phonebook_s * phonebook) {
    phonebook->humans = NULL;

    // set capacity to 0
    phonebook->capacity = 0;

    // set size to 0
    phonebook->size = 0;
}

// init user data
void init_user_data(user_data_s * user_data, phonebook_s * phonebook) {
    // link user data's phonebook and our phonebook
    user_data->phonebook = phonebook;

    // set buffer size to 1024
    user_data->buffer = (char *)malloc(1024 * sizeof(char));

    // set phone's counter to 0
    user_data->cur_phone = 0;

    // set err to 0
    user_data->err = 0;
    
    for (int i = 0; i < 10; i++) {
        user_data->phone[i][0] = 0;
    }
}

//print phonebook
void print_phonebook(phonebook_s * book) {
    printf("%d\n", (int)book->size);

    for (int i = 0; i < (int)book->size; i++) {
        printf("name: %s\n", book->humans[i].name);
        printf("middle name: %s\n", book->humans[i].middle_name);
        printf("family name: %s\n", book->humans[i].family_name);

        for (int j = 0; j < 10 && book->humans[i].phones[j][0]; j++) {
            printf("phone: %s\n", book->humans[i].phones[j]);
        }

        printf("\n");
    }
}

void clear_phonebook(phonebook_s * book) {
    if (book->humans != NULL) free(book->humans);

    book->size = 0;
    book->capacity = 0;
}

int load_phonebook(const char * filename, phonebook_s * phonebook) {
    Depth = 0;
    
    // try to open XML file
    FILE * file = fopen(filename, "r");

    // if troubles with files
    if (file == NULL) {
        return 1;
    }

    // create new parser
    XML_Parser parser = XML_ParserCreate(NULL);

    // set start and end tag functions
    XML_SetElementHandler(parser, start, end);

    // set value tag function
    XML_SetCharacterDataHandler(parser, value);

    // create new user data
    user_data_s * user_data = (user_data_s *)malloc(sizeof(user_data_s));

    // init user data
    init_user_data(user_data, phonebook);

    // set parser's user data to user data
    XML_SetUserData(parser, user_data);

    size_t len = 0; // len of symbols are read
    size_t buf_len = 100000; // size of buffer
    char buffer[buf_len]; // buffer

    // parsing when file is not empty
    while ((len = fread(buffer, sizeof(char), buf_len, file))) {

        // check if XML file is correct
        if (0 == XML_Parse(parser, buffer, len, len < buf_len)) {
            int code = XML_GetErrorCode(parser);
            const char * msg = (const char *)XML_ErrorString((XML_Error)code);
            fprintf(stderr, "Parsing error code %d message %s\n", code, msg);
            break;
        }
    }

    // save error
    int err = user_data->err;
    
    // free user data
    free(user_data->buffer);
    free(user_data);

    fclose(file);

    // free parser
    XML_ParserFree(parser);

    return err;
}

int save_phonebook(const char * filename, phonebook_s * phonebook) {
    FILE * file = fopen(filename, "w");

    if (file == NULL) {
        return 1;
    }

    fprintf(file, "<phonebook>\n");

    for (int i = 0; i < phonebook->size; i++) {
        fprintf(file, "\t<human name=\"%s %s %s\">\n",
               phonebook->humans[i].name,
               phonebook->humans[i].middle_name,
               phonebook->humans[i].family_name);

        for (int j = 0; phonebook->humans[i].phones[j][0] && j < 10; j++) {
            fprintf(file, "\t\t<phone>%s</phone>\n", phonebook->humans[i].phones[j]);
        }

        fprintf(file, "\t</human>\n");
    }

    fprintf(file, "</phonebook>");

    fclose(file);

    return 0;
}

void gen_phonebook(phonebook_s * phonebook, size_t size) {
    clear_phonebook(phonebook);

    human_s * tmp_human = (human_s *)malloc(sizeof(human_s));

    int number_phones = 0, len_phone = 0;
    for (size_t i = 0; i < size; i++) {
        strcpy(tmp_human->name, kNames[rand() % NAMES_CNT]);
        strcpy(tmp_human->middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        strcpy(tmp_human->family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);

        number_phones = 1 + rand() % 10;
        for (int k = 0; k < number_phones; k++) {
            len_phone = 1 + rand() % 20;
            for (int j = 0; j < len_phone; j++) {
                tmp_human->phones[k][j] = (char)('0' + rand() % 10);
            }
            tmp_human->phones[k][len_phone] = 0;
        }

        for (int k = number_phones; k < 10; k++) {
            tmp_human->phones[k][0] = 0;
        }

        push_back_human(phonebook, tmp_human);
    }

    free(tmp_human);
}

human_s get_human(phonebook_s * book, char * family_name) {
    for (int i = 0; i < book->size; i++) {
        if (!strcmp(book->humans[i].family_name, family_name)) {
            return book->humans[i];
        }
    }

    human_s new_human;

    strcpy(new_human.family_name, family_name);

    return new_human;
}

int compare(const void * first, const void * second) {
    return strcmp(((human_s *)first)->family_name, ((human_s *)second)->family_name);
}

int main(int argc, char ** argv) {

    srand((unsigned int)time(NULL));

    phonebook_s *phonebook = (phonebook_s *)malloc(sizeof(phonebook_s));

    init_phonebook(phonebook);

    int err = load_phonebook(argv[1], phonebook);

    if (err) {
        printf("File aint exist or aint correct\n");
    } else {
        qsort(phonebook->humans, phonebook->size, sizeof(human_s), &compare);
        print_phonebook(phonebook);
    }

    gen_phonebook(phonebook, (size_t)(1 + rand() % 100));

    qsort(phonebook->humans, phonebook->size, sizeof(human_s), &compare);

    save_phonebook(argv[2], phonebook);

    clear_phonebook(phonebook);

    free(phonebook);

    return 0;
}
