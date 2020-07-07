/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 5;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FuraCode Nerd Font:style=Medium:size=9", "JoyPixels:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[]       = { "FuraCode Nerd Font:style=Medium:size=9" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance    title       tags mask     isfloating   monitor */
	{ "mpv",               NULL,       NULL,       0,            1,           -1 },
	{ "firefox",           NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Navigator",         NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[N]",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define XF86MonBrightnessDown   0x1008ff03
#define XF86MonBrightnessUp     0x1008ff02
#define XF86AudioMute           0x1008ff12
#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioRaiseVolume    0x1008ff13
#define XF86AudioPlay           0x1008FF14
#define XF86AudioPrev           0x1008FF16
#define XF86AudioNext           0x1008FF17
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "90x30", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_Delete, spawn,          SHCMD("dmenu-action") },
	{ MODKEY,                       XK_Insert, spawn,          SHCMD("clipmenu") },
	{ MODKEY|ShiftMask,             XK_Insert, spawn,          SHCMD("st -e notetaking") },
	{ 0,                            XK_Print,  spawn,          SHCMD("maimpick") },
	{ ShiftMask,                    XK_Print,  spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,                       XK_Print,  spawn,          SHCMD("dmenu-record") },
	{ MODKEY,                       XK_m,      spawn,          SHCMD("st -e ncmpcpp") },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("st -e pulsemixer") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("st -e newsboat") },
	{ MODKEY|ControlMask,           XK_w,      spawn,          SHCMD("st -e nmtui") },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("st -e htop") },
	{ MODKEY,                       XK_f,      spawn,          SHCMD("st -e lf") },

	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ 0,         XF86MonBrightnessDown,        spawn,          SHCMD("light -U 5") },
	{ 0,         XF86MonBrightnessUp,          spawn,          SHCMD("light -A 5") },
	{ 0,         XF86AudioMute,                spawn,          SHCMD("pulsemixer --toggle-mute; kill -44 $(pidof dwmblocks)") },
	{ 0,         XF86AudioRaiseVolume,         spawn,          SHCMD("pulsemixer --change-volume +5; kill -44 $(pidof dwmblocks)") },
	{ 0,         XF86AudioLowerVolume,         spawn,          SHCMD("pulsemixer --change-volume -5; kill -44 $(pidof dwmblocks)") },
	{ 0,         XF86AudioPlay,                spawn,          SHCMD("mpc toggle") },
	{ 0,         XF86AudioPrev,                spawn,          SHCMD("mpc prev") },
	{ 0,         XF86AudioNext,                spawn,          SHCMD("mpc next") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
