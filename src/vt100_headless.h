#ifndef __VT100_HEADLESS_H__
#define __VT100_HEADLESS_H__

#define CHILD 0

#include "terminal_vt100.h"

struct vt100_headless
{
    int master;
    struct termios backup;
    struct terminal_vt100 *term;
    void (*changed)(struct vt100_headless *this);
};


void vt100_headless_fork(struct vt100_headless *this, const char *progname, char *const argv[]);
struct vt100_headless *vt100_headless_init(void);

#endif