#ifndef ERROR_H
#define ERROR_H
typedef enum {
  RET_SUCCESS = 0,
  RET_ERR_PARAMS,
  RET_ERR_BUFFER,
  RET_ERR_ALLOC,
  RET_ERR_OTHER
} Status_t;
#endif