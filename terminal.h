#ifndef __TERMINAL_H__
#define __TERMINAL_H__

/*
**
** Introduction
** ============
**
** terminal.c is a basic level that parses escape sequences to call
** appropriated callbacks permiting you to implement a specific terminal.
**
** Callbacks
** =========
**
** terminal.c maps sequences to callbacks in this way :
** \033...  maps to terminal->callbacks->esc
** \033[... maps to terminal->callbacks->csi
** \033#... maps to terminal->callbacks->hash
** and \033( and \033) maps to terminal->callbacks->scs
**
** In 'callbacks', esc, csi, hash and scs are structs ascii_callbacks
** where you can bind your callbacks.
**
** Typically when terminal parses \033[42;43m
** it calls terminal->callbacks->csi->m(terminal);
**
** Parameters (here 42;43) are stored in terminal->argc and terminal->argv
** argv is an array of integers of length argc.
**
** Public members
** ==============
**
** terminal->user_data :
**     A (void *) where your implementation can store whatever you want
**     to get it back on your callabks.
**
** terminal->write = vt100_write;
** terminal->callbacks.csi.f = HVP;
**
**
**
*/

#define TERM_STACK_SIZE 1024

enum term_state
{
    INIT,
    ESC,
    HASH,
    G0SET,
    G1SET,
    CSI
};

struct terminal;

typedef void (*term_action)(struct terminal *emul);

struct ascii_callbacks
{
    term_action n0;
    term_action n1;
    term_action n2;
    term_action n3;
    term_action n4;
    term_action n5;
    term_action n6;
    term_action n7;
    term_action n8;
    term_action n9;

    term_action h3A;
    term_action h3B;
    term_action h3C;
    term_action h3D;
    term_action h3E;
    term_action h3F;
    term_action h40;

    term_action A;
    term_action B;
    term_action C;
    term_action D;
    term_action E;
    term_action F;
    term_action G;
    term_action H;
    term_action I;
    term_action J;
    term_action K;
    term_action L;
    term_action M;
    term_action N;
    term_action O;
    term_action P;
    term_action Q;
    term_action R;
    term_action S;
    term_action T;
    term_action U;
    term_action V;
    term_action W;
    term_action X;
    term_action Y;
    term_action Z;

    term_action h5B;
    term_action h5C;
    term_action h5D;
    term_action h5E;
    term_action h5F;
    term_action h60;

    term_action a;
    term_action b;
    term_action c;
    term_action d;
    term_action e;
    term_action f;
    term_action g;
    term_action h;
    term_action i;
    term_action j;
    term_action k;
    term_action l;
    term_action m;
    term_action n;
    term_action o;
    term_action p;
    term_action q;
    term_action r;
    term_action s;
    term_action t;
    term_action u;
    term_action v;
    term_action w;
    term_action x;
    term_action y;
    term_action z;
};

struct term_callbacks
{
    struct ascii_callbacks esc;
    struct ascii_callbacks csi;
    struct ascii_callbacks hash;
    struct ascii_callbacks scs;
};

struct terminal
{
    unsigned int           cursor_pos_x;
    unsigned int           cursor_pos_y;
    enum term_state        state;
    unsigned int           argc;
    unsigned int           argv[TERM_STACK_SIZE];
    void                   (*write)(struct terminal *, char c);
    char                   stack[TERM_STACK_SIZE];
    unsigned int           stack_ptr;
    struct term_callbacks  callbacks;
    char                   flag;
    void                   *user_data;
    void                   (*unimplemented)(struct terminal*,
                                            char *seq, char chr);
    int                    fd;
};

struct terminal *terminal_init(void);
void terminal_default_unimplemented(struct terminal* term, char *seq, char chr);
void terminal_read(struct terminal *term, char c);
void terminal_read_str(struct terminal *term, char *c);

#endif
