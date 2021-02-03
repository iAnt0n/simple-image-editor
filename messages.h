#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include "io.h"

const char* read_error_messages[] = {
        [READ_INVALID_SIGNATURE] = "Неверная сигнатура файла",
        [READ_INVALID_BITS] = "Содержимое файла не совпадает с заголовком",
        [READ_INVALID_HEADER] = "Неверный заголовок файла"
};

const char* write_error_messages[] = {
        [WRITE_ERROR] = "Ошибка записи в файл"
};

const char* open_error_messages[] = {
        [OPEN_ERROR] = "Ошибка открытия файла"
};

const char* close_error_messages[] = {
        [CLOSE_ERROR] = "Ошибка закрытия файла"
};

#endif //_MESSAGES_H_
