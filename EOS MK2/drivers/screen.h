#define VIDEO_ADDRESS 0xb8000
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xfc
#define MAX_COLS 80
#define MAX_ROWS 25

void clear_screen();
void kprint_at(char *, int, int);
void kprint(char *);
