#ifndef TYPES_H
#define TYPES_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#if SDL_BYTEORDER != SDL_LIL_ENDIAN
#error This program is not (yet) prepared for big endian CPUs, please contact the author.
#endif

// This macro is from SDL_types.h.
// It is #undefined at the end of that file, even though it can be useful outside that file.
/* Make sure the types really have the right sizes */
#define SDL_COMPILE_TIME_ASSERT(name, x)               \
       typedef int SDL_dummy_ ## name[(x) * 2 - 1]

// "far" and "near" makes sense only for 16-bit
#define far
#define near
#define __pascal
#define malloc_near malloc
#define malloc_far  malloc
#define free_near free
#define free_far  free
#define memset_near memset
#define memset_far  memset
#define memcpy_near memcpy
#define memcpy_far  memcpy

typedef Uint8 byte;
typedef Sint8 sbyte;
typedef Uint16 word;
typedef Uint32 dword;

typedef struct rect_type {
	short top,left,bottom,right;
} rect_type;

typedef struct piece {
	byte base_id;
	byte floor_left;
	sbyte base_y;
	byte right_id;
	byte floor_right;
	sbyte right_y;
	byte stripe_id;
	byte topright_id;
	byte bottom_id;
	byte fore_id;
	byte fore_x;
	sbyte fore_y;
} piece;
typedef struct tile_and_mod {
	byte tiletype;
	byte modifier;
} tile_and_mod;

typedef int __pascal far (*add_table_type)(short chtab_id, int id, sbyte xh, sbyte xl, int ybottom, byte blit, byte peel);

typedef struct back_table_type {
	sbyte xh;
	sbyte xl;
	short y;
	byte chtab_id;
	byte id;
	byte blit;
} back_table_type;

typedef struct midtable_type {
	sbyte xh;
	sbyte xl;
	short y;
	byte chtab_id;
	byte id;
	byte peel;
	rect_type clip;
	byte blit;
} midtable_type;

typedef struct wipetable_type {
	sbyte left_high;
	short bottom;
	sbyte height;
	sbyte width_high;
	sbyte color;
	sbyte layer;
} wipetable_type;

enum soundflags { sfDigi=1, sfMidi=2, soundflags_4=4, sfLoop=0x80 };

enum tiles {
	tiles_0_empty = 0,
	tiles_1_floor = 1,
	tiles_2_spike = 2,
	tiles_3_pillar = 3,
	tiles_4_gate = 4,
	tiles_5_stuck = 5,
	tiles_6_closer = 6, // a.k.a. drop button
	tiles_7_doortop_with_floor = 7, // a.k.a. tapestry
	tiles_8_bigpillar_bottom = 8,
	tiles_9_bigpillar_top = 9,
	tiles_10_potion = 10,
	tiles_11_loose = 11,
	tiles_12_doortop = 12, // a.k.a. tapestry top
	tiles_13_mirror = 13,
	tiles_14_debris = 14, // a.k.a. broken floor
	tiles_15_opener = 15, // a.k.a. raise button
	tiles_16_level_door_left = 16, // a.k.a. exit door
	tiles_17_level_door_right = 17,
	tiles_18_chomper = 18,
	tiles_19_torch = 19,
	tiles_20_wall = 20,
	tiles_21_skeleton = 21,
	tiles_22_sword = 22,
	tiles_23_balcony_left = 23,
	tiles_24_balcony_right = 24,
	tiles_25_lattice_pillar = 25,
	tiles_26_lattice_down = 26, // a.k.a. lattice support
	tiles_27_lattice_small = 27,
	tiles_28_lattice_left = 28,
	tiles_29_lattice_right = 29,
	tiles_30_torch_with_debris = 30
};

enum chtabs {
	id_chtab_0_sword = 0,
	id_chtab_1_flameswordpotion = 1,
	id_chtab_2_kid = 2,
	id_chtab_3_princessinstory = 3,
	id_chtab_4_jaffarinstory_princessincutscenes = 4,
	id_chtab_5_guard = 5,
	id_chtab_6_environment = 6,
	id_chtab_7_environmentwall = 7,
	id_chtab_8_princessroom = 8,
	id_chtab_9_princessbed = 9
};

