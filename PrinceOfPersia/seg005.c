#include "common.h"

// data:1888
const word seqtbl_offsets[] = {
0x0000, 0x1973, 0x19A0, 0x1A93, 0x1ACD, 0x1B39, 0x1B5A, 0x1BDB,
0x1C54, 0x1CA1, 0x1D04, 0x1D25, 0x1D49, 0x1D4F, 0x1D68, 0x1DF6,
0x1C84, 0x202B, 0x1C1C, 0x1C01, 0x205A, 0x1C38, 0x209C, 0x1D36,
0x1C69, 0x1CD1, 0x1B04, 0x1B1A, 0x1D7D, 0x1F9E, 0x1F92, 0x1F82,
0x1F72, 0x1F5D, 0x1F48, 0x1F33, 0x1F19, 0x1F13, 0x1EF7, 0x1EDA,
0x1EBB, 0x1E9C, 0x1E7D, 0x1B53, 0x1E59, 0x1E06, 0x1E3B, 0x1DFC,
0x1D9B, 0x1FB3, 0x1FA7, 0x20BE, 0x20D1, 0x20D4, 0x20C9, 0x19C4,
0x1A13, 0x1A2E, 0x1A3C, 0x1A7C, 0x1A83, 0x1A63, 0x1A5E, 0x1A68,
0x1A6E, 0x1A75, 0x1A5A, 0x19F9, 0x1CEC, 0x1A54, 0x20DD, 0x20AE,
0x1E78, 0x1CDC, 0x19DC, 0x1A42, 0x1A07, 0x19A8, 0x2009, 0x1B1B,
0x1A8B, 0x1B85, 0x1BA1, 0x1BBF, 0x196E, 0x20A9, 0x1A22, 0x19A6,
0x19AC, 0x1B2D, 0x19C1, 0x1FCA, 0x1FDA, 0x1FFB, 0x2195, 0x2132,
0x214F, 0x2166, 0x2199, 0x21A8, 0x216D, 0x226E, 0x2136, 0x21BC,
0x1BFA, 0x2245, 0x2253, 0x225B, 0x21C4, 0x21C0, 0x21E6, 0x21EA,
0x21FC, 0x2240, 0x2257
};

// seg005:000A
void __pascal far seqtbl_offset_char(short seq_index) {
	Char.curr_seq = seqtbl_offsets[seq_index];
}

// seg005:001D
void __pascal far seqtbl_offset_opp(int seq_index) {
	Opp.curr_seq = seqtbl_offsets[seq_index];
}

// seg005:0030
void __pascal far do_fall() {
	if (is_screaming == 0 && Char.fall_y >= 31) {
		play_sound(1); // falling
		is_screaming = 1;
	}
	if ((word)y_land[Char.curr_row + 1] > (word)Char.y) {
		check_grab();
	} else {
		if (get_tile_at_char() == tiles_20_wall) {
			in_wall();
		}
		if (tile_is_floor(curr_tile2)) {
			land();
		} else {
			inc_curr_row();
		}
	}
}

// seg005:0090
void __pascal far land() {
	word seq_id;
	is_screaming = 0;
	Char.y = y_land[Char.curr_row + 1];
	if (get_tile_at_char() != tiles_2_spike) {
		if (! tile_is_floor(get_tile_infrontof_char()) &&
			distance_to_edge_weight() < 3
		) {
			Char.x = char_dx_forward(-3);
		}
		start_chompers();
	} else {
		goto loc_5EE6;
	}
	if (Char.alive < 0) {
		if ((distance_to_edge_weight() >= 12 &&
			get_tile_behind_char() == tiles_2_spike) ||
			get_tile_at_char() == tiles_2_spike
		) {
			loc_5EE6:
			if (is_spike_harmful()) {
				spiked();
				return;
			}
		}
		{
			if (Char.fall_y < 22) {
				loc_5EFD:
				if (Char.charid >= charid_2_guard || Char.sword == 2) {
					Char.sword = 2;
					seq_id = 63; // stand active after landing
				} else {
					seq_id = 17; // crouch (soft land)
				}
				if (Char.charid == charid_0_kid) {
					play_sound(17); // soft land (crouch)
					is_guard_notice = 1;
				}
			} else if (Char.fall_y < 33) {
				if (Char.charid == charid_1_shadow) goto loc_5EFD;
				if (Char.charid == charid_2_guard) goto loc_5F6C;
				if (! take_hp(1)) {
					play_sound(16); // medium land
					is_guard_notice = 1;
					seq_id = 20; // medium land (lose 1 HP, crouch)
				} else {
					goto loc_5F75;
				}
			} else {
				goto loc_5F6C;
			}
		}
	} else {
		loc_5F6C:
		take_hp(100);
		loc_5F75:
		play_sound(0); // prince crashing into the floor
		seq_id = 22; // dead (after falling)
	}
	seqtbl_offset_char(seq_id);
	play_seq();
	Char.fall_y = 0;
}

