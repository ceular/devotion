/*
===========================================================================
Copyright (C) 2004-2006 Tony J. White
Portions Copyright (C) 2009 Karl F. Kuglin

This file is part of the Open Arena source code.

Originally copied from Tremulous under GPL version 2 including any later
version.  The code has been modified to fit the needs of Open Arena. 

Open Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Open Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Open Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#ifndef _G_ADMIN_H
#define _G_ADMIN_H

#define AP(x) trap_SendServerCommand(-1, x)
#define CP(x) trap_SendServerCommand(ent-g_entities, x)
#define CPx(x, y) trap_SendServerCommand(x, y)
#define ADMP(x) G_admin_print(ent, x)
#define ADMBP(x) G_admin_buffer_print(ent, x)
#define ADMBP_begin() G_admin_buffer_begin()
#define ADMBP_end() G_admin_buffer_end(ent)

#define MAX_ADMIN_LEVELS 32 
#define MAX_ADMIN_ADMINS 1024
#define MAX_ADMIN_BANS 1024
#define MAX_ADMIN_PLAYERHOOKS 1024
#define MAX_ADMIN_NAMELOGS 128
#define MAX_ADMIN_NAMELOG_NAMES 5
#define MAX_ADMIN_FLAGS 64
#define MAX_ADMIN_COMMANDS 64
#define MAX_ADMIN_CMD_LEN 20
#define MAX_ADMIN_BAN_REASON 50
#define MAX_ADMIN_PLAYERHOOK 32
#define MAX_ADMIN_PLAYERHOOK_ARG 256
//KK-OAX
#define MAX_ADMIN_WARNINGS 1024

/*
 * 1 - cannot be vote kicked, vote muted
 * 2 - cannot be censored or flood protected TODO
 * 3 - never loses credits for changing teams
 * 4 - can see team chat as a spectator
 * 5 - can switch teams any time, regardless of balance
 * 6 - does not need to specify a reason for a kick/ban
 * 7 - can call a vote at any time (regardless of a vote being disabled or 
 * voting limitations)
 * 8 - does not need to specify a duration for a ban
 * 9 - can run commands from team chat
 * 0 - inactivity rules do not apply to them
 * ! - admin commands cannot be used on them
 * @ - does not show up as an admin in !listplayers
 * $ - sees all information in !listplayers 
 * ? - receieves and can send /a admin messages
 */
#define ADMF_IMMUNITY '1'
#define ADMF_NOCENSORFLOOD '2' /* TODO */
#define ADMF_TEAMCHANGEFREE '3'
#define ADMF_SPEC_ALLCHAT '4'
#define ADMF_FORCETEAMCHANGE '5'
#define ADMF_UNACCOUNTABLE '6'
#define ADMF_NO_VOTE_LIMIT '7'
#define ADMF_CAN_PERM_BAN '8'
#define ADMF_TEAMCHAT_CMD '9'
#define ADMF_ACTIVITY '0'

#define ADMF_IMMUTABLE '!'
#define ADMF_INCOGNITO '@'
#define ADMF_ADMINCHAT '?'
#define ADMF_SHOW_IP '/'
#define ADMF_SHOW_GUIDSTUB '/'
// XXX: reserved values:
// '*' - matches everything
// '-'
// '+'

