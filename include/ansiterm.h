#ifndef ANSITERM_H_
#define ANSITERM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#ifndef ANSITERM_ASSERT
#include <assert.h>
#define ANSITERM_ASSERT assert
#endif // ANSITERM_ASSERT

#define ansiterm_move_cursor_rel(dx, dy) ansiterm_fmove_cursor_rel(stdout, dx, dy)
void ansiterm_fmove_cursor_rel(FILE *file, int dx, int dy);

#define ansiterm_move_cursor_lines(dy) ansiterm_fmove_cursor_lines(stdout, dy)
void ansiterm_fmove_cursor_lines(FILE *file, int dy);

#define ansiterm_move_cursor_col_abs(x) ansiterm_fmove_cursor_col_abs(stdout, x)
void ansiterm_fmove_cursor_col_abs(FILE *file, unsigned int x);

#define ansiterm_move_cursor_abs(x, y) ansiterm_fmove_cursor_abs(stdout, x, y)
void ansiterm_fmove_cursor_abs(FILE *file, unsigned int x, unsigned int y);

typedef enum {
    ANSITERM_CLEAR_TO_END = 0,
    ANSITERM_CLEAR_FROM_BEGIN = 1,
    ANSITERM_CLEAR_ALL = 2,
    ANSITERM_CLEAR_SCROLLBACK = 3,
} Ansiterm_Clear;

#define ansiterm_clear(type) ansiterm_fclear(stdout, type)
void ansiterm_fclear(FILE *file, Ansiterm_Clear type);

#define ansiterm_clear_line(type) ansiterm_fclear_line(stdout, type)
void ansiterm_fclear_line(FILE *file, Ansiterm_Clear type);

#define ansiterm_scroll(dy) ansiterm_fscroll(stdout, dy)
void ansiterm_fscroll(FILE *file, int dy);

typedef enum {
    ANSITERM_ATTR_RESET,
    ANSITERM_ATTR_BOLD,
    ANSITERM_ATTR_FAINT,
    ANSITERM_ATTR_ITALIC,
    ANSITERM_ATTR_UNDERLINE,
    ANSITERM_ATTR_BLINK_SLOW,
    ANSITERM_ATTR_BLINK_FAST,
    ANSITERM_ATTR_SWAP_COLORS,
    ANSITERM_ATTR_HIDE,
    ANSITERM_ATTR_STRIKETHROUGH,
    ANSITERM_ATTR_FONT,
    ANSITERM_ATTR_FONT_FRAKTUR = 20,
    ANSITERM_ATTR_DOUBLE_UNDERLINE,
    ANSITERM_ATTR_NORMAL_INTENSITY,
    ANSITERM_ATTR_NEITHER_ITALIC_NOR_BLACKLETTER,
    ANSITERM_ATTR_NO_UNDERLINE,
    ANSITERM_ATTR_NO_BLINK,
    ANSITERM_ATTR_PROPORTIONAL_SPACING,
    ANSITERM_ATTR_NO_SWAP_COLORS,
    ANSITERM_ATTR_NO_HIDE,
    ANSITERM_ATTR_NO_STRIKETHROUGH,
    ANSITERM_ATTR_SET_FG,
    ANSITERM_ATTR_SET_FG_EX = 38,
    ANSITERM_ATTR_DEFAULT_FG,
    ANSITERM_ATTR_SET_BG,
    ANSITERM_ATTR_SET_BG_EX = 48,
    ANSITERM_ATTR_DEFAULT_BG,
    ANSITERM_ATTR_NO_PROPORTIONAL_SPACING,
    ANSITERM_ATTR_FRAMED,
    ANSITERM_ATTR_ENCIRCLED,
    ANSITERM_ATTR_OVERLINED,
    ANSITERM_ATTR_NEITHER_FRAMED_NOR_ENCIRCLED,
    ANSITERM_ATTR_NO_OVERLINE,
    ANSITERM_ATTR_SET_UNDERLINE_COLOR,
    ANSITERM_ATTR_DEFAULT_UNDERLINE_COLOR,
    ANSITERM_ATTR_IDEOGRAM_UNDERLINE_OR_RIGHT_SIDE_LINE,
    ANSITERM_ATTR_IDEOGRAM_DOUBLE_UNDERLINE_OR_DOUBLE_RIGHT_SIDE_LINE,
    ANSITERM_ATTR_IDEOGRAM_OVERLINE_OR_LEFT_SIDE_LINE,
    ANSITERM_ATTR_IDEOGRAM_DOUBLE_OVERLINE_OR_DOUBLE_LEFT_SIDE_LINE,
    ANSITERM_ATTR_IDEOGRAM_STRESS_MARKING,
    ANSITERM_ATTR_NO_IDEOGRAM,
    ANSITERM_ATTR_SUPERSCRIPT = 73,
    ANSITERM_ATTR_SUBSCRIPT,
    ANSITERM_ATTR_NEITHER_SUPERSCRIPT_NOR_SUBSCRIPT,
    ANSITERM_ATTR_SET_BRIGHT_FG = 90,
    ANSITERM_ATTR_SET_BRIGHT_BG = 100,
} Ansiterm_Attr;