// seg005:01B7
void __pascal far spiked() {
	// If someone falls into spikes, those spikes become harmless (to others).
	curr_room_modif[curr_tilepos] = 0xFF;
	Char.y = y_land[Char.curr_row + 1];
	Char.x = x_bump[tile_col + 5] + 10;
	Char.x = char_dx_forward(8);
	Char.fall_y = 0;
	play_sound(48); // something spiked
	take_hp(100);
	seqtbl_offset_char(51); // spiked
	play_seq();
}

// seg005:0213
void __pascal far control() {
	short char_frame;
	short char_action;
	char_frame = Char.frame;
	if (Char.alive >= 0) {
		if (char_frame == 15 || // stand
			char_frame == 166 || // stand
			char_frame == 158 || // stand with sword
			char_frame == 171 // stand with sword
		) {
			seqtbl_offset_char(71); // dying (not stabbed)
		}
	} else {
		char_action = Char.action;
		if (char_action == actions_5_bumped ||
			char_action == actions_4_in_freefall
		) {
			release_arrows();
		} else if (Char.sword == 2) {
			control_with_sword();
		} else if (Char.charid >= charid_2_guard) {
			control_guard_inactive();
		} else if (char_frame == 15 || // standing
			(char_frame>=50 && char_frame<53) // end of turning
		) {
			control_standing();
		} else if (char_frame == 48) { // a frame in turning
			control_turning();
		} else if (char_frame < 4) { // start run
			control_startrun();
		} else if (char_frame >= 67 && char_frame < 70) { // start jump up
			control_jumpup();
		} else if (char_frame < 15) { // running
			control_running();
		} else if (char_frame >= 87 && char_frame < 100) { // hanging
			control_hanging();
		} else if (char_frame == 109) { // crouching
			control_crouched();
		}
	}
}

// seg005:02EB
void __pascal far control_crouched() {
	if (need_level1_music != 0 && current_level == 1) {
		// Special event: music when crouching
		if (! check_sound_playing()) {
			if (need_level1_music == 1) {
				play_sound(25); // presentation (level 1 start)
				need_level1_music = 2;
			} else {
				need_level1_music = 0;
			}
		}
	} else {
		need_level1_music = 0;
		if (control_shift2 < 0 && check_get_item()) return;
		if (control_y != 1) {
			seqtbl_offset_char(49); // stand up from crouch
		} else {
			if (control_forward < 0) {
				control_forward = 1; // disable automatic repeat
				seqtbl_offset_char(79); // crouch-hop
			}
		}
	}
}

// seg005:0358
void __pascal far control_standing() {
	short var_2;
	if (control_shift2 < 0 && control_shift < 0 && check_get_item()) {
		return;
	}
	if (Char.charid != charid_0_kid && control_down < 0 && control_forward < 0) {
		draw_sword();
		return;
	} //else
	if (have_sword) {
		if (word_1EFCE != 0 && control_shift >= 0) goto loc_6213;
		if (can_guard_see_kid >= 2) {
			var_2 = char_opp_dist();
			if (var_2 >= -10 && var_2 < 90) {
				holding_sword = 1;
				if ((word)var_2 < (word)-6) {
					if (Opp.charid == charid_1_shadow &&
						(Opp.action == actions_3_in_midair || (Opp.frame >= 107 && Opp.frame < 118))
					) {
						word_1EFCE = 0;
					} else {
						draw_sword();
						return;
					}
				} else {
					back_pressed();
					return;
				}
			}
		} else {
			word_1EFCE = 0;
		}
	}
	if (control_shift < 0) {
		if (control_backward < 0) {
			back_pressed();
		} else if (control_up < 0) {
			up_pressed();
		} else if (control_down < 0) {
			down_pressed();
		} else if (control_x < 0 && control_forward < 0) {
			safe_step();
		}
	} else loc_6213: if (control_forward < 0) {
		if (is_keyboard_mode && control_up < 0) {
			standing_jump();
		} else {
			forward_pressed();
		}
	} else if (control_backward < 0) {
		back_pressed();
	} else if (control_up < 0) {
		if (is_keyboard_mode && control_forward < 0) {
			standing_jump();
		} else {
			up_pressed();
		}
	} else if (control_down < 0) {
		down_pressed();
	} else if (control_x < 0) {
		forward_pressed();
	}
}