#define ADMF_ADMINTEST       'a'
#define ADMF_BAN             'b'
#define ADMF_UNBAN           ADMF_BAN
#define ADMF_ADJUSTBAN       ADMF_BAN
#define ADMF_SHOWBANS        'B'
#define ADMF_CANCELVOTE      'c'
#define ADMF_TIME            'C'
#define ADMF_DISORIENT       'd'
#define ADMF_ORIENT          ADMF_DISORIENT
#define ADMF_LISTADMINS      'D'
#define ADMF_NAMELOG         'e'
#define ADMF_SETPING         'E'
#define ADMF_EQPING          ADMF_SETPING
#define ADMF_SHUFFLE         'f'
#define ADMF_READCONFIG      'G'
#define ADMF_HELP            'h'
#define ADMF_LISTPLAYERS     'i'
#define ADMF_PLAYSOUND       'j'
#define ADMF_KICK            'k'
#define ADMF_LOCK            'K'
#define ADMF_UNLOCK          ADMF_LOCK
#define ADMF_LOCKALL         ADMF_LOCK
#define ADMF_UNLOCKALL       ADMF_LOCKALL
#define ADMF_TOURNEYLOCK     'L'
#define ADMF_TOURNEYUNLOCK   ADMF_TOURNEYLOCK
#define ADMF_MUTE            'm'
#define ADMF_VOTEMUTE        ADMF_MUTE
#define ADMF_MUTESPEC        ADMF_MUTE
#define ADMF_UNMUTESPEC      ADMF_MUTESPEC
#define ADMF_MAP             'M'
#define ADMF_NEXTMAP         'n'
#define ADMF_VOTENEXTMAP     ADMF_NEXTMAP
#define ADMF_RENAME          'N'
#define ADMF_SHADOWMUTE      'O'
#define ADMF_PUTTEAM         'p'
#define ADMF_SWAP            ADMF_PUTTEAM
#define ADMF_SPEC999         'P'
#define ADMF_COIN            'q'
#define ADMF_RESTART         'r'
#define ADMF_RECORD          'R'
#define ADMF_STOPRECORD      ADMF_RECORD
#define ADMF_SETLEVEL        's'
#define ADMF_SLAP            'S'
#define ADMF_HANDICAP        ADMF_SLAP
#define ADMF_TIMEOUT         't'
#define ADMF_TIMEIN          ADMF_TIMEOUT
#define ADMF_TEAMS           'T'
#define ADMF_PASSVOTE        'V'
#define ADMF_WARN            'w'
#define ADMF_PLAYERHOOK      'X'
#define ADMF_ALLREADY        'y'

#define MAX_ADMIN_LISTITEMS 20
#define MAX_ADMIN_SHOWBANS 10

// important note: QVM does not seem to allow a single char to be a
// member of a struct at init time.  flag has been converted to char*
typedef struct
{
  char *keyword;
  char *alias;
  qboolean ( * handler ) ( gentity_t *ent, int skiparg );
  int flag;
  char *function;  // used for !help
  char *syntax;  // used for !help
}
g_admin_cmd_t;

typedef struct g_admin_level
{
  int level;
  char name[ MAX_NAME_LENGTH ];
  char flags[ MAX_ADMIN_FLAGS ];
}
g_admin_level_t;

typedef struct g_admin_admin
{
  char guid[ 33 ];
  char name[ MAX_NAME_LENGTH ];
  int level;
  char flags[ MAX_ADMIN_FLAGS ];
}
g_admin_admin_t;

typedef struct g_admin_ban
{
  char name[ MAX_NAME_LENGTH ];
  char guid[ 33 ];
  char ip[ 40 ];
  char reason[ MAX_ADMIN_BAN_REASON ];
  char made[ 18 ]; // big enough for strftime() %c
  int expires;
  char banner[ MAX_NAME_LENGTH ];
}
g_admin_ban_t;

typedef struct g_admin_playerhook
{
  char name[ MAX_NAME_LENGTH ];
  char guid[ 33 ];
  char ip[ 40 ];
  char action[ MAX_ADMIN_PLAYERHOOK ];
  char argument[ MAX_ADMIN_PLAYERHOOK_ARG ];
  char made[ 18 ]; // big enough for strftime() %c
  int expires;
  char banner[ MAX_NAME_LENGTH ];
}
g_admin_playerhook_t;

typedef struct g_admin_command
{
  char command[ MAX_ADMIN_CMD_LEN ];
  char exec[ MAX_QPATH ];
  char desc[ 50 ];
  int levels[ MAX_ADMIN_LEVELS + 1 ];
}
g_admin_command_t;

typedef struct g_admin_namelog
{
  char      name[ MAX_ADMIN_NAMELOG_NAMES ][ MAX_NAME_LENGTH ];
  char      ip[ 40 ];
  char      guid[ 33 ];
  int       slot;
  qboolean  banned;
}
g_admin_namelog_t;
//KK-OAX Added for Warnings
typedef struct g_admin_warning {
	char    name[ MAX_NAME_LENGTH ];
	char    guid[ 33 ];
	char    ip[ 40 ];
	char    warning[MAX_STRING_CHARS];
	char    made[ 18 ];
	char    warner[MAX_NAME_LENGTH];
	int     expires;
} g_admin_warning_t;