enum blitters {
	blitters_0_no_transp = 0,
	// It seems to me that the "or" blitter can be safely replaced with the "transparent" blitter.
	blitters_2_or = 2,
	blitters_3_xor = 3, // used for the shadow
	blitters_9_black = 9,
	blitters_10h_transp = 0x10,
	/* 0x40..0x4F will draw a monochrome image with color 0..15 */
	blitters_40h_mono = 0x40,
	blitters_46h_mono_6 = 0x46, // used for palace wall patterns
	blitters_4Ch_mono_12 = 0x4C // used for chomper blood
};

enum grmodes {
	gmCga = 1,
	gmHgaHerc = 2,
	gmEga = 3,
	gmTga = 4,
	gmMcgaVga = 5
};

enum sound_modes {
	smAuto = 0,
	smAdlib = 1,
	smGblast = 2,
	smSblast = 3,
	smCovox = 4,
	smIbmg = 5,
	smTandy = 6
};

#pragma pack(push,1)
typedef struct link_type {
	byte left,right,up,down;
} link_type;

typedef struct level_type {
	byte fg[720];
	byte bg[720];
	byte doorlinks1[256];
	byte doorlinks2[256];
	link_type roomlinks[24];
	byte used_rooms;
	byte roomxs[24];
	byte roomys[24];
	byte fill_1[15];
	byte start_room;
	byte start_pos;
	sbyte start_dir;
	byte fill_2[4];
	byte guards_tile[24];
	byte guards_dir[24];
	byte guards_x[24];
	byte guards_seq_lo[24];
	byte guards_skill[24];
	byte guards_seq_hi[24];
	byte guards_color[24];
	byte fill_3[18];
} level_type;
SDL_COMPILE_TIME_ASSERT(level_size, sizeof(level_type) == 2305);
#pragma pack(pop)

typedef SDL_Surface surface_type;
typedef SDL_Surface image_type;
typedef struct peel_type {
	SDL_Surface* peel;
	rect_type rect;
} peel_type;

typedef struct chtab_type {
	word n_images;
	word chtab_palette_bits;
	word has_palette_bits;
	// This is a variable-size array, with n_images elements.
	image_type* far pointers[0];
} chtab_type;

#pragma pack(push,1)
typedef struct rgb_type {
	byte r,g,b;
} rgb_type;
typedef struct dat_pal_type {
	word row_bits;
	byte n_colors;
	rgb_type vga[16];
	byte cga[16];
	byte ega[32];
} dat_pal_type;
typedef struct dat_shpl_type {
	byte n_images;
	dat_pal_type palette;
} dat_shpl_type;
SDL_COMPILE_TIME_ASSERT(dat_shpl_size, sizeof(dat_shpl_type) == 100);
#pragma pack(pop)

typedef struct char_type {
	byte frame;
	byte x;
	byte y;
	sbyte direction;
	sbyte curr_col;
	sbyte curr_row;
	byte action;
	sbyte fall_x;
	sbyte fall_y;
	byte room;
	byte repeat;
	byte charid;
	byte sword;
	sbyte alive;
	word curr_seq;
} char_type;

enum charids {
	charid_0_kid      = 0,
	charid_1_shadow   = 1,
	charid_2_guard    = 2,
	charid_3          = 3,
	charid_4_skeleton = 4,
	charid_5_princess = 5,
	charid_6_vizier   = 6,
	charid_24_mouse   = 0x18
};

typedef struct auto_move_type {
	short time,move;
} auto_move_type;

/* obj_type:
	0 = Kid, princess, vizier
	1 = shadow
	2 = Guard
	3 = sword
	4 = mirror image
	5 = hurt splash
	0x80 = loose floor
*/
typedef struct objtable_type {
	sbyte xh;
	sbyte xl;
	short y;
	byte chtab_id;
	byte id;
	sbyte direction;
	byte obj_type;
	rect_type clip;
	byte tilepos;
} objtable_type;

typedef struct frame_type {
	byte image;
	
	// 0x3F: sword image
	// 0xC0: chtab
	byte sword;
	
	sbyte dx;
	sbyte dy;
	
	// 0x1F: weight x
	// 0x20: thin
	// 0x40: needs floor
	// 0x80: even/odd pixel
	byte flags;
} frame_type;

typedef struct trob_type {
	byte tilepos;
	byte room;
	sbyte type;
} trob_type;

typedef struct mob_type {
	byte xh;
	byte y;
	byte room;
	sbyte speed;
	byte type;
	byte row;
} mob_type;