// seg005:0482
void __pascal far up_pressed() {
	if ((get_tile_at_char() == tiles_16_level_door_left ||
		get_tile_behind_char() == tiles_16_level_door_left ||
		get_tile_infrontof_char() == tiles_16_level_door_left) &&
		level.start_room != drawn_room &&
		leveldoor_open
	){
		go_up_leveldoor();
	} else {
		if (control_x < 0) {
			standing_jump();
		} else {
			check_jump_up();
		}
	}
}

// seg005:04C7
void __pascal far down_pressed() {
	control_down = 1; // disable automatic repeat
	if (! tile_is_floor(get_tile_infrontof_char()) &&
		distance_to_edge_weight() < 3
	) {
		Char.x = char_dx_forward(5);
		load_fram_det_col();
	} else {
		if (! tile_is_floor(get_tile_behind_char()) &&
			distance_to_edge_weight() >= 8
		) {
			through_tile = get_tile_behind_char();
			get_tile_at_char();
			if (can_grab() &&
				(Char.direction >= dir_0_right ||
				get_tile_at_char() != tiles_4_gate ||
				curr_room_modif[curr_tilepos] >> 2 >= 6)
			) {
				Char.x = char_dx_forward(distance_to_edge_weight() - 9);
				seqtbl_offset_char(68); // climb down
			} else {
				crouch();
			}
		} else {
			crouch();
		}
	}
}

// seg005:0574
void __pascal far go_up_leveldoor() {
	Char.x = x_bump[tile_col + 5] + 10;
	Char.direction = dir_FF_left; // right
	seqtbl_offset_char(70); // go up on level door
}

// seg005:058F
void __pascal far control_turning() {
	if (control_shift >= 0 && control_x < 0 && control_y >= 0) {
		seqtbl_offset_char(43); // start run and run (after turning)
	}
}

// seg005:05AD
void __pascal far crouch() {
	seqtbl_offset_char(50); // crouch
	control_down = release_arrows();
}

// seg005:05BE
void __pascal far back_pressed() {
	word seq_id;
	control_backward = release_arrows();
	// After turn, Kid will draw sword if ...
	if (have_sword == 0 || // if Kid has sword
		can_guard_see_kid < 2 || // and can see Guard
		char_opp_dist() > 0 || // and Guard was behind him
		distance_to_edge_weight() < 2
	) {
		seq_id = 5; // turn
	} else {
		Char.sword = 2;
		word_1EFCE = 0;
		seq_id = 89; // turn and draw sword
	}
	seqtbl_offset_char(seq_id);
}

// seg005:060F
void __pascal far forward_pressed() {
	short distance;
	distance = get_edge_distance();
	if (edge_type == 1 && curr_tile2 != tiles_18_chomper && distance < 8) {
		// If char is near a wall, step instead of run.
		if (control_forward < 0) {
			safe_step();
		}
	} else {
		seqtbl_offset_char(1); // start run and run
	}
}

// seg005:0649
void __pascal far control_running() {
	if (control_x == 0 && (Char.frame == 7 || Char.frame == 11)) {
		control_forward = release_arrows();
		seqtbl_offset_char(13); // stop run
	} else if (control_x > 0) {
		control_backward = release_arrows();
		seqtbl_offset_char(6); // run-turn
	} else if (control_y < 0 && control_up < 0) {
		run_jump();
	} else if (control_down < 0) {
		control_down = 1; // disable automatic repeat
		seqtbl_offset_char(26); // crouch while running
	}
}

// seg005:06A8
void __pascal far safe_step() {
	short distance;
	control_shift2 = 1; // disable automatic repeat
	control_forward = 1; // disable automatic repeat
	distance = get_edge_distance();
	if (distance) {
		Char.repeat = 1;
		seqtbl_offset_char(distance + 28); // 29..42: safe step to edge
	} else if (edge_type != 1 && Char.repeat != 0) {
		Char.repeat = 0;
		seqtbl_offset_char(44); // step on edge
	} else {
		seqtbl_offset_char(39); // unsafe step (off ledge)
	}
}