#define ansiterm_set_attr(attr) ansiterm_fset_attr(stdout, attr)
void ansiterm_fset_attr(FILE *file, Ansiterm_Attr attr);

#define ansiterm_set_fg_3bit(color) ansiterm_fset_fg_3bit(stdout, color)
void ansiterm_fset_fg_3bit(FILE *file, uint8_t color);

#define ansiterm_set_fg_8bit(color) ansiterm_fset_fg_8bit(stdout, color)
void ansiterm_fset_fg_8bit(FILE *file, uint8_t color);

#define ansiterm_set_fg_24bit(r, g, b) ansiterm_fset_fg_24bit(stdout, r, g, b)
void ansiterm_fset_fg_24bit(FILE *file, uint8_t r, uint8_t g, uint8_t b);

#define ansiterm_set_bg_3bit(color) ansiterm_fset_bg_3bit(stdout, color)
void ansiterm_fset_bg_3bit(FILE *file, uint8_t color);

#define ansiterm_set_bg_8bit(color) ansiterm_fset_bg_8bit(stdout, color)
void ansiterm_fset_bg_8bit(FILE *file, uint8_t color);

#define ansiterm_set_bg_24bit(r, g, b) ansiterm_fset_bg_24bit(stdout, r, g, b)
void ansiterm_fset_bg_24bit(FILE *file, uint8_t r, uint8_t g, uint8_t b);

#define ansiterm_set_colors_3bit(fg, bg) ansiterm_fset_colors_3bit(stdout, fg, bg)
#define ansiterm_fset_colors_3bit(file, fg, bg) (ansiterm_fset_fg_3bit(file, fg), ansiterm_fset_bg_3bit(file, bg))
#define ansiterm_set_colors_8bit(fg, bg) ansiterm_fset_colors_8bit(stdout, fg, bg)
#define ansiterm_fset_colors_8bit(file, fg, bg) (ansiterm_fset_fg_8bit(file, fg), ansiterm_fset_bg_8bit(file, bg))
#define ansiterm_set_colors_24bit(fgr, fgg, fgb, bgr, bgg, bgb) ansiterm_fset_colors_24bit(stdout, fgr, fgg, fgb, bgr, bgg, bgb)
#define ansiterm_fset_colors_24bit(file, fgr, fgg, fgb, bgr, bgg, bgb) (ansiterm_fset_fg_24bit(file, fgr, fgg, fgb), ansiterm_fset_bg_24bit(file, bgr, bgg, bgb))

#define ansiterm_aux_port(on) ansiterm_faux_port_on(stdout, on)
void ansiterm_faux_port(FILE *file, bool on);

#define ansiterm_save_cursor() ansiterm_fsave_cursor(stdout)
void ansiterm_fsave_cursor(FILE *file);

#define ansiterm_restore_cursor() ansiterm_frestore_cursor(stdout)
void ansiterm_frestore_cursor(FILE *file);

#define ansiterm_set_cursor_visibility(visible) ansiterm_fset_cursor_visibility(stdout, visible)
void ansiterm_fset_cursor_visibility(FILE *file, bool visible);

#define ansiterm_set_alternate_buffer(alternate) ansiterm_fset_alternate_buffer(stdout, alternate)
void ansiterm_fset_alternate_buffer(FILE *file, bool alternate);

#endif // ANSITERM_H_

