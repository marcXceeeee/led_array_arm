#ifndef __SCAN_H__
#define __SCAN_H__

#include "common.h"

#define COLOR_24BPP

#if defined(COLOR_8BPP)
#define WIDTH_RED       3
#define WIDTH_GREEN     3
#define WIDTH_BLUE      2
#define WIDTH_ALPHA     0
#define PWM_LEVELS      8
#define CHNL_DATATYPE   uint8_t
#elif defined(COLOR_12BPP)
#define WIDTH_RED       4
#define WIDTH_GREEN     4
#define WIDTH_BLUE      4
#define WIDTH_ALPHA     0
#define PWM_LEVELS      16
#define CHNL_DATATYPE   uint8_t
#elif defined(COLOR_18BPP)
#define WIDTH_RED       6
#define WIDTH_GREEN     6
#define WIDTH_BLUE      6
#define WIDTH_ALPHA     0
#define PWM_LEVELS      64
#define CHNL_DATATYPE   uint8_t
#elif defined(COLOR_24BPP)
#define WIDTH_RED       8
#define WIDTH_GREEN     8
#define WIDTH_BLUE      8
#define WIDTH_ALPHA     0
#define PWM_LEVELS      256
#define CHNL_DATATYPE   uint8_t
#else
#error COLOR gamut not configured
#endif
#define PX_MAX_VAL      (PWM_LEVELS - 1)

#define TARGET_FPS  30
#define _PWM(x,pwm) (((x) <= (pwm)) ? 0x00 : 0x01)
#define CHANNEL_SHIFT(x) ((x) * 8)

#define NUM_ROWS 16
#define NUM_COLS 32
#define NUM_FRAME_BFRS 2

#define DWT_CYCCNT (*((volatile uint32_t *)0xE0001004))

/*
 * The interleave factor is the number of rows until you get to the
 * "paired" or "aliased" line. TVs have an interleave factor of 2. This
 * LED array restarts at 8.
 */
#define INTERLEAVE_FACTOR   8
#define NUM_SCAN_ROWS       (INTERLEAVE_FACTOR)

typedef union
{
    struct
    {
        uint32_t r0 :1;
        uint32_t g0 :1;
        uint32_t b0 :1;
        uint32_t r1 :1;
        uint32_t g1 :1;
        uint32_t b1 :1;
        uint32_t clk :1;
        uint32_t lat :1;
        uint32_t oe :1;
        uint32_t rs9 :1;
        uint32_t row :3;
        uint32_t rsvd13_31 :19;
    } bits;
    struct fastbits
    {
        uint32_t rgb0 :3;
        uint32_t rgb1 :3;
        uint32_t clk :1;
        uint32_t lat :1;
        uint32_t oe :1;
        uint32_t rs9 :1;
        uint32_t row :3;
        uint32_t rsvd13_31 :19;
    } fastbits;
    struct fasterbits
    {
        uint32_t rgb0_1 :6;
        uint32_t clk :1;
        uint32_t lat :1;
        uint32_t oe :1;
        uint32_t rs9 :1;
        uint32_t row :3;
        uint32_t rsvd13_31 :19;
    } fasterbits;
    uint32_t all;
} port_t;

/* For efficiency, pixel information is always 32-bits for pass-by-value */
typedef union
{
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } bits;
    uint32_t all;
} pixel_t;

typedef enum
{
    FB_FLIP_ANIMATE_DONE,
    FB_FLIP_SCAN_DONE,
    FB_FLIP_FORCE,
} fb_flip_control_t;

int32_t task_scan(void);
int32_t task_animate(void);
void init_scan(void);

extern pixel_t (*fb_ptr)[NUM_ROWS][NUM_COLS];
extern pixel_t (*fb_back_ptr)[NUM_ROWS][NUM_COLS];

#endif /* __SCAN_H__ */