// seg005:06F0
int __pascal far check_get_item() {
	if (get_tile_at_char() == tiles_10_potion ||
		curr_tile2 == tiles_22_sword
	) {
		if (! tile_is_floor(get_tile_behind_char())) {
			return 0;
		}
		Char.x = char_dx_forward(-14);
		load_fram_det_col();
	}
	if (get_tile_infrontof_char() == tiles_10_potion ||
		curr_tile2 == tiles_22_sword
	) {
		get_item();
		return 1;
	}
	return 0;
}

// seg005:073E
void __pascal far get_item() {
	short distance;
	if (Char.frame != 109) { // crouching
		distance = get_edge_distance();
		if (edge_type != 2) {
			Char.x = char_dx_forward(distance);
		}
		if (Char.direction >= dir_0_right) {
			Char.x = char_dx_forward((curr_tile2 == tiles_10_potion) - 2);
		}
		crouch();
	} else if (curr_tile2 == tiles_22_sword) {
		do_pickup(-1);
		seqtbl_offset_char(91); // get sword
	} else { // potion
		do_pickup(curr_room_modif[curr_tilepos] >> 5);
		seqtbl_offset_char(78); // drink
#ifdef USE_COPYPROT
		if (current_level == 15) {
			short index;
			for (index = 0; index < 14; ++index) {
				// remove letter on potions level
				if (copyprot_room[index] == curr_room &&
					copyprot_tile[index] == curr_tilepos
				) {
					copyprot_room[index] = 0;
					break;
				}
			}
		}
#endif
	}
}

// seg005:07FF
void __pascal far control_startrun() {
	if (control_y < 0 && control_x < 0) {
		standing_jump();
	}
}

// seg005:0812
void __pascal far control_jumpup() {
	if (control_x < 0 || control_forward < 0) {
		standing_jump();
	}
}

// seg005:0825
void __pascal far standing_jump() {
	control_up = control_forward = 1; // disable automatic repeat
	seqtbl_offset_char(3); // standing jump
}

// seg005:0836
void __pascal far check_jump_up() {
	control_up = release_arrows();
	through_tile = get_tile_above_char();
	get_tile_front_above_char();
	if (can_grab()) {
		grab_up_with_floor_behind();
	} else {
		through_tile = get_tile_behind_above_char();
		get_tile_above_char();
		if (can_grab()) {
			jump_up_or_grab();
		} else {
			jump_up();
		}
	}
}

// seg005:087B
void __pascal far jump_up_or_grab() {
	short distance;
	distance = distance_to_edge_weight();
	if (distance < 6) {
		jump_up();
	} else if (! tile_is_floor(get_tile_behind_char())) {
		// There is not floor behind char.
		grab_up_no_floor_behind();
	} else {
		// There is floor behind char, go back a bit.
		Char.x = char_dx_forward(distance - 14);
		load_fram_det_col();
		grab_up_with_floor_behind();
	}
}

// seg005:08C7
void __pascal far grab_up_no_floor_behind() {
	get_tile_above_char();
	Char.x = char_dx_forward(distance_to_edge_weight() - 10);
	seqtbl_offset_char(16); // jump up and grab (no floor behind)
}

// seg005:08E6
void __pascal far jump_up() {
	short distance;
	control_up = release_arrows();
	distance = get_edge_distance();
	if (distance < 4 && edge_type == 1) {
		Char.x = char_dx_forward(distance - 3);
	}
	get_tile(Char.room, get_tile_div_mod(back_delta_x(0) + dx_weight() - 6), Char.curr_row - 1);
	if (curr_tile2 != tiles_20_wall && ! tile_is_floor(curr_tile2)) {
		seqtbl_offset_char(28); // jump up with nothing above
	} else {
		seqtbl_offset_char(14); // jump up with wall or floor above
	}
}