enum directions {
	dir_0_right = 0x00,
	dir_56_none = 0x56,
	dir_FF_left = -1
};

enum actions {
	actions_0_stand         = 0,
	actions_1_run_jump      = 1,
	actions_2_hang_climb    = 2,
	actions_3_in_midair     = 3,
	actions_4_in_freefall   = 4,
	actions_5_bumped        = 5,
	actions_6_hang_straight = 6,
	actions_7_turn          = 7,
	actions_99_hurt         = 99,
};

typedef struct sword_table_type {
	byte id;
	sbyte x;
	sbyte y;
} sword_table_type;

#pragma pack(push,1)
typedef struct dat_header_type {
	Uint32 table_offset;
	Uint16 table_size;
} dat_header_type;
SDL_COMPILE_TIME_ASSERT(dat_header_size, sizeof(dat_header_type) == 6);

typedef struct dat_res_type {
	Uint16 id;
	Uint32 offset;
	Uint16 size;
} dat_res_type;
SDL_COMPILE_TIME_ASSERT(dat_res_size, sizeof(dat_res_type) == 8);

typedef struct dat_table_type {
	Uint16 res_count;
	dat_res_type entries[0];
} dat_table_type;
SDL_COMPILE_TIME_ASSERT(dat_table_size, sizeof(dat_table_type) == 2);

typedef struct image_data_type {
	Uint16 height;
	Uint16 width;
	Uint16 flags;
	byte data[0];
} image_data_type;
SDL_COMPILE_TIME_ASSERT(image_data_size, sizeof(image_data_type) == 6);
#pragma pack(pop)

typedef struct dat_type {
	struct dat_type* next_dat;
	FILE* handle;
	char filename[64];
	dat_table_type* dat_table;
	// handle and dat_table are NULL if the DAT is a directory.
} dat_type;

typedef void __pascal far (*cutscene_ptr_type)();

#ifdef USE_FADE
typedef struct palette_fade_type {
	word which_rows;
	word wait_time;
	word fade_pos;
	rgb_type original_pal[256];
	rgb_type faded_pal[256];
	int __pascal far (*proc_fade_frame)(struct palette_fade_type far *palette_buffer);
	void __pascal far (*proc_restore_free)(struct palette_fade_type far *palette_buffer);
} palette_fade_type;
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

#ifdef USE_TEXT
typedef struct font_type {
	byte first_char;
	byte last_char;
	short height_above_baseline;
	short height_below_baseline;
	short space_between_lines;
	short space_between_chars;
	chtab_type* chtab;
} font_type;

typedef struct textstate_type {
	short current_x;
	short current_y;
	short textblit;
	short textcolor;
	font_type* ptr_font;
} textstate_type;

#pragma pack(push,1)
typedef struct rawfont_type {
	byte first_char;
	byte last_char;
	short height_above_baseline;
	short height_below_baseline;
	short space_between_lines;
	short space_between_chars;
	word offsets[0];
} rawfont_type;
SDL_COMPILE_TIME_ASSERT(rawfont_type, sizeof(rawfont_type) == 10);
#pragma pack(pop)

#endif

typedef enum data_location {
	data_none = 0,
	data_DAT = 1,
	data_directory = 2
} data_location;

enum sound_type {
	sound_speaker = 0,
	sound_digi = 1,
	sound_midi = 2
};
#pragma pack(push,1)
typedef struct note_type {
	word frequency; // 0x00 or 0x01 = rest, 0x12 = end
	byte length;
} note_type;
SDL_COMPILE_TIME_ASSERT(note_type, sizeof(note_type) == 3);
typedef struct speaker_type { // IBM
	word tempo;
	note_type notes[0];
} speaker_type;
SDL_COMPILE_TIME_ASSERT(speaker_type, sizeof(speaker_type) == 2);

typedef struct digi_type { // wave
	word sample_rate;
	word sample_count;
	word unknown;
	byte sample_size; // =8
	byte samples[0];
} digi_type;
SDL_COMPILE_TIME_ASSERT(digi_type, sizeof(digi_type) == 7);

typedef struct midi_type {
	byte data[0];
} midi_type;

typedef struct sound_buffer_type {
	byte type;
	union {
		speaker_type speaker;
		digi_type digi;
		midi_type midi;
	};
} sound_buffer_type;
#pragma pack(pop)

#endif
