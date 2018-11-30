#define PROT_NONE      0b0000
#define PROT_READ      0b0001
#define PROT_WRITE     0b0010
#define PROT_EXEC      0b0100

#define MAP_SHARED     0b0001
#define MAP_PRIVATE    0b0010
#define MAP_ANONYMOUS  0b0100

#define MAP_FAILED ((void*) - 1)

#define EINVAL 1 // 錯誤參數
#define EACCES 2 // 沒有權限
#define ENXIO  3 //錯誤地址