// seg005:0968
void __pascal far control_hanging() {
	if (Char.alive < 0) {
		if (word_1E18A == 0 && control_y < 0) {
			can_climb_up();
		} else if (control_shift < 0) {
			// hanging against a wall or a doortop
			if (Char.action != actions_6_hang_straight &&
				(get_tile_at_char() == tiles_20_wall ||
				(Char.direction == dir_FF_left && ( // facing left
					curr_tile2 == tiles_7_doortop_with_floor ||
					curr_tile2 == tiles_12_doortop
				)))
			) {
				if (word_1E18A == 0) {
					play_sound(8); // touching a wall (hang against wall)
				}
				seqtbl_offset_char(25); // hang against wall (straight)
			} else {
				if (! tile_is_floor(get_tile_above_char())) {
					hang_fall();
				}
			}
		} else {
			hang_fall();
		}
	} else {
		hang_fall();
	}
}

// seg005:09DF
void __pascal far can_climb_up() {
	short seq_id;
	seq_id = 10; // climb up
	control_up = control_shift2 = release_arrows();
	get_tile_above_char();
	if (((curr_tile2 == tiles_13_mirror || curr_tile2 == tiles_18_chomper) &&
		Char.direction == dir_0_right) ||
		(curr_tile2 == tiles_4_gate && Char.direction != dir_0_right &&
		curr_room_modif[curr_tilepos] >> 2 < 6)
	) {
		seq_id = 73; // climb up to closed gate and down
	}
	seqtbl_offset_char(seq_id);
}

// seg005:0A46
void __pascal far hang_fall() {
	control_down = release_arrows();
	if (! tile_is_floor(get_tile_behind_char()) &&
		! tile_is_floor(get_tile_at_char())
	) {
		seqtbl_offset_char(23); // release ledge and fall
	} else {
		if (get_tile_at_char() == tiles_20_wall ||
			(Char.direction < dir_0_right && ( // looking left
				curr_tile2 == tiles_7_doortop_with_floor ||
				curr_tile2 == tiles_12_doortop
			))
		) {
			Char.x = char_dx_forward(-7);
		}
		seqtbl_offset_char(11); // end of climb down
	}
}

// seg005:0AA8
void __pascal far grab_up_with_floor_behind() {
	short distance;
	distance = distance_to_edge_weight();
	if (distance < 4 && get_edge_distance() < 4 && edge_type != 1) {
		Char.x = char_dx_forward(distance);
		seqtbl_offset_char(8); // jump up and grab (when?)
	} else {
		Char.x = char_dx_forward(distance - 4);
		seqtbl_offset_char(24); // jump up and grab (with floor behind)
	}
}

// seg005:0AF7
void __pascal far run_jump() {
	short var_2;
	short xpos;
	short col;
	short var_8;
	if (Char.frame >= 7) {
		// Align Kid to edge of floor.
		xpos = char_dx_forward(4);
		col = get_tile_div_mod_m7(xpos);
		for (var_2 = 0; var_2 < 2; ++var_2) {
			col += dir_front[Char.direction + 1];
			get_tile(Char.room, col, Char.curr_row);
			if (curr_tile2 == tiles_2_spike || ! tile_is_floor(curr_tile2)) {
				var_8 = distance_to_edge(xpos) + 14 * var_2 - 14;
				if ((word)var_8 < (word)-8 || var_8 >= 2) {
					if (var_8 < 128) return;
					var_8 = -3;
				}
				Char.x = char_dx_forward(var_8 + 4);
				break;
			}
		}
		control_up = release_arrows(); // disable automatic repeat
		seqtbl_offset_char(4); // run-jump
	}
}

// sseg005:0BB5
void __pascal far back_with_sword() {
	short frame;
	frame = Char.frame;
	if (frame == 158 || frame == 170 || frame == 171) {
		control_backward = 1; // disable automatic repeat
		seqtbl_offset_char(57); // back with sword
	}
}

// seg005:0BE3
void __pascal far forward_with_sword() {
	short frame;
	frame = Char.frame;
	if (frame == 158 || frame == 170 || frame == 171) {
		control_forward = 1; // disable automatic repeat
		if (Char.charid != charid_0_kid) {
			seqtbl_offset_char(56); // forward with sword (Guard)
		} else {
			seqtbl_offset_char(86); // forward with sword (Kid)
		}
	}
}

// seg005:0C1D
void __pascal far draw_sword() {
	word seq_id;
	seq_id = 55; // draw sword
	control_forward = control_shift2 = release_arrows();
	if (Char.charid == charid_0_kid) {
		play_sound(19); // taking out the sword
		word_1EFCE = 0;
	} else if (Char.charid != charid_1_shadow) {
		seq_id = 90; // stand active
	}
	Char.sword = 2;
	seqtbl_offset_char(seq_id);
}