qboolean G_admin_ban_check( char *userinfo, char *reason, int rlen );
qboolean G_admin_apply_playerhooks( gentity_t *player, char *userinfo );
qboolean G_admin_cmd_check( gentity_t *ent, qboolean say );
qboolean G_admin_record( gentity_t *ent, int skiparg );
qboolean G_admin_showbalance( gentity_t *ent, int skiparg );
qboolean G_admin_balance( gentity_t *ent, int skiparg );
qboolean G_admin_stoprecord( gentity_t *ent, int skiparg );
qboolean G_admin_readconfig( gentity_t *ent, int skiparg );
qboolean G_admin_permission( gentity_t *ent, int flag );
qboolean G_admin_uses_registeredname( gentity_t *ent );
qboolean G_admin_name_check( gentity_t *ent, char *name, char *err, int len );
void G_admin_namelog_update( gclient_t *ent, qboolean disconnect );
int G_admin_level( gentity_t *ent );
int G_admin_parse_time( const char *time );

// ! command functions
qboolean G_admin_teams( gentity_t *ent, int skiparg );
qboolean G_admin_time( gentity_t *ent, int skiparg );
qboolean G_admin_timeout( gentity_t *ent, int skiparg );
qboolean G_admin_timein( gentity_t *ent, int skiparg );
qboolean G_admin_tourneylock( gentity_t *ent, int skiparg );
qboolean G_admin_tourneyunlock( gentity_t *ent, int skiparg );
qboolean G_admin_setlevel( gentity_t *ent, int skiparg );
qboolean G_admin_kick( gentity_t *ent, int skiparg );
qboolean G_admin_frag( gentity_t *ent, int skiparg );
qboolean G_admin_adjustban( gentity_t *ent, int skiparg );
qboolean G_admin_ban( gentity_t *ent, int skiparg );
qboolean G_admin_unban( gentity_t *ent, int skiparg );
qboolean G_admin_playsound( gentity_t *ent, int skiparg );
qboolean G_admin_putteam( gentity_t *ent, int skiparg );
qboolean G_admin_playerhook( gentity_t *ent, int skiparg );
qboolean G_admin_swap( gentity_t *ent, int skiparg );
qboolean G_admin_swaprecent( gentity_t *ent, int skiparg );
qboolean G_admin_listadmins( gentity_t *ent, int skiparg );
qboolean G_admin_listplayers( gentity_t *ent, int skiparg );
qboolean G_admin_map( gentity_t *ent, int skiparg );
qboolean G_admin_mute( gentity_t *ent, int skiparg );
qboolean G_admin_mutespec( gentity_t *ent, int skiparg );
qboolean G_admin_unmutespec( gentity_t *ent, int skiparg );
qboolean G_admin_showbans( gentity_t *ent, int skiparg );
qboolean G_admin_handicap( gentity_t *ent, int skiparg );
qboolean G_admin_help( gentity_t *ent, int skiparg );
qboolean G_admin_admintest( gentity_t *ent, int skiparg );
qboolean G_admin_allready( gentity_t *ent, int skiparg );
qboolean G_admin_cancelvote( gentity_t *ent, int skiparg );
qboolean G_admin_coin( gentity_t *ent, int skiparg );
qboolean G_admin_passvote( gentity_t *ent, int skiparg );
qboolean G_admin_spec999( gentity_t *ent, int skiparg );
qboolean G_admin_rename( gentity_t *ent, int skiparg );
qboolean G_admin_restart( gentity_t *ent, int skiparg );
qboolean G_admin_nextmap( gentity_t *ent, int skiparg );
qboolean G_admin_votenextmap( gentity_t *ent, int skiparg );
qboolean G_admin_namelog( gentity_t *ent, int skiparg );
qboolean G_admin_lock( gentity_t *ent, int skiparg );
qboolean G_admin_unlock( gentity_t *ent, int skiparg );
qboolean G_admin_lockall( gentity_t *ent, int skiparg );
qboolean G_admin_unlockall( gentity_t *ent, int skiparg );
//KK-OAX
qboolean G_admin_disorient( gentity_t *ent, int skiparg );
qboolean G_admin_orient(gentity_t *ent, int skiparg );
qboolean G_admin_eqping(gentity_t *ent, int skiparg );
qboolean G_admin_setping(gentity_t *ent, int skiparg );
qboolean G_admin_slap(gentity_t *ent, int skiparg );
qboolean G_admin_warn( gentity_t *ent, int skiparg );
qboolean G_admin_shuffle( gentity_t *ent, int skiparg );

void G_admin_print( gentity_t *ent, char *m );
void G_admin_buffer_print( gentity_t *ent, char *m );
void G_admin_buffer_begin( void );
void G_admin_buffer_end( gentity_t *ent );

void G_admin_duration( int secs, char *duration, int dursize );
void G_admin_cleanup( void );
void G_admin_namelog_cleanup( void );

#endif /* ifndef _G_ADMIN_H */