#ifdef ANSITERM_IMPLEMENTATION

void ansiterm_fmove_cursor_rel(FILE *file, int dx, int dy) {
    char dirx = 'C';
    if (dx < 0) { dirx = 'D'; dx *= -1; }
    char diry = 'B';
    if (dy < 0) { diry = 'A'; dy *= -1; }

    if (dx != 0) fprintf(file, "\x1b[%d%c", dx, dirx);
    if (dy != 0) fprintf(file, "\x1b[%d%c", dy, diry);
}

void ansiterm_fmove_cursor_lines(FILE *file, int dy) {
    char dir = 'E';
    if (dy < 0) { dir = 'F'; dy *= -1; }

    if (dy != 0) fprintf(file, "\x1b[%d%c", dy, dir);
}

void ansiterm_fmove_cursor_col_abs(FILE *file, unsigned int x) {
    fprintf(file, "\x1b[%uG", x);
}

void ansiterm_fmove_cursor_abs(FILE *file, unsigned int x, unsigned int y) {
    fprintf(file, "\x1b[%u;%uH", x, y);
}

void ansiterm_fclear(FILE *file, Ansiterm_Clear type) {
    fprintf(file, "\x1b[%dJ", type);
}

void ansiterm_fclear_line(FILE *file, Ansiterm_Clear type) {
    fprintf(file, "\x1b[%dK", type);
}

void ansiterm_fscroll(FILE *file, int dy) {
    char dir = 'T';
    if (dy < 0) { dir = 'S'; dy *= -1; }

    if (dy != 0) fprintf(file, "\x1b[%d%c", dy, dir);
}

void ansiterm_fset_attr(FILE *file, Ansiterm_Attr attr) {
    fprintf(file, "\x1b[%dm", attr);
}

void ansiterm_faux_port(FILE *file, bool on) {
    if (on) {
        fprintf(file, "\x1b[5i");
    } else {
        fprintf(file, "\x1b[4i");
    }
}

void ansiterm_fset_fg_3bit(FILE *file, uint8_t color) {
    ANSITERM_ASSERT(color < (ANSITERM_ATTR_SET_FG_EX - ANSITERM_ATTR_SET_FG));
    ansiterm_fset_attr(file, ANSITERM_ATTR_SET_FG + color);
}

void ansiterm_fset_fg_8bit(FILE *file, uint8_t color) {
    fprintf(file, "\x1b[%d;5;%hhum", ANSITERM_ATTR_SET_FG_EX, color);
}

void ansiterm_fset_fg_24bit(FILE *file, uint8_t r, uint8_t g, uint8_t b) {
    fprintf(file, "\x1b[%d;2;%hhu;%hhu;%hhum", ANSITERM_ATTR_SET_FG_EX, r, g, b);
}

void ansiterm_fset_bg_3bit(FILE *file, uint8_t color) {
    ANSITERM_ASSERT(color < (ANSITERM_ATTR_SET_BG_EX - ANSITERM_ATTR_SET_BG));
    ansiterm_fset_attr(file, ANSITERM_ATTR_SET_BG + color);
}

void ansiterm_fset_bg_8bit(FILE *file, uint8_t color) {
    fprintf(file, "\x1b[%d;5;%hhum", ANSITERM_ATTR_SET_BG_EX, color);
}

void ansiterm_fset_bg_24bit(FILE *file, uint8_t r, uint8_t g, uint8_t b) {
    fprintf(file, "\x1b[%d;2;%hhu;%hhu;%hhum", ANSITERM_ATTR_SET_BG_EX, r, g, b);
}

void ansiterm_fsave_cursor(FILE *file) {
    fprintf(file, "\x1b""7");
}

void ansiterm_frestore_cursor(FILE *file) {
    fprintf(file, "\x1b""8");
}

void ansiterm_fset_cursor_visibility(FILE *file, bool visible) {
    fprintf(file, "\x1b[?25%c", visible ? 'h' : 'l');
}

void ansiterm_fset_alternate_buffer(FILE *file, bool alternate) {
    fprintf(file, "\x1b[?1049%c", alternate ? 'h' : 'l');
}

#endif // ANSITERM_IMPLEMENTATION

#if defined(ANSITERM_STRIP_PREFIX) && !defined(ANSITERM_STRIP_PREFIX_GUARD)
#define ANSITERM_STRIP_PREFIX_GUARD