// seg005:0C67
void __pascal far control_with_sword() {
	short distance;
	if (Char.action < actions_2_hang_climb) {
		if (get_tile_at_char() == tiles_11_loose || can_guard_see_kid >= 2) {
			distance = char_opp_dist();
			if ((word)distance < (word)90) {
				swordfight();
				return;
			} else if (distance < 0) {
				if ((word)distance < (word)-4) {
					seqtbl_offset_char(60); // turn with sword (after switching places)
					return;
				} else {
					swordfight();
					return;
				}
			}
		} /*else*/ {
			if (Char.charid == charid_0_kid && Char.alive < 0) {
				holding_sword = 0;
			}
			if (Char.charid < charid_2_guard) {
				// frame 171: stand with sword
				if (Char.frame == 171) {
					Char.sword = 0;
					seqtbl_offset_char(92); // put sword away (Guard died)
				}
			} else {
				swordfight();
			}
		}
	}
}

// seg005:0CDB
void __pascal far swordfight() {
	short frame;
	short seq_id;
	short charid;
	frame = Char.frame;
	charid = Char.charid;
	// frame 161: parry
	if (frame == 161 && control_shift2 >= 0) {
		seqtbl_offset_char(57); // back with sword (when parrying)
		return;
	} else if (control_shift2 < 0) {
		if (charid == charid_0_kid) {
			kid_sword_strike = 15;
		}
		sword_strike();
		if (control_shift2 == 1) return;
	}
	if (control_down < 0) {
		if (frame == 158 || frame == 170 || frame == 171) {
			control_down = 1; // disable automatic repeat
			Char.sword = 0;
			if (charid == charid_0_kid) {
				word_1EFCE = 1;
				guard_refrac = 9;
				holding_sword = 0;
				seq_id = 93; // put sword away fast (down pressed)
			} else if (charid == charid_1_shadow) {
				seq_id = 92; // put sword away
			} else {
				seq_id = 87; // stand inactive (when Kid leaves sight)
			}
			seqtbl_offset_char(seq_id);
		}
	} else if (control_up < 0) {
		parry();
	} else if (control_forward < 0) {
		forward_with_sword();
	} else if (control_backward < 0) {
		back_with_sword();
	}
}

// seg005:0DB0
void __pascal far sword_strike() {
	short frame;
	short seq_id;
	frame = Char.frame;
	if (frame == 157 || // walk with sword
		frame == 158 || // stand with sword
		frame == 170 || // stand with sword
		frame == 171 || // stand with sword
		frame == 165 // walk with sword
	) {
		if (Char.charid == charid_0_kid) {
			seq_id = 75; // strike with sword (Kid)
		} else {
			seq_id = 58; // strike with sword (Guard)
		}
	} else if (frame == 150 || frame == 161) { // parry
		seq_id = 66; // strike with sword after parrying
	} else {
		return;
	}
	control_shift2 = 1; // disable automatic repeat
	seqtbl_offset_char(seq_id);
}

// seg005:0E0F
void __pascal far parry() {
	short opp_frame;
	short char_frame;
	short var_6;
	short seq_id;
	short char_charid;
	char_frame = Char.frame;
	opp_frame = Opp.frame;
	char_charid = Char.charid;
	seq_id = 62; // defend (parry) with sword
	var_6 = 0;
	if (
		char_frame == 158 || // stand with sword
		char_frame == 170 || // stand with sword
		char_frame == 171 || // stand with sword
		char_frame == 168 || // back?
		char_frame == 165 // walk with sword
	) {
		if (char_opp_dist() >= 32 && char_charid != charid_0_kid) {
			back_with_sword();
			return;
		} else if (char_charid == charid_0_kid) {
			if (opp_frame == 168) return;
			if (opp_frame != 151 &&
				opp_frame != 152 &&
				opp_frame != 162
			) {
				if (opp_frame == 153) { // strike
					var_6 = 1;
				} else
				if (char_charid != charid_0_kid) {
					back_with_sword();
					return;
				}
			}
		} else {
			if (opp_frame != 152) return;
		}
	} else {
		if (char_frame != 167) return;
		seq_id = 61; // parry after striking with sword
	}
	control_up = 1; // disable automatic repeat
	seqtbl_offset_char(seq_id);
	if (var_6) {
		play_seq();
	}
}