#define move_cursor_rel ansiterm_move_cursor_rel
#define fmove_cursor_rel ansiterm_fmove_cursor_rel
#define move_cursor_lines ansiterm_move_cursor_lines
#define fmove_cursor_lines ansiterm_fmove_cursor_lines
#define move_cursor_col_abs ansiterm_move_cursor_col_abs
#define fmove_cursor_col_abs ansiterm_fmove_cursor_col_abs
#define move_cursor_abs ansiterm_move_cursor_abs
#define fmove_cursor_abs ansiterm_fmove_cursor_abs
#define CLEAR_TO_END ANSITERM_CLEAR_TO_END
#define CLEAR_FROM_BEGIN ANSITERM_CLEAR_FROM_BEGIN
#define CLEAR_ALL ANSITERM_CLEAR_ALL
#define CLEAR_SCROLLBACK ANSITERM_CLEAR_SCROLLBACK
#define Clear Ansiterm_Clear
#define clear ansiterm_clear
#define fclear ansiterm_fclear
#define clear_line ansiterm_clear_line
#define fclear_line ansiterm_fclear_line
#define scroll ansiterm_scroll
#define fscroll ansiterm_fscroll
#define ATTR_RESET ANSITERM_ATTR_RESET
#define ATTR_BOLD ANSITERM_ATTR_BOLD
#define ATTR_FAINT ANSITERM_ATTR_FAINT
#define ATTR_ITALIC ANSITERM_ATTR_ITALIC
#define ATTR_UNDERLINE ANSITERM_ATTR_UNDERLINE
#define ATTR_BLINK_SLOW ANSITERM_ATTR_BLINK_SLOW
#define ATTR_BLINK_FAST ANSITERM_ATTR_BLINK_FAST
#define ATTR_SWAP_COLORS ANSITERM_ATTR_SWAP_COLORS
#define ATTR_HIDE ANSITERM_ATTR_HIDE
#define ATTR_STRIKETHROUGH ANSITERM_ATTR_STRIKETHROUGH
#define ATTR_FONT ANSITERM_ATTR_FONT
#define ATTR_FONT_FRAKTUR ANSITERM_ATTR_FONT_FRAKTUR
#define ATTR_DOUBLE_UNDERLINE ANSITERM_ATTR_DOUBLE_UNDERLINE
#define ATTR_NORMAL_INTENSITY ANSITERM_ATTR_NORMAL_INTENSITY
#define ATTR_NEITHER_ITALIC_NOR_BLACKLETTER ANSITERM_ATTR_NEITHER_ITALIC_NOR_BLACKLETTER
#define ATTR_NO_UNDERLINE ANSITERM_ATTR_NO_UNDERLINE
#define ATTR_NO_BLINK ANSITERM_ATTR_NO_BLINK
#define ATTR_PROPORTIONAL_SPACING ANSITERM_ATTR_PROPORTIONAL_SPACING
#define ATTR_NO_SWAP_COLORS ANSITERM_ATTR_NO_SWAP_COLORS
#define ATTR_NO_HIDE ANSITERM_ATTR_NO_HIDE
#define ATTR_NO_STRIKETHROUGH ANSITERM_ATTR_NO_STRIKETHROUGH
#define ATTR_SET_FG ANSITERM_ATTR_SET_FG
#define ATTR_SET_FG_EX ANSITERM_ATTR_SET_FG_EX
#define ATTR_DEFAULT_FG ANSITERM_ATTR_DEFAULT_FG
#define ATTR_SET_BG ANSITERM_ATTR_SET_BG
#define ATTR_SET_BG_EX ANSITERM_ATTR_SET_BG_EX
#define ATTR_DEFAULT_BG ANSITERM_ATTR_DEFAULT_BG
#define ATTR_NO_PROPORTIONAL_SPACING ANSITERM_ATTR_NO_PROPORTIONAL_SPACING
#define ATTR_FRAMED ANSITERM_ATTR_FRAMED
#define ATTR_ENCIRCLED ANSITERM_ATTR_ENCIRCLED
#define ATTR_OVERLINED ANSITERM_ATTR_OVERLINED
#define ATTR_NEITHER_FRAMED_NOR_ENCIRCLED ANSITERM_ATTR_NEITHER_FRAMED_NOR_ENCIRCLED
#define ATTR_NO_OVERLINE ANSITERM_ATTR_NO_OVERLINE
#define ATTR_SET_UNDERLINE_COLOR ANSITERM_ATTR_SET_UNDERLINE_COLOR
#define ATTR_DEFAULT_UNDERLINE_COLOR ANSITERM_ATTR_DEFAULT_UNDERLINE_COLOR
#define ATTR_IDEOGRAM_UNDERLINE_OR_RIGHT_SIDE_LINE ANSITERM_ATTR_IDEOGRAM_UNDERLINE_OR_RIGHT_SIDE_LINE
#define ATTR_IDEOGRAM_DOUBLE_UNDERLINE_OR_DOUBLE_RIGHT_SIDE_LINE ANSITERM_ATTR_IDEOGRAM_DOUBLE_UNDERLINE_OR_DOUBLE_RIGHT_SIDE_LINE
#define ATTR_IDEOGRAM_OVERLINE_OR_LEFT_SIDE_LINE ANSITERM_ATTR_IDEOGRAM_OVERLINE_OR_LEFT_SIDE_LINE
#define ATTR_IDEOGRAM_DOUBLE_OVERLINE_OR_DOUBLE_LEFT_SIDE_LINE ANSITERM_ATTR_IDEOGRAM_DOUBLE_OVERLINE_OR_DOUBLE_LEFT_SIDE_LINE
#define ATTR_IDEOGRAM_STRESS_MARKING ANSITERM_ATTR_IDEOGRAM_STRESS_MARKING
#define ATTR_NO_IDEOGRAM ANSITERM_ATTR_NO_IDEOGRAM
#define ATTR_SUPERSCRIPT ANSITERM_ATTR_SUPERSCRIPT
#define ATTR_SUBSCRIPT ANSITERM_ATTR_SUBSCRIPT
#define ATTR_NEITHER_SUPERSCRIPT_NOR_SUBSCRIPT ANSITERM_ATTR_NEITHER_SUPERSCRIPT_NOR_SUBSCRIPT
#define ATTR_SET_BRIGHT_FG ANSITERM_ATTR_SET_BRIGHT_FG
#define ATTR_SET_BRIGHT_BG ANSITERM_ATTR_SET_BRIGHT_BG
#define set_attr ansiterm_set_attr
#define fset_attr ansiterm_fset_attr
#define set_fg_3bit ansiterm_set_fg_3bit
#define fset_fg_3bit ansiterm_fset_fg_3bit
#define set_fg_8bit ansiterm_set_fg_8bit
#define fset_fg_8bit ansiterm_fset_fg_8bit
#define set_fg_24bit ansiterm_set_fg_24bit
#define fset_fg_24bit ansiterm_fset_fg_24bit
#define set_bg_3bit ansiterm_set_bg_3bit
#define fset_bg_3bit ansiterm_fset_bg_3bit
#define set_bg_8bit ansiterm_set_bg_8bit
#define fset_bg_8bit ansiterm_fset_bg_8bit
#define set_bg_24bit ansiterm_set_bg_24bit
#define fset_bg_24bit ansiterm_fset_bg_24bit
#define set_colors_3bit ansiterm_set_colors_3bit
#define fset_colors_3bit ansiterm_fset_colors_3bit
#define set_colors_8bit ansiterm_set_colors_8bit
#define fset_colors_8bit ansiterm_fset_colors_8bit
#define set_colors_24bit ansiterm_set_colors_24bit
#define fset_colors_24bit ansiterm_fset_colors_24bit
#define aux_port ansiterm_aux_port
#define faux_port ansiterm_faux_port
#define save_cursor ansiterm_save_cursor
#define fsave_cursor ansiterm_fsave_cursor
#define restore_cursor ansiterm_restore_cursor
#define frestore_cursor ansiterm_frestore_cursor
#define set_cursor_visibility ansiterm_set_cursor_visibility
#define fset_cursor_visibility ansiterm_fset_cursor_visibility
#define set_alternate_buffer ansiterm_set_alternate_buffer
#define fset_alternate_buffer ansiterm_fset_alternate_buffer

#endif // ANSITERM_STRIP_PREFIX
